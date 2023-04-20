#include "Client.h"

[[noreturn]] int main() {
    Client client;

    std::string addr;
    int port;

    std::cin >> addr >> port;

    client.Run(addr, port);
    client.Test();

     while (true)
        client.Work();
}
