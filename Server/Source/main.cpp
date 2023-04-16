#include <Server.h>

Server server;

void SignalHandler(int sigNum) {
    server.Close(sigNum);
}

int main() {
    signal(SIGINT, SignalHandler);
    signal(SIGTERM, SignalHandler);
    signal(SIGHUP, SignalHandler);
    server.Run();
}
