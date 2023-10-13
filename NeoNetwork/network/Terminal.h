#pragma once
#include "IOCPSession.h"
namespace neo::network
{
	class Terminal : public IOCPSession
	{
	public:
		Terminal();
		~Terminal() override;
		bool OnAccept(TCPSocket* socket, SocketAddress* addrInfo) override;
		void OnSend(size_t transferSize) override;
		void OnRecv(size_t transferSize) override;
	};
}

