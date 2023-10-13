#include"DBServer/DBServer.h"
#include<Windows.h>

int main()
{
	HWND hWnd = GetConsoleWindow();
	SetWindowPos(hWnd, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	neo::server::DBServer server; 
	server.InitializeServer(6559,4);
	server.StartServer();
	server.UpdateServer();
	server.StopServer();
	return 0;
}