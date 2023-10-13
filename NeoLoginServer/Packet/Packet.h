#pragma once
#include <packetprocess/Packet.h>

#include "system/InputMemoryStream.h"
#include "PacketID.h"

namespace neo::packet::login
{
	class Packet
	{
	public:
		virtual ~Packet() = default;
		virtual PacketID GetID() { return (PacketID)0; };
		virtual int32_t GetSize() { return 0; };
		virtual void Serialize(system::OutputMemoryStream& buffer) {};
		virtual void Deserialize(system::InputMemoryStream& buffer) {};
		//header
		void HeaderSerialize(system::OutputMemoryStream& buffer)
		{
			buffer.Write((int)GetID());
			buffer.Write((int)GetSize());
		}

		static size_t GetHeaderSize()
		{
			return sizeof(PacketID)+ sizeof(int32_t);
		}

		static bool HeaderDeserialize(__out int32_t& id,__out int32_t& size,system::InputMemoryStream& stream)
		{
			if (stream.GetLength() + sizeof(int32_t) * 2 > stream.GetCapacity())
				return false;

			//PACKET ID
			stream.Read(id);
			//PACKET SIZE
			stream.Read(size);
			return true;
		}
	};

	//session 정보와 packet 정보를 들고 있는 클래스
	class Package :public neo::process::IPacket
	{
	public:
		int GetType() override
		{
			return static_cast<int>(packet->GetID());
		}

		std::shared_ptr<network::IOCPSession> GetSession() override
		{
			return session;
		}

		std::unique_ptr<Packet> packet;
		std::shared_ptr<network::IOCPSession> session;
	};



}
