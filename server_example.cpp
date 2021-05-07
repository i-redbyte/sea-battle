#ifdef SERVER_EXAMPLE

#include <iostream>
#include <signal.h>

#include "include/tcp_server.h"

TcpServer server;

server_observer_t observer1, observer2;

void onIncomingMsg1(const Client & client, const char * msg, size_t size) {
    std::string msgStr = msg;
    std::cout << "Observer1 got client msg: " << msgStr << std::endl;

    if (msgStr.find("quit") != std::string::npos) {
        std::cout << "Closing server..." << std::endl;
        pipe_ret_t finishRet = server.finish();
        if (finishRet.success) {
            std::cout << "Server closed." << std::endl;
        } else {
            std::cout << "Failed closing server: " << finishRet.msg << std::endl;
        }
    } else if (msgStr.find("print") != std::string::npos){
        server.printClients();
    } else {
        std::string replyMsg = "server got this msg: "+ msgStr;
        server.sendToAllClients(replyMsg.c_str(), replyMsg.length());
    }
}

void onIncomingMsg2(const Client & client, const char * msg, size_t size) {
    std::string msgStr = msg;
    std::cout << "Observer2 got client msg: " << msgStr << std::endl;

    std::string replyMsg = "server got this msg: "+ msgStr;
    server.sendToClient(client, msg, size);
}

void onClientDisconnected(const Client & client) {
    std::cout << "Client: " << client.getIp() << " disconnected: " << client.getInfoMessage() << std::endl;
}

int main(int argc, char *argv[])
{
    pipe_ret_t startRet = server.start(65123);
    if (startRet.success) {
        std::cout << "Server setup succeeded" << std::endl;
    } else {
        std::cout << "Server setup failed: " << startRet.msg << std::endl;
        return EXIT_FAILURE;
    }

    observer1.incoming_packet_func = onIncomingMsg1;
    observer1.disconnected_func = onClientDisconnected;
    observer1.wantedIp = "127.0.0.1";
    server.subscribe(observer1);

    observer2.incoming_packet_func = onIncomingMsg2;
    observer1.disconnected_func = nullptr;
    observer2.wantedIp = "10.88.0.11";
    server.subscribe(observer2);

    while(1) {
        Client client = server.acceptClient(0);
        if (client.isConnected()) {
            std::cout << "Got client with IP: " << client.getIp() << std::endl;
            server.printClients();
        } else {
            std::cout << "Accepting client failed: " << client.getInfoMessage() << std::endl;
        }
        sleep(1);
    }

    return 0;
}

#endif