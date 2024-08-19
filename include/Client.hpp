#pragma once
#include <string>

class Client
{
private:
	static const int DEFAULT_CONN_ATTEMPTS = 3;
	static const int DEFAULT_ATTEMPT_TIMEOUT = 500;
	bool m_isConnected;
	int m_sockfd;
	int m_connAttempts;
	int m_attemptTimeoutMs;

	int socket();
	struct sockaddr_in setupServerAddr(const std::string ip, unsigned short port);
	struct in_addr stringToAddr(const std::string addrStr);
	void connectSocket(const struct sockaddr_in serverAddr);
public:
	Client();
	Client(int connAttempts, int attemptTimeoutMs);
	~Client();
	void connect(const std::string ip, unsigned short port);
	bool isConnected();
};
