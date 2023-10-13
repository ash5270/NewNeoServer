#pragma once
#include<network/IOCPSession.h>
#include "../Process/DBPacketAnalyze.h"
#include "../Process/DBPacketProcess.h"
namespace neo::server
{
	class DBSession : public neo::network::IOCPSession
	{
	public:
		DBSession();
		~DBSession();
		bool OnAccept(neo::network::TCPSocket* socket, neo::network::SocketAddress* addrInfo) override;
		void OnSend(size_t transferSize) override;
		void OnRecv(size_t transferSize) override;

		void SetProcess(const std::shared_ptr<process::DBPacketProcess>& process)
		{
			mProcess = process;
		}
		void SendPacket(neo::packet::db::Packet& packet);
	private:
		std::shared_ptr<process::DBPacketProcess> mProcess;
		size_t mRecvRemainSize = {};
	};
}

