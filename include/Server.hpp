#pragma once
#include <string>
#include <netinet/in.h>

class Server
{
private:
	static const int LISTEN_BACKLOG = 5;
	unsigned short m_port;
	bool m_isRunning;
	struct sockaddr_in m_address;
	int m_sockfd;

	struct sockaddr_in setupAddress(unsigned short port);
	int socket();
	static void bind(int sockfd, struct sockaddr_in address);
	void listen();
	int accept();
public:
	Server(unsigned short port);
	~Server();
	unsigned short getPort();
	bool isRunning();
	int numConnections();
	void start();
};
