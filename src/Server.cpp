#include "Server.hpp"
#include "NetworkError.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <future>

Server::Server(unsigned short port)
{
	this->m_sockfd = socket();
	this->m_address = setupAddress(port);
	bind(m_sockfd, m_address);
	this->m_port = port;
	this->m_isRunning = false;
}

Server::~Server()
{
	close(m_sockfd);
}

struct sockaddr_in Server::setupAddress(unsigned short port)
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY = 0 -> to accept any address (any incoming address)
	addr.sin_port = htons(port); // htons converts from (little-endian/big-endian) -> big-endian, which is the byte order needed for port bytes.
	// CPUs, especially intel CPUs use little-endian
	return addr;
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
	std::cout << "Server: Starting server on port " << m_port << std::endl;
	listen();

	// int epollfd = epoll_create(0); // argument is ignored
	
	// struct epoll_event event;
	// event.events = EPOLLIN;
	// int status = epoll_ctl(epollfd, EPOLL_CTL_ADD, m_sockfd, &event);

	int clientSockfd = accept();
}

int Server::socket()
{
	int fd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
		throw NetworkError("Could not create server socket.");
	std::cout << "Server: socket created" << std::endl;
	return fd;
}

void Server::bind(int sockfd, sockaddr_in address)
{
	int status = ::bind(sockfd, (sockaddr *)&address, sizeof(m_address));
	if (status < 0)
		throw NetworkError("Could not bind to socket");
	std::cout << "Server: socket binded" << std::endl;
}

void Server::listen()
{
	int status = ::listen(m_sockfd, Server::LISTEN_BACKLOG);
	if (status < 0)
		throw NetworkError("Error when setting socket to listen");
	std::cout << "Server: Socket listening" << std::endl;
}

int Server::accept()
{
	socklen_t addrlen = sizeof(m_address);
	// std::future<int> futureClientSockfd = std::async(std::launch::async, ::accept, m_sockfd, (struct sockaddr *)&m_address, &addrlen);
	// onServerListening(); // call subscribers of server started listening
	// int clientSockfd = futureClientSockfd.get();

	int clientSockfd = ::accept(m_sockfd, (struct sockaddr *)&m_address, &addrlen);
	if (clientSockfd < 0)
		throw NetworkError("Error when accept new connection");
	std::cout << "Server: Socket accepted new connection!" << std::endl;
	return clientSockfd;
}
