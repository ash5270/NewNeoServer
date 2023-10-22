#pragma once
//
//패킷의 id를 확인하여 packet을 만들어주는 곳 
//
#include <optional>

#include "../Packet/PacketData.h"
#include <network/IOCPSession.h>
#include <system/InputMemoryStream.h>
#include <Singleton.h>
namespace neo::process
{
	class PacketAnalyze :public Singleton<PacketAnalyze> 
	{
	public:
		//
		std::optional<std::unique_ptr<packet::login::Package>> CreatePackage(
			const int& id,
			const int& size,
			neo::system::InputMemoryStream& stream,
			std::shared_ptr<neo::network::IOCPSession> session);


	private:
		optional<std::unique_ptr<packet::login::Packet>> CreatePacket(
			const int& id,
			const int& size,
			neo::system::InputMemoryStream& stream);
	};
}
