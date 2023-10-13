#include "Server/TestServer.h"
#include <iostream>

using namespace neo::test;

int main()
{
	int x = 0;
	TestServer server;
	if (!server.InitializeServer(6889))
		return 0;

	server.StartServer();
	server.UpdateServer();
	server.StopServer();
	return 0;
}