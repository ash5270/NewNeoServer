#pragma once
#include <network/IOCPSession.h>
#include <system/Buffer.h>
using namespace neo::network;

namespace  neo::test
{
	class TestSession : public IOCPSession
	{
	public:
		TestSession();
		~TestSession();

	public:
		bool OnAccept(TCPSocket* socket, SocketAddress* addrInfo) override;
		void OnSend(size_t transferSize) override;
		void OnRecv(size_t transferSize) override;

		void SendTestData();

	};

}

