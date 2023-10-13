#pragma once
#include <network/IOCPSession.h>
using namespace neo::network;

namespace neo::test
{
	class TestSession : public IOCPSession
	{
	public:
		bool OnAccept(TCPSocket* socket, SocketAddress* addrInfo) override;
		void OnSend(size_t transferSize) override;
		void OnRecv(size_t transferSize) override;

		void SendBuffer();
	private:
		std::atomic<size_t> mRecvTotalSize;
	};

}

