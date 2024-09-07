#include "Server.hpp"
#include "Client.hpp"
#include <iostream>
#include <unistd.h>
#include <vector>

std::string to_lower(const std::string str)
{
	std::string result;
	for (unsigned long i = 0; i < str.length(); i++)
		result.push_back(std::tolower(str[i]));
	return result;
}

void char_arr_to_string(char** from, std::vector<std::string> &to, int n)
{
	for (int i = 0; i < n; i++)
		to[i] = from[i];
}

void wrong_args()
{
	std::cout << "unrecognized command, please type \"server <port>\" or \"client <ip> <port>\"" << std::endl;
	exit(0);
}

unsigned short get_port_num(std::string port)
{
	unsigned short port_num;
	try
	{
		port_num = std::stoi(port);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "Invalid portnumber" << std::endl;
		wrong_args();
	}
	return port_num;
}

void launch_client(std::string ip, std::string port)
{
	Client client;
	client.connect(ip, get_port_num(port));
}

void launch_server(std::string port)
{
	Server server(get_port_num(port));
	server.start();
	while (true)
	{
		std::cout << "hello from main" << std::endl;
		sleep(1);
	}
}

void process_args(std::vector<std::string> &args)
{
	std::string arg = to_lower(args[0]);
	if (arg == "client" || arg == "c")
	{
		if (args.size() < 3 || args[1].empty() || args[2].empty())
		{
			std::cout << "missing args" << std::endl;
			wrong_args();
		}

		std::cout << "Launching client..." << std::endl;
		launch_client(args[1], args[2]);
	}
	else if (arg == "server" || arg == "s")
	{
		if (args.size() < 2 || args[1].empty())
		{
			std::cout << "missing args" << std::endl;
			wrong_args();
		}

		std::cout << "Launching server..." << std::endl;
		launch_server(args[1]);
	}
	else
		wrong_args();
}

int main(int argc, char **argv)
{
	std::vector<std::string> str_args(argc - 1);
	char_arr_to_string(argv + 1, str_args, argc - 1);

	process_args(str_args);

	return 0;
}
