#pragma once
#include <network/TerminalClient.h>
#include"S2SSession.h"
#include"../Packet/Packet.h"
namespace neo::server
{
	class S2SClient : public neo::network::TerminalClient<S2SSession>
	{
	public:
		S2SClient(HANDLE* iocpHandle, const std::string& ip, int port)
			: TerminalClient<S2SSession>(iocpHandle, ip, port)
		{
			
		}

	public:
		void SendPacket(neo::packet::game::Packet& packet)
		{
			mTerminal->SendPacket(packet);
		}

		void SetProcess(std::shared_ptr<process::LogicProcess> process)
		{
			this->mTerminal->SetProcess(process);
		}
	private:
	};
}
