#include "doctest.hpp"
#include "NetworkError.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include <iostream>
#include <string>
#include <thread>

// TEST_CASE("Server should be connecteable")
// {
// 	// Arrange
// 	std::string serverIP = "127.0.0.1";
// 	unsigned short serverPort = 50000;
//
// 	Server server(serverPort);
// 	Client client;
//
// 	// Act
// 	bool threwError = false;
// 	std::thread serverTh;
// 	try
// 	{
// 		// server.start();
// 		serverTh = std::thread(&Server::start, &server);
// 		client.connect(serverIP, serverPort);
// 	}
// 	catch (const NetworkError &e)
// 	{
// 		std::cout << e.what() << std::endl;
// 		threwError = true;
// 	}
// 	serverTh.join();
//
// 	// Assert
// 	CHECK(threwError == false);
// 	CHECK(client.isConnected() == true);
// 	CHECK(server.isRunning() == true);
// 	CHECK(server.numConnections() == 1);
// }
//
// TEST_CASE("Should throw when unable to start server")
// {
// 	// Arrange
// 	unsigned short serverPort = 50000;
//
// 	Server server0(serverPort);
//
// 	server0.start();
//
// 	// Act
// 	bool threwError = false;
// 	try
// 	{
// 		Server server1(serverPort);
// 		server1.start();
// 	}
// 	catch (const NetworkError &e)
// 	{
// 		threwError = true;
// 	}
//
// 	// Assert
// 	CHECK(threwError == true);
// 	CHECK(server0.isRunning() == true);
// 	// CHECK(server1.isRunning() == false);
// }
//
// TEST_CASE("Should increse number of connections")
// {
// 	CHECK(false);
// }
