#pragma once
#include <packetprocess/PacketProcess.h>
#include <sw/redis++/redis++.h>
namespace neo::process
{
	class DBPacketProcess : public PacketProcess
	{
	private:
		static constexpr int THREAD_COUNT = 6;
	public:
		DBPacketProcess();
		~DBPacketProcess();
		
	private:
		void LoginUserProcess(std::shared_ptr<network::IOCPSession> session, std::unique_ptr<IPacket> packet);
		void ChannelReqProcess(std::shared_ptr<network::IOCPSession> session, std::unique_ptr<IPacket> packet);
		void CharacterReqProcess(std::shared_ptr<network::IOCPSession> session, std::unique_ptr<IPacket> packet);
		void InGamePlayerDataReqProcess(std::shared_ptr<network::IOCPSession> session, std::unique_ptr<IPacket> packet);
		void WorldMapReqProcess(std::shared_ptr<network::IOCPSession> session, std::unique_ptr<IPacket> packet);
		sw::redis::Redis mRedisConnection;
	};

}
