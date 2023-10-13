#include "DBServer.h"

#include "../DB/ConnectionPool.h"
#include "../DB/MYSQLConnectionPool.h"
#include "../DB/MYSqlConnection.h"



neo::server::DBServer::DBServer() :IOCPServer<DBSession>(L"DBServer")
{
	mProcess = std::make_shared<process::DBPacketProcess>();
	
}

neo::server::DBServer::~DBServer()
{

}

neo::server::DBSession* neo::server::DBServer::OnAccept(neo::network::TCPSocket* socket, neo::network::SocketAddress* addrInfo)
{
	auto session = make_shared<DBSession>();
	session->OnAccept(socket, addrInfo);
	mSessions.push_back(session);
	session->SetProcess(mProcess);
	return session.get();
}

void neo::server::DBServer::UpdateServer()
{
	system::LogSystem::GetInstance().Update();
	//IOCPServer<OtherServerSession>::UpdateServer();
}



void neo::server::DBServer::OnCompleteInit()
{
	LOG_PRINT(LOG_LEVEL::LOG_INFO, L"Connecting MySql...\n");
	db::MYSQLConnectionPool::GetInstance().Init(10);
}
