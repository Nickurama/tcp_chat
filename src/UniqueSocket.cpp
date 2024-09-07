#include "UniqueSocket.hpp"
#include <iostream>
#include <unistd.h>

UniqueSocket::UniqueSocket(int sockFd) : m_fd(sockFd)
{
	std::cout << "Unique Socket created!" << std::endl;
}

UniqueSocket::~UniqueSocket()
{
	// !!! LOG POTENTIAL ERRORS !!!
	std::cout << "Unique Socket destroyed!" << std::endl;
	close(m_fd);
}

int UniqueSocket::get() const
{
	return m_fd;
}

UniqueSocket::operator int() const
{
	return m_fd;
}
