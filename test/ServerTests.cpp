#include "doctest.hpp"
#include "NetworkError.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include <string>

TEST_CASE("Server should be connecteable")
{
	// Arrange
	std::string serverIP = "127.0.0.1";
	int serverPort = 70000;

	Server server(serverIP, serverPort);
	Client client;

	// Act
	bool threwError = false;
	try
	{
		server.start();
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

TEST_CASE("Should throw when unable to start server")
{
	// Arrange
	std::string serverIP = "127.0.0.1";
	int serverPort = 70000;

	Server server0(serverIP, serverPort);
	Server server1(serverIP, serverPort);

	server0.start();

	// Act
	bool threwError = false;
	try
	{
		server1.start();
	}
	catch (const NetworkError &e)
	{
		threwError = true;
	}

	// Assert
	CHECK(threwError == true);
	CHECK(server0.isRunning() == true);
	CHECK(server1.isRunning() == false);
}

TEST_CASE("Should increse number of connections")
{
	CHECK(false);
}
