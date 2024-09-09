#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <tuple>
#include <fcntl.h>
#include "Server.hpp"
#include "NetworkError.hpp"

using namespace Networking;

Server::Server(unsigned short port, int maxClients = 10)
	// : m_socket(makeSocket()),
	: m_sockfd(-1),
	m_address(setupAddress(port)),
	m_port(port),
	m_isRunning(false),
	m_allowNewConnections(true),
	m_thread(),
	m_maxClients(maxClients),
	m_epollMaxEvents(maxClients + 2), // + 2 = server event, pipe
	m_epollFd(-1),
	m_clients(2 * maxClients), // 2x to try to mitigate collisions at the cost of memory
	m_epollEventQueue(new struct epoll_event[m_epollMaxEvents]),
	m_epollServerEvent(new struct epoll_event),
	m_epollPipeStopEvent(new struct epoll_event)
{
	makePipe(m_pipeStopEvent);
	epollSetupPipeStopEvent();
}

Server::~Server()
{
	stop();
	closePipeStopEvent();
}

void Server::closePipeStopEvent()
{
	int statusRead = close(m_pipeStopEvent[0]);
	int statusWrite = close(m_pipeStopEvent[1]);

	if (statusRead < 0)
		std::cout << "Could not close read end of stop event pipe." << std::endl;
	std::cout << "Closed read end of stop event pipe." << std::endl;
	if (statusWrite < 0)
		std::cout << "Could not close read end of stop event pipe." << std::endl;
	std::cout << "Closed read end of stop event pipe." << std::endl;
}

void Server::makePipe(int *pipe)
{
	int status = ::pipe(pipe);
	if (status < 0)
		throw NetworkError("Could not create stop event pipe.");
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

unsigned short Server::port()
{
	return m_port;
}

// THREADING: CRITICAL SECTION
bool Server::isRunning() noexcept
{
	std::lock_guard<std::mutex> lock(m_isRunningMutex);
	return m_isRunning;
}

// THREADING: CRITICAL SECTION
void Server::setRunning(bool value) noexcept
{
	std::lock_guard<std::mutex> lock(m_isRunningMutex);
	m_isRunning = value;
}

// THREADING: CRITICAL SECTION
bool Server::allowNewConnections() noexcept
{
	std::lock_guard<std::mutex> lock(m_allowNewConnectionsMutex);
	return m_allowNewConnections;
}

// THREADING: CRITICAL SECTION
void Server::setAllowNewConnections(bool value) noexcept
{
	std::lock_guard<std::mutex> lock(m_allowNewConnectionsMutex);
	m_allowNewConnections = value;
}

// THREADING: CRITICAL SECTION
int Server::numConnections()
{
	std::lock_guard<std::mutex> lock(m_clientsMutex);
	return m_clients.size();
}

// THREDING: joins the server thread
void Server::stop() noexcept
{
	if (!isRunning())
		return;

	std::cout << "Stopping server..." << std::endl;

	setAllowNewConnections(false);
	disconnectAll();
	triggerPipeStopEvent();
	m_thread.join();
	setRunning(false); // sets running to false after disconnecting everyone
	closeEpollFd();
	closeServerFd();
}

void Server::triggerPipeStopEvent()
{
	char buf = 1;
	int status = write(m_pipeStopEvent[1], &buf, sizeof(char));
	if (status < 0)
		std::cout << "failed to write to pipe (stop event)" << std::endl;
}

void Server::closeEpollFd()
{
	try
	{
		closefd(m_epollFd);
	}
	catch (NetworkError& e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "Epoll file descriptor didn't close correctly." << std::endl;
	}

	m_epollFd = -1;
	m_epollServerEvent.reset(new struct epoll_event);
}

void Server::closeServerFd()
{
	try
	{
		closefd(m_sockfd);
	}
	catch (NetworkError& e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "Server socket didn't close correctly." << std::endl;
	}
	m_sockfd = -1;
}

// THREADING: CRITICAL SECTION
void Server::disconnect(int fd)
{
	std::lock_guard<std::mutex> lock(m_clientsMutex);

	if (!isRunning())
		return;

	if (m_clients.find(fd) != m_clients.end())
		m_clients.erase(fd);
	// TODO: Send disconnect message to user
	closefd(fd);
}

// THREADING: CRITICAL SECTION
void Server::disconnectAll()
{
	std::lock_guard<std::mutex> lock(m_clientsMutex);

	if (!isRunning())
		return;

	std::unordered_map<int, std::tuple<std::unique_ptr<struct epoll_event>, std::unique_ptr<struct sockaddr_in>>>::iterator it;
	for (it = m_clients.begin(); it != m_clients.end(); )
	{
		closefd(it->first);
		it = m_clients.erase(it); // it++, as it now points to where the deleted object pointed to
	}
}

void Server::closefd(int fd)
{
	int status = close(fd);
	if (status < 0)
		throw NetworkError("Could not close file descriptor.");
	std::cout << "Closed a file descriptor" << std::endl;
}

// THREDING: starts the server thread
void Server::start()
{
	if (isRunning())
		return;

	// start socket
	m_sockfd = makeSocket();

	bind(m_sockfd, m_address);
	listen(m_sockfd);
	setNonblocking(m_sockfd);

	std::cout << "Server: Starting server on port " << m_port << std::endl;

	// start epoll instance
	m_epollFd = makeEpoll();
	epollAddPipeStop();
	epollSetupServerEvent();
	epollAddServer();

	// start thread
	setRunning(true);
	setAllowNewConnections(true);
	m_thread = std::thread(&Server::runServerLoop, this);
}

void Server::setNonblocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	if (flags < 0)
		throw NetworkError("could not get flags from file descriptor.");
	
	int status = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
	if (status < 0)
		throw NetworkError("could not set flags of file descriptor.");
}

void Server::epollSetupPipeStopEvent()
{
	m_epollPipeStopEvent->events = EPOLLIN;
	m_epollPipeStopEvent->data.fd = m_pipeStopEvent[0];
}

void Server::epollAddPipeStop()
{
	int status = epoll_ctl(m_epollFd, EPOLL_CTL_ADD, m_pipeStopEvent[0], m_epollPipeStopEvent.get());
	if (status < 0)
		throw NetworkError("Could not add pipe file descriptor to epoll instance.");
}

// needs m_sockfd to be set
void Server::epollSetupServerEvent()
{
	m_epollServerEvent->events = EPOLLIN;
	m_epollServerEvent->data.fd = m_sockfd;
}

// needs epoll, socket and event
void Server::epollAddServer()
{
	int status = epoll_ctl(m_epollFd, EPOLL_CTL_ADD, m_sockfd, m_epollServerEvent.get());
	if (status < 0)
		throw NetworkError("Could not add server file descriptor to epoll instance.");
}

// THREADING: ran on a different thread
void Server::runServerLoop()
{
	int eventsReady = 0;
	bool shouldStop = false;
	while (!shouldStop)
	{
		eventsReady = epoll_wait(m_epollFd, m_epollEventQueue.get(), m_epollMaxEvents, 1000);

		if (eventsReady < 0)
		{
			std::cout << "epoll: encountered an error while waiting." << std::endl;
			continue;
		}
		else if (eventsReady == 0)
		{
			std::cout << "epoll: nothing to do." << std::endl;
			continue;
		}


		std::cout << "epoll: events detected." << std::endl;
		shouldStop = processEvents(eventsReady);
	}
}

// returns if pipe stop event was triggered.
bool Server::processEvents(int eventsReady)
{
	bool shouldStop = false;
	for (int i = 0; i < eventsReady; i++)
	{
		int currFd = m_epollEventQueue[i].data.fd;

		if (currFd == m_pipeStopEvent[0]) // stop signal
		{
			std::cout << "epoll: pipe stop event detected!" << std::endl;
			consumePipeStopEvent();
			shouldStop = true;
			break;
		}
		else if (currFd == m_sockfd && allowNewConnections()) // new connection
		{
			std::cout << "epoll: socket new connection event detected!" << std::endl;
			acceptConnection();
			continue;
		}

		// received message
		std::cout << "epoll: socket data received event detected!" << std::endl;
		receiveMessage(currFd);
	}
	return shouldStop;
}

void Server::consumePipeStopEvent()
{
	char tmp;
	read(m_pipeStopEvent[0], &tmp, 1);
}

// THREADING: CRITICAL SECTION
void Server::acceptConnection()
{
	// client addr
	std::unique_ptr<struct sockaddr_in> clientAddr(new struct sockaddr_in);
	int clientFd = accept(m_sockfd, *(clientAddr.get()));
	if (clientFd < 0)
	{
		std::cout << "Error on accepting connection." << std::endl;
		return;
	}
	setNonblocking(clientFd);

	// client event
	std::unique_ptr<struct epoll_event> clientEvent(new struct epoll_event);
	clientEvent->events = EPOLLIN;
	clientEvent->data.fd = clientFd;

	// save to hashmap
	std::lock_guard<std::mutex> lock(m_clientsMutex);

	m_clients[clientFd] = std::make_tuple(std::move(clientEvent), std::move(clientAddr));
}

void Server::receiveMessage(int fd)
{
	// TODO
}

int Server::makeEpoll()
{
	int fd = epoll_create1(0);
	if (fd < 0)
		throw NetworkError("Could not create epoll instance.");
	return fd;
}

int Server::makeSocket()
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);
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

void Server::listen(int sockfd)
{
	int status = ::listen(sockfd, Server::LISTEN_BACKLOG);
	if (status < 0)
		throw NetworkError("Error when setting socket to listen");
	std::cout << "Server: Socket listening" << std::endl;
}

int Server::accept(int sockfd, sockaddr_in& address)
{
	socklen_t addrlen = sizeof(m_address);
	int clientSockfd = ::accept(sockfd, (struct sockaddr *)&address, &addrlen);
	if (clientSockfd < 0)
		throw NetworkError("Error when accept new connection");
	std::cout << "Server: Socket accepted new connection!" << std::endl;
	return clientSockfd;
}
