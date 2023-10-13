#include "LoginServer.h"
#include "S2SManager.h"

neo::server::LoginServer::LoginServer() : IOCPServer<neo::server::LoginSession>(L"LoginServer")
{
	mSessionManager = std::make_shared<SessionManager<neo::server::LoginSession>>();
	mLoginProcess = std::make_shared<neo::process::LoginProcess>(mSessionManager);
}

neo::server::LoginServer::~LoginServer()
{
}

neo::server::LoginSession* neo::server::LoginServer::OnAccept(TCPSocket* socket, SocketAddress* addrInfo)
{
	const auto session = mSessionManager->CreateSession();
	session.lock()->OnAccept(socket, addrInfo);
	//process setting
	session.lock()->SetProcess(mLoginProcess);
	session.lock()->SetServer(this);
	return session.lock().get();
}

void neo::server::LoginServer::OnCompleteInit()
{
	//IOCPServer<LoginSession>::OnCompleteInit();
	S2SManager::GetInstance().AddS2SClient(L"DBServer", &mIOCPHandle, "127.0.0.1", 6559);
	S2SManager::GetInstance().GetClient(L"DBServer")->lock()->SetProcess(this->mLoginProcess);
}

std::shared_ptr<SessionManager<neo::server::LoginSession>> neo::server::LoginServer::GetSessionManager()
{
	return mSessionManager;
}

void neo::server::LoginServer::UpdateServer()
{
	system::LogSystem::GetInstance().Update();
}
