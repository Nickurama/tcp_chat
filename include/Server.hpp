#pragma once
#include <string>
#include <netinet/in.h>

class Server
{
private:
	static const int LISTEN_BACKLOG = 5;
	std::string m_ip;
	unsigned short m_port;
	bool m_isRunning;
	struct sockaddr_in m_address;
	void setupAddress(unsigned short port);
	int socket();
	void bind(int sockfd);
	void listen(int sockfd);
	int accept(int sockfd);
public:
	Server(const std::string ip, const unsigned short port);
	std::string getIp();
	unsigned short getPort();
	bool isRunning();
	int numConnections();
	void start();
};
