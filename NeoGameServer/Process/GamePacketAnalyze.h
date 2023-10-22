#pragma once
#include "../Packet/Packet.h"
#include <network/IOCPSession.h>
#include <system/InputMemoryStream.h>
#include <Singleton.h>
#include<optional>
namespace neo::process
{
	class GamePacketAnalyze : public Singleton<GamePacketAnalyze>
	{
	public:
		//
		std::optional<std::unique_ptr<packet::game::Package>> CreatePackage(
			const int& id,
			const int& size,
			neo::system::InputMemoryStream& stream,
			std::shared_ptr<neo::network::IOCPSession> session);

	private:
		std::optional<std::unique_ptr<packet::game::Packet>> CreatePacket(
			const int& id,
			const int& size,
			neo::system::InputMemoryStream& stream);
	};

}
