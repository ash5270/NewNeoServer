#include "GameServer.h"
#include "S2SManager.h"
#include <network/SessionManager.h>
neo::game::GameServer::GameServer():neo::network::IOCPServer<neo::game::GameSession>(L"GameServer")
{
	mSessionManager = std::make_shared<network::SessionManager<GameSession>>();
	for(int i=0; i<1; i++)
	{
		mRegionByProcesses.push_back({ mSessionManager });
	}
}

neo::game::GameServer::~GameServer()
{
	mRegionByProcesses.clear();
} 

void neo::game::GameServer::OnCompleteInit()
{
	//IOCPServer<GameSession>::OnCompleteInit();
	server::S2SManager::GetInstance().AddS2SClient(L"DBServer", &mIOCPHandle, "127.0.0.1", 6559);
	server::S2SManager::GetInstance().GetClient(L"DBServer")->lock()->SetProcess(this->mRegionByProcesses[0].LogicProcess);

	for(int i = 0; i < mRegionByProcesses.size(); i++)
	{
		mRegionByProcesses[i].Start();
	}
}

neo::game::GameSession* neo::game::GameServer::OnAccept(network::TCPSocket* socket, network::SocketAddress* addrInfo)
{
	const auto session = mSessionManager->CreateSession();
	if(session.expired())
		return nullptr;
	session.lock()->OnAccept(socket, addrInfo);
	session.lock()->SetProcess(mRegionByProcesses[0].LogicProcess);
	return session.lock().get();
}

void neo::game::GameServer::UpdateServer()
{
	//IOCPServer<GameSession>::UpdateServer();
	system::LogSystem::GetInstance().Update();
}
