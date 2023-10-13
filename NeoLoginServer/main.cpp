#include"LoginServer/LoginServer.h"
#include"LoginServer/LoginSession.h"

int main()
{
	HWND hWnd = GetConsoleWindow();
	SetWindowPos(hWnd, 0, 0,1080/2, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	neo::server::LoginServer loginServer;
	loginServer.InitializeServer(6889);
	loginServer.StartServer();
	loginServer.UpdateServer();
	loginServer.CloseServer();
	return 0; 
} 