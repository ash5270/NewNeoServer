#include <iostream>
#include "Gameserver/GameServer.h"

int main()
{
	HWND hWnd = GetConsoleWindow();
	SetWindowPos(hWnd, 0, 1920/2, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	neo::game::GameServer server;
	if (!server.InitializeServer(12239))
		return 0;

	server.StartServer();
	server.UpdateServer();
	server.StopServer();
	
	return 0;
}