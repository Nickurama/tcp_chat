#pragma once
#include <mutex>
#include <netinet/in.h>
#include <thread>
#include <unordered_map>

namespace Networking
{
	class Server
	{
	public:
		explicit Server(unsigned short port, int maxClients);
		~Server();

		unsigned short port();
		bool isRunning() noexcept;
		int numConnections();

		void start();
		void stop() noexcept;

	private:
		static const int LISTEN_BACKLOG = 5;

		// member variables
		int m_sockfd;
		struct sockaddr_in m_address;
		unsigned short m_port;
		std::mutex m_isRunningMutex;
		bool m_isRunning;
		std::mutex m_allowNewConnectionsMutex;
		bool m_allowNewConnections;
		std::thread m_thread;
		int m_pipeStopEvent[2];
		const int m_maxClients;
		const int m_epollMaxEvents;
		int m_epollFd;
		std::mutex m_clientsMutex;
		std::unordered_map<int, std::tuple<std::unique_ptr<struct epoll_event>, std::unique_ptr<struct sockaddr_in>>> m_clients;
		std::unique_ptr<struct epoll_event[]> m_epollEventQueue;
		std::unique_ptr<struct epoll_event> m_epollServerEvent;
		std::unique_ptr<struct epoll_event> m_epollPipeStopEvent;

		// no copying or assignment permitted
		Server(const Server&) = delete;
		Server& operator=(const Server&) = delete;

		// utility functions
		static struct sockaddr_in setupAddress(unsigned short port);
		static void bind(int sockfd, struct sockaddr_in address);
		static void listen(int sockfd);
		static int accept(int sockfd, sockaddr_in& address);
		static void closefd(int fd);
		static int makeSocket();
		static int makeEpoll();
		static void makePipe(int *pipe);
		void closePipeStopEvent();
		void closeEpollFd();
		void closeServerFd();
		void epollSetupServerEvent();
		void epollAddServer();
		void triggerPipeStopEvent();
		void epollSetupPipeStopEvent();
		void epollAddPipeStop();

		// functions
		void setRunning(bool value) noexcept;
		bool allowNewConnections() noexcept;
		void setAllowNewConnections(bool value) noexcept;
		void disconnect(int fd);
		void disconnectAll();
		void runServerLoop();
		void acceptConnection();
		void receiveMessage(int fd);
	};
}
