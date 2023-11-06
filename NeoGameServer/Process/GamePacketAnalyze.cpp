#include "GamePacketAnalyze.h"
#include "../Packet/PacketData.h"
std::optional<std::unique_ptr<neo::packet::game::Package>> neo::process::GamePacketAnalyze::CreatePackage(const int& id,
	const int& size, neo::system::InputMemoryStream& stream, std::shared_ptr<neo::network::IOCPSession> session)
{

	auto packetOpt = CreatePacket(id, size, stream);
	if (packetOpt.has_value())
	{
		auto creatPackage = std::make_unique<neo::packet::game::Package>();
		creatPackage->packet = std::move(packetOpt.value());
		creatPackage->session = session;
		return std::move(creatPackage);
	}
	else
	{
		return std::nullopt;
	}
}

std::optional<std::unique_ptr<neo::packet::game::Packet>> neo::process::GamePacketAnalyze::CreatePacket(const int& id,
	const int& size, neo::system::InputMemoryStream& stream)
{
	switch (packet::game::PacketID packet = static_cast<packet::game::PacketID>(id); packet)
	{

	case packet::game::PacketID::PI_C_REQ_WORLD_ENTER_THE_SERVER:
	{
		std::unique_ptr<neo::packet::game::Packet> createPacket =
			std::make_unique<packet::game::P_C_REQ_WORLD_ENTER_THE_SERVER>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}

	case packet::game::PacketID::PI_S_RES_DB_ENTER_INGAME_CHAR_DATA:
	{
		std::unique_ptr<neo::packet::game::Packet> createPacket =
			std::make_unique<packet::game::P_S_RES_DB_ENTER_INGAME_CHAR_DATA>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}

	case packet::game::PacketID::PI_S_RES_WORLD_PLAYER_DATA:
	{
		std::unique_ptr<neo::packet::game::Packet> createPacket =
			std::make_unique<packet::game::P_S_RES_WORLD_PLAYER_DATA>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}

	case packet::game::PacketID::PI_C_UPDATE_CHAR_POSITION:
	{
		std::unique_ptr<neo::packet::game::Packet> createPacket =
			std::make_unique<packet::game::P_C_UPDATE_CHAR_POSITION>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}

	case packet::game::PacketID::PI_S_RES_DB_WORLD_MAP_INFO:
	{
		std::unique_ptr<neo::packet::game::Packet> createPacket =
			std::make_unique<packet::game::P_S_RES_DB_WORLD_MAP_INFO>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}

	case packet::game::PacketID::PI_C_REQ_LEAVE_MAP:
	{
		std::unique_ptr<neo::packet::game::Packet> createPacket =
			std::make_unique<packet::game::P_C_REQ_LEAVE_MAP>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}

	case packet::game::PacketID::PI_C_NOTIFY_PING:
	{
		std::unique_ptr<neo::packet::game::Packet> createPacket =
			std::make_unique<packet::game::P_C_NOTIFY_PING>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}

	case packet::game::PacketID::PI_C_NOTIFY_RTT:
	{
		std::unique_ptr<neo::packet::game::Packet> createPacket =
			std::make_unique<packet::game::P_C_NOTIFY_RTT>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}

	case packet::game::PacketID::PI_C_REQ_PLAYER_ATTACK:
	{
		std::unique_ptr<neo::packet::game::Packet> createPacket =
			std::make_unique<packet::game::P_C_REQ_PLAYER_ATTACK>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}



	/*case packet::game::PacketID::PI_C_REQ_ENTER_MAP:
	{
		std::unique_ptr<neo::packet::game::Packet> createPacket =
			std::make_unique<packet::game::P_C_NOTIFY_LEAVE_MAP>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}*/

	default:
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"not found packet id = %d\n", id);
		return std::nullopt;
	}
}
