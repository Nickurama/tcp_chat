#include "Client.hpp"
#include "NetworkError.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <thread>
#include <unistd.h>

Client::Client(int connAttempts, int attemptTimeoutMs)
	: m_isConnected(false),
	m_receiveThread(),
	m_sockfd(-1),
	m_connAttempts(connAttempts),
	m_attemptTimeoutMs(attemptTimeoutMs)
{
	makePipe(m_pipeStopEvent);
}

Client::Client() : Client(DEFAULT_CONN_ATTEMPTS, DEFAULT_ATTEMPT_TIMEOUT) {}

Client::~Client()
{
	disconnect();
}

void Client::makePipe(int *pipe)
{
	int status = ::pipe(pipe);
	if (status < 0)
		throw NetworkError("Could not create stop event pipe.");
}

void Client::connect(const std::string& ip, unsigned short port)
{
	if (isConnected())
		return;

	m_sockfd = socket();
	std::cout << "Client: Connecting to server on port " << port << std::endl;
	struct sockaddr_in serverAddr = setupServerAddr(ip, port);
	connectSocket(m_sockfd, serverAddr, m_connAttempts, m_attemptTimeoutMs);
	setConnected(true);
	m_receiveThread = std::thread(&Client::startReceiving, this, m_sockfd, m_pipeStopEvent[0]);
}

void Client::disconnect()
{
	if (!isConnected())
		return;

	setConnected(false);
	close(m_sockfd);
	// TODO
}

void Client::startReceiving(int sockfd, int pipefd)
{
	static const int POLL_NUM_FDS = 2; // socket and pipe
	static const int POLL_TIMEOUT = 1000; // socket and pipe
	std::unique_ptr<struct pollfd[]> fds(new struct pollfd[POLL_NUM_FDS]);
	// setup pipe event
	fds[0].fd = pipefd;
	fds[0].events = POLLIN;
	// setup socket receive event
	fds[1].fd = sockfd;
	fds[1].events = POLLIN;

	bool shouldStop = false;
	while (!shouldStop)
	{
		int nTriggers = poll(fds.get(), POLL_NUM_FDS, POLL_TIMEOUT);
		if (nTriggers < 0)
		{
			std::cout << "poll: unknown error!" << std::endl;
			continue;
		}

		if (nTriggers == 0)
		{
			std::cout << "poll: nothing to do." << std::endl;
			continue;
		}

		if (fds[0].revents & POLLIN) // pipe stop event
		{
			shouldStop = true;
			continue;
		}
		else if (fds[1].revents & POLLIN) // socket received data
		{

		}
	}
}

int Client::socket()
{
	int fd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
		throw NetworkError("Could not create client socket");
	std::cout << "Client: socket created" << std::endl;
	return fd;
}

struct sockaddr_in Client::setupServerAddr(const std::string& ip, unsigned short port)
{
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr = stringToAddr(ip);
	return serverAddr;
}

struct in_addr Client::stringToAddr(const std::string& addrStr)
{
	struct in_addr addr;
	int status = inet_pton(AF_INET, addrStr.c_str(), &addr);
	if (status < 0)
		throw NetworkError("Invalid ip string");
	return addr;
}

void Client::connectSocket(int sockfd, const struct sockaddr_in serverAddr,
						   int connAttempts, int attemptTimeoutMs)
{
	int status = ::connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

	for (int i = 1; i < connAttempts && status < 0; i++)
	{
		std::cout << "Connection failed! retrying..." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(attemptTimeoutMs));
		status = ::connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	}

	if (status < 0)
		throw NetworkError("Could not connect to server");

	std::cout << "Client: connected to server" << std::endl;
}

// THREADING: CRITICAL SECTION
void Client::setConnected(bool value)
{
	std::lock_guard<std::mutex> lock(m_isConnectedMutex);
	m_isConnected = value;
}

// THREADING: CRITICAL SECTION
bool Client::isConnected()
{
	std::lock_guard<std::mutex> lock(m_isConnectedMutex);
	return m_isConnected;
}
