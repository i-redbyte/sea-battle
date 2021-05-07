
#ifdef CLIENT_EXAMPLE

#include <iostream>
#include <signal.h>
#include "include/tcp_client.h"

TcpClient client;

void sig_exit(int s)
{
	std::cout << "Closing client..." << std::endl;
	pipe_ret_t finishRet = client.finish();
	if (finishRet.success) {
		std::cout << "Client closed." << std::endl;
	} else {
		std::cout << "Failed to close client." << std::endl;
	}
	exit(0);
}

void onIncomingMsg(const char * msg, size_t size) {
	std::cout << "Got msg from server: " << msg << std::endl;
}

void onDisconnection(const pipe_ret_t & ret) {
	std::cout << "Server disconnected: " << ret.msg << std::endl;
	std::cout << "Closing client..." << std::endl;
    pipe_ret_t finishRet = client.finish();
	if (finishRet.success) {
		std::cout << "Client closed." << std::endl;
	} else {
		std::cout << "Failed to close client: " << finishRet.msg << std::endl;
	}
}


int main() {
	signal(SIGINT, sig_exit);

    client_observer_t observer;
	observer.wantedIp = "127.0.0.1";
	observer.incoming_packet_func = onIncomingMsg;
	observer.disconnected_func = onDisconnection;
	client.subscribe(observer);

    pipe_ret_t connectRet = client.connectTo("127.0.0.1", 65123);
	if (connectRet.success) {
		std::cout << "Client connected successfully" << std::endl;
	} else {
		std::cout << "Client failed to connect: " << connectRet.msg << std::endl;
		return EXIT_FAILURE;
	}

	while(1)
	{
		std::string msg = "hello server\n";
        pipe_ret_t sendRet = client.sendMsg(msg.c_str(), msg.size());
		if (!sendRet.success) {
			std::cout << "Failed to send msg: " << sendRet.msg << std::endl;
			break;
		}
		sleep(1);
	}

	return 0;
}

#endif