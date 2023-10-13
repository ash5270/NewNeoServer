#pragma once
#include <network/IOCPServer.h>
#include <vector>

#include"TestSession.h"

using namespace neo::network;

namespace neo::test
{
	class TestServer :public IOCPServer
	{
	public:
		TestServer();
		~TestServer() override;
		IOCPSession* OnAccept(TCPSocket* socket, SocketAddress* addrInfo) override;
		void UpdateServer() override;

	private:
		std::vector<std::shared_ptr<TestSession>> mConnectionSessions;
	};
}


