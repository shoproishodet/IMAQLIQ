#include "Client.h"


Client::Client() noexcept : sock(ioService) {}

void Client::Run(const std::string &address, int port) {
    ep = std::move(ip::tcp::endpoint(ip::address::from_string(address), port));
    sock.connect(ep);
}

void Client::WriteFile(const std::string &path) {
    size_t fileSize = std::filesystem::file_size(path);
    std::cout << fileSize << std::endl;

    std::fstream file(path);

    std::string fileSizeStr = std::to_string(fileSize) + " ";
    std::string buf;

    buf.resize(fileSize);

    file.read(buf.data(), static_cast<std::streamsize>(fileSize));
    file.close();

    sock.write_some(buffer(fileSizeStr));
    sock.write_some(buffer(buf));
}

void Client::Test() {
    WriteFile("cash.txt");
    WriteFile("potter.txt");

    std::this_thread::sleep_for(std::chrono::seconds(2));
    WriteFile("cash.txt");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    WriteFile("potter.txt");
}

void Client::Work() {
    std::string path;
    std::cout << "Input file path:" << std::endl;
    std::cin >> path;

    WriteFile(path);
}

