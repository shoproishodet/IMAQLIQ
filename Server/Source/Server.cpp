#include "Server.h"


void Server::ConnectionHandler() {
    std::cout << ep.address() << "\t" << ep.port() << std::endl;

    while (areWorked.load()) {
        boost::system::error_code ec;
        acceptor->listen();

        ip::tcp::socket sock(ioService);
        acceptor->accept(sock, ec);

        if (ec)
            std::cout << "Acceptor error occurred!";

        if (sock.is_open()) {
            std::lock_guard<std::mutex> lock(socketsAccess);
            sockets.emplace_back(std::move(sock));
        }
    }
}

void Server::ReadUntilEndOfConnection() {
    while (areWorked.load()) {
        std::unique_lock<std::mutex> lock(socketsAccess);
        for (auto &sock : sockets) {
            if (!sock.available())
                continue;

            streambuf sockBuf;

            char delim = ' ';

            boost::system::error_code ec;
            size_t consumeSize = read(sock, sockBuf, transfer_exactly(sock.available()), ec);

            if (ec) {
                std::cerr << "Can't read data size from socket!" << std::endl;
                continue;
            }

            Parsing(sockBuf);

            sockBuf.consume(consumeSize);
        }
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(std::rand() % 100 + 1));
    }
}

Server::Server() : ep(ip::tcp::endpoint(ip::tcp::v4(), 2001)), fileId(0), areWorked(false) {}

void Server::Run() {
    std::ifstream fileStream("available_file_id.txt");

    if (!fileStream.is_open()) {
        std::cerr << "Error occurred, can't open available_file_id.txt" << std::endl;
        exit(OPEN_FILE_ERROR);
    }

    fileStream >> fileId;
    fileStream.close();

    areWorked.store(true);

    acceptor = std::make_unique<ip::tcp::acceptor>(ioService, ep);

    threadPool.emplace_back([this](){ this->ConnectionHandler(); });
    threadPool.emplace_back([this](){ this->ReadUntilEndOfConnection(); });

    while (areWorked.load())
        std::this_thread::sleep_for(std::chrono::seconds (1));


    threadPool[0].detach();
    threadPool[1].join();
}

void Server::Close(int sigNum) {
    std::cout << "Handling signal: " << sigNum << std::endl;

    areWorked.store(false);

    /*
    std::cout << (areWorked.load() ? "areWorked is true, seems it's a problem" : "areWorked is false, seems it's not a problem") << std::endl;
    */

    acceptor->close();

    /*
    if (acceptor->is_open())
        std::cerr << "Acceptor already open, try fix it" << std::endl;
    else
        std::cerr << "Acceptor is close, seems it's not a problem" << std::endl;
    */

    std::unique_lock<std::mutex> lock(socketsAccess);

    for (auto &sock : sockets)
        sock.close();

    std::ofstream fileStream("available_file_id.txt");

    if (!fileStream.is_open()) {
        std::cerr << "Error occurred, can't open available_file_id.txt" << std::endl;
        exit(OPEN_FILE_ERROR);
    }

    fileStream << fileId + 1;
    fileStream.close();
}

void Server::Parsing(streambuf &buf) {
    std::istream bufStream(&buf);

    while (!bufStream.eof()) {
        size_t fileSize;
        bufStream >> fileSize;

        if (bufStream.eof())
            break;

        char trash;
        bufStream.read(&trash, 1);

        std::string toWrite;
        toWrite.resize(fileSize);

        bufStream.read(toWrite.data(), fileSize);

        std::ofstream file("outputFiles/received_file_id_" + std::to_string(fileId++) + ".txt");

        if (!file.is_open())
            std::cerr << "Create file error occurred!" << std::endl;

        file.write(toWrite.data(), fileSize);
        file.close();
    }


}
