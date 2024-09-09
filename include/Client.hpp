#pragma once
#include <mutex>
#include <string>
#include <thread>

class Client
{
public:
	Client();
	Client(int connAttempts, int attemptTimeoutMs);
	~Client();
	void connect(const std::string& ip, unsigned short port);
	void disconnect();
	bool isConnected();
private:
	static const int DEFAULT_CONN_ATTEMPTS = 3;
	static const int DEFAULT_ATTEMPT_TIMEOUT = 500;
	std::mutex m_isConnectedMutex;
	bool m_isConnected;
	std::thread m_receiveThread;
	int m_sockfd;
	int m_connAttempts;
	int m_attemptTimeoutMs;
	int m_pipeStopEvent[2];

	static int socket();
	static struct in_addr stringToAddr(const std::string& addrStr);
	static struct sockaddr_in setupServerAddr(const std::string& ip, unsigned short port);
	static void connectSocket(int sockfd, const struct sockaddr_in serverAddr, int connAttempts, int attemptTimeoutMs);
	static void makePipe(int *pipe);

	void startReceiving(int sockfd, int pipefd);
	void setConnected(bool value);
};
