#include "Server.hpp"
#include "NetworkError.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>

Server::Server(const std::string ip, const unsigned short port)
{
	this->m_ip = ip;
	this->m_port = port;
	this->m_isRunning = false;
	setupAddress(port);

}

void Server::setupAddress(unsigned short port)
{
	this->m_address.sin_family = AF_INET;
	this->m_address.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY = 0 -> to accept any address (any incoming address)
	this->m_address.sin_port = htons(port); // htons converts from (little-endian/big-endian) -> big-endian, which is the byte order needed for port bytes.
	// CPUs, especially intel CPUs use little-endian
}

std::string Server::getIp()
{
	return m_ip;
}

unsigned short Server::getPort()
{
	return m_port;
}

bool Server::isRunning()
{
	return m_isRunning;
}

int Server::numConnections()
{
	return 1; // TODO
}

void Server::start()
{
	int sockfd = socket();
	bind(sockfd);
	listen(sockfd);
	int clientSockfd = accept(sockfd);
}

int Server::socket()
{
	int sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		throw NetworkError("Could not create socket.");
	std::cout << "Socket created" << std::endl;
	return sockfd;
}

void Server::bind(int sockfd)
{
	int bindStat = ::bind(sockfd, (sockaddr *)&m_address, sizeof(m_address));
	if (bindStat < 0)
		throw NetworkError("Could not bind to socket");
	std::cout << "Socket binded" << std::endl;
}

void Server::listen(int sockfd)
{
	int listenStat = ::listen(sockfd, Server::LISTEN_BACKLOG);
	if (listenStat < 0)
		throw NetworkError("Error when setting socket to listen");
	std::cout << "Socket listening" << std::endl;
}

int Server::accept(int sockfd)
{
	socklen_t addrlen = sizeof(m_address);
	int clientSockfd = ::accept(sockfd, (struct sockaddr *)&m_address, &addrlen);
	if (clientSockfd < 0)
		throw NetworkError("Error when accept new connection");
	std::cout << "Socket accepted new connection!" << std::endl;
	return clientSockfd;
}
