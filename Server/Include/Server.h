#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#ifndef OPEN_FILE_ERROR
#define OPEN_FILE_ERROR 125
#endif // OPEN_FILE_ERROR

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/completion_condition.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/bind.hpp>

#include <vector>
#include <thread>
#include <mutex>
#include <iostream>
#include <fstream>
#include <memory>
#include <queue>

#include <csignal>

using namespace boost::asio;


class Server {
private:
    io_service ioService;
    ip::tcp::endpoint ep;

    std::vector<ip::tcp::socket> sockets;

    std::unique_ptr<ip::tcp::acceptor> acceptor;

    std::vector<std::thread> threadPool;
    std::mutex socketsAccess;

    std::atomic<bool> areWorked;

    size_t fileId;

    void ConnectionHandler();
    void ReadUntilEndOfConnection();
    void Parsing(streambuf &buf);
public:
    Server();
    void Run();
    void Close(int sigNum);
};

#endif
