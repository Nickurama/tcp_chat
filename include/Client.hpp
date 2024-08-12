#pragma once
#include <string>

class Client
{
private:
	bool m_isConnected;
public:
	Client();
	void connect(const std::string ip, const int port);
	bool isConnected();
};
