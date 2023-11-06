#include "PacketAnalyze.h"

std::optional<std::unique_ptr<neo::packet::login::Package>> neo::process::PacketAnalyze::CreatePackage(const int& id, const int& size,
	neo::system::InputMemoryStream& stream, std::shared_ptr<neo::network::IOCPSession> session)
{
	auto packetOpt = CreatePacket(id, size, stream);
	if (packetOpt.has_value())
	{
		auto creatPackage = std::make_unique<neo::packet::login::Package>();
		creatPackage->packet = std::move(packetOpt.value());
		creatPackage->session = session;
		return std::move(creatPackage);
	}
	else
	{
		return std::nullopt;
	}
}

std::optional<std::unique_ptr<neo::packet::login::Packet>> neo::process::PacketAnalyze::CreatePacket(const int& id, const int& size,
	neo::system::InputMemoryStream& stream)
{
	switch (packet::login::PacketID packet = static_cast<packet::login::PacketID>(id); packet)
	{
	case packet::login::PacketID::PI_C_REQ_LOGIN:
	{
		auto createPacket = std::make_unique<neo::packet::login::P_C_REQ_LOGIN>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}

	case packet::login::PacketID::PI_S_RES_DB_LOGIN:
	{
		auto createPacket = std::make_unique<neo::packet::login::P_S_RES_DB_LOGIN>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}

	case packet::login::PacketID::PI_C_REQ_CHANNEL_INFO:
	{
		auto createPacket = std::make_unique<neo::packet::login::P_C_REQ_CHANNEL_INFO>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}

	case packet::login::PacketID::PI_S_RES_DB_CHANNEL_INFO:
	{
		auto createPacket = std::make_unique<neo::packet::login::P_S_RES_DB_CHANNEL_INFO>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}

	case packet::login::PacketID::PI_C_REQ_CHAR_DATA:
	{
		auto createPacket = std::make_unique<neo::packet::login::P_C_REQ_CHAR_DATA>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}

	case packet::login::PacketID::PI_S_RES_DB_CHAR_DATA:
	{
		auto createPacket = std::make_unique<neo::packet::login::P_S_RES_DB_CHAR_DATA>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}

	case packet::login::PacketID::PI_C_REQ_GAME_SERVER_INFO:
	{
		auto createPacket = std::make_unique<neo::packet::login::P_C_REQ_GAME_SERVER_INFO>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}

	case packet::login::PacketID::PI_C_REQ_CREATE_ID:
	{
		auto createPacket = std::make_unique<neo::packet::login::P_C_REQ_CREATE_ID>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}

	case packet::login::PacketID::PI_C_REQ_CREATE_ID_CHECK:
	{
		auto createPacket = std::make_unique<neo::packet::login::P_C_REQ_CREATE_ID_CHECK>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}

	case packet::login::PacketID::PI_S_RES_DB_ID_CREATE:
	{
		auto createPacket = std::make_unique<neo::packet::login::P_S_RES_DB_ID_CREATE>();
		createPacket->Deserialize(stream);
		return std::move(createPacket);
	}



	default:
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"not found packet id = %d\n", id);
		return std::nullopt;
	}
}
