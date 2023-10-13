#include "TestServer.h"

neo::test::TestServer::TestServer() : IOCPServer()
{
}

neo::test::TestServer::~TestServer()
{
}

IOCPSession* neo::test::TestServer::OnAccept(TCPSocket* socket, SocketAddress* addrInfo)
{
	auto newSession = std::make_shared<neo::test::TestSession>();
	newSession->OnAccept(socket, addrInfo);
	mConnectionSessions.push_back(newSession);
	return newSession.get();
}

void neo::test::TestServer::UpdateServer()
{
	system::LogSystem::GetInstance().Update();
}
