#pragma once
#include <network/Terminal.h>
#include <packetprocess/LogicProcess.h>
#include "../Packet/Packet.h"
namespace neo::server
{
	class S2SSession : public neo::network::Terminal
	{
	public:
		void OnClose() override;
		~S2SSession() override;
		bool OnAccept(network::TCPSocket* socket, network::SocketAddress* addrInfo) override;
		void OnSend(size_t transferSize) override;
		void OnRecv(size_t transferSize) override;
	public:
		void SendPacket(neo::packet::game::Packet& packet);
		void SetProcess(const std::shared_ptr<process::LogicProcess>& process);
	private:
		std::shared_ptr<process::LogicProcess> mProcess;
		size_t mRecvRemainSize = {};
	};
}
