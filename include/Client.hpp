#pragma once
#include <string>

class Client
{
private:
	bool m_isConnected;
	int m_sockfd;

	int socket();
	struct sockaddr_in setupServerAddr(const std::string ip, unsigned short port);
	struct in_addr stringToAddr(const std::string addrStr);
	void connectSocket(const struct sockaddr_in serverAddr);
public:
	Client();
	~Client();
	void connect(const std::string ip, unsigned short port);
	bool isConnected();
};
