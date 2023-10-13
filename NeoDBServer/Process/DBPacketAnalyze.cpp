#include "DBPacketAnalyze.h"

std::optional<std::unique_ptr<neo::packet::db::Package>> neo::process::DBPacketAnalyze::CreatePackage(const int& id, const int& size,
	neo::system::InputMemoryStream& stream, std::shared_ptr<neo::network::IOCPSession> session)
{
	auto packetOpt = CreatePacket(id, size, stream);
	if (packetOpt.has_value())
	{
		auto creatPackage = std::make_unique<neo::packet::db::Package>();
		creatPackage->packet = std::move(packetOpt.value());
		creatPackage->session = session;
		return std::move(creatPackage);
	}
	else
	{
		return std::nullopt;
	}
}

std::optional<std::unique_ptr<neo::packet::db::Packet>> neo::process::DBPacketAnalyze::CreatePacket(const int& id, const int& size,
	neo::system::InputMemoryStream& stream)
{
	switch (packet::db::PacketID packet = static_cast<packet::db::PacketID>(id); packet)
	{
	case packet::db::PacketID::PI_S_REQ_DB_LOGIN:
	{
		std::unique_ptr<neo::packet::db::Packet> createPacket =
			std::make_unique<packet::db::P_S_REQ_DB_LOGIN>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}
	case packet::db::PacketID::PI_S_REQ_DB_CHANNEL_INFO:
	{
		std::unique_ptr<neo::packet::db::Packet> createPacket =
			std::make_unique<packet::db::P_S_REQ_DB_CHANNEL_INFO>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}
	case packet::db::PacketID::PI_S_REQ_DB_CHAR_DATA:
	{
		std::unique_ptr<neo::packet::db::Packet> createPacket =
			std::make_unique<packet::db::P_S_REQ_DB_CHAR_DATA>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}
	case packet::db::PacketID::PI_S_REQ_DB_ENTER_INGAME_CHAR_DATA:
	{
		std::unique_ptr<neo::packet::db::Packet> createPacket =
			std::make_unique<packet::db::P_S_REQ_DB_ENTER_INGAME_CHAR_DATA>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}
	case packet::db::PacketID::PI_S_REQ_DB_WORLD_MAP_INFO:
	{
		std::unique_ptr<neo::packet::db::Packet> createPacket =
			std::make_unique<packet::db::P_S_REQ_DB_WORLD_MAP_INFO>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}


	default:
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"not found packet id = %d\n", id);
		return std::nullopt;
	}
}
