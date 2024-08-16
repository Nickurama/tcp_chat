#include "Client.hpp"
#include "NetworkError.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

Client::Client()
{
	this->m_sockfd = socket();
	this->m_isConnected = false;
}

Client::~Client()
{
	close(this->m_sockfd);
}

void Client::connect(const std::string ip, unsigned short port)
{
	std::cout << "Client: Connecting to server on port " << port << std::endl;
	connectSocket(setupServerAddr(ip, port));
	m_isConnected = true;
}

int Client::socket()
{
	int fd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
		throw NetworkError("Could not create client socket");
	std::cout << "Client: socket created" << std::endl;
	return fd;
}

struct sockaddr_in Client::setupServerAddr(const std::string ip, unsigned short port)
{
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr = stringToAddr(ip);
	return serverAddr;
}

struct in_addr Client::stringToAddr(const std::string addrStr)
{
	struct in_addr addr;
	int status = inet_pton(AF_INET, addrStr.c_str(), &addr);
	if (status < 0)
		throw NetworkError("Invalid ip string");
	return addr;
}

void Client::connectSocket(const struct sockaddr_in serverAddr)
{
	int status = ::connect(m_sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	if (status < 0)
		throw NetworkError("Could not connect to server");
	std::cout << "Client: connected to server" << std::endl;
}

bool Client::isConnected()
{
	return m_isConnected;
}
