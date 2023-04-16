#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/write.hpp>

#include <thread>
#include <mutex>
#include <fstream>
#include <filesystem>
#include <vector>
#include <iostream>

using namespace boost::asio;

class Client {
private:
    io_service ioService;
    ip::tcp::socket sock;
    ip::tcp::endpoint ep;
public:
    Client() noexcept;
    void Run(const std::string &address, int port);
    void WriteFile(const std::string &path);
    void Test();
    void Work();
};


#endif //CLIENT_CLIENT_H
