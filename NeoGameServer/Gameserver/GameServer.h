#pragma once
#include<network/IOCPServer.h>
#include <network/SessionManager.h>
#include "WorldByProcess.h"
#include "GameSession.h"
namespace  neo::game
{
	class GameServer : public network::IOCPServer<GameSession>
	{
	public:
		GameServer();
		~GameServer() override;
	public:
		void OnCompleteInit() override;
		GameSession* OnAccept(network::TCPSocket* socket, network::SocketAddress* addrInfo) override;
		void UpdateServer() override;
	private:
		vector<WorldByProcess> mRegionByProcesses;
		GameSessionManagerPtr mSessionManager;
	};

}
