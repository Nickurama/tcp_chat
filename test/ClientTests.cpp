#include "../include/doctest.hpp"
#include "NetworkError.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include <string>

TEST_CASE("Should connect to server")
{
	// Arrange
	std::string serverIP = "127.0.0.1";
	int serverPort = 70000;

	Server server(serverIP, serverPort);
	Client client;

	server.start();

	// Act
	bool threwError = false;
	try
	{
		client.connect(serverIP, serverPort);
	}
	catch (const NetworkError &e)
	{
		threwError = true;
	}

	// Assert
	CHECK(threwError == false);
	CHECK(client.isConnected() == true);
	CHECK(server.isRunning() == true);
	CHECK(server.numConnections() == 1);
}	

TEST_CASE("Should throw when unable to connect")
{
	// Arrange
	std::string serverIP = "127.0.0.1";
	int serverPort = 70000;
	int connectPort = 69999;

	Server server(serverIP, serverPort);
	Client client;

	server.start();

	// Act
	bool threwError = false;
	try
	{
		client.connect(serverIP, connectPort);
	}
	catch (const NetworkError &e)
	{
		threwError = true;
	}

	// Assert
	CHECK(threwError == true);
	CHECK(client.isConnected() == false);
	CHECK(server.isRunning() == true);
	CHECK(server.numConnections() == 0);
}
