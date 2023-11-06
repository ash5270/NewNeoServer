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
		void ChannelReqProcess(std::shared_ptr<network::IOCPSession> session, std::unique_ptr<IPacket> packet);
		void CharacterReqProcess(std::shared_ptr<network::IOCPSession> session, std::unique_ptr<IPacket> packet);
		void InGamePlayerDataReqProcess(std::shared_ptr<network::IOCPSession> session, std::unique_ptr<IPacket> packet);
		void WorldMapReqProcess(std::shared_ptr<network::IOCPSession> session, std::unique_ptr<IPacket> packet);
		//id 생성관련
		void IDCheckProcess(std::shared_ptr<network::IOCPSession> session, std::unique_ptr<IPacket> packet);
		void IDCreateProcess(std::shared_ptr<network::IOCPSession> session, std::unique_ptr<IPacket> packet);
		//로그인 관려
		void LoginUserProcess(std::shared_ptr<network::IOCPSession> session, std::unique_ptr<IPacket> packet);

		sw::redis::Redis mRedisConnection;
		std::string redisConfig;
	};

}
