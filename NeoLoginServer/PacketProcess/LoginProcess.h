#pragma once
#include <packetprocess/PacketProcess.h>
#include <network/SessionManager.h>
#include "../LoginServer/LoginSession.h"
#include <sw/redis++/redis++.h>

namespace neo::process
{
	class LoginProcess : public PacketProcess
	{
	private:
		static constexpr int THREAD_COUNT = 6;
	public:
		LoginProcess(const std::shared_ptr<network::SessionManager<server::LoginSession>>& manager);
		~LoginProcess();

	private:
		//로그인
		void LoginUser(std::shared_ptr<network::IOCPSession> session, std::unique_ptr<IPacket> packet);
		//로그인 처리
		void LoginUserProcess(std::shared_ptr<network::IOCPSession> session, std::unique_ptr<IPacket> packet);
		//채널
		void ChannelReqProcess(std::shared_ptr<network::IOCPSession> session, std::unique_ptr<IPacket> packet);
		void ChannelResProcess(std::shared_ptr<network::IOCPSession> session, std::unique_ptr<IPacket> packet);
		//채널 캐릭터
		void CharacterReqProcess(std::shared_ptr<network::IOCPSession> session, std::unique_ptr<IPacket> packet);
		void CharacterResProcess(std::shared_ptr<network::IOCPSession> session, std::unique_ptr<IPacket> packet);
		//게임 서버 정보 전달
		void GameServerInfoReqProcess(std::shared_ptr<network::IOCPSession> session, std::unique_ptr<IPacket> packet);
		//아이디 생성
		void IDCreateProcess(std::shared_ptr<network::IOCPSession> session, std::unique_ptr<IPacket> packet);
		void IDCheckProcess(std::shared_ptr<network::IOCPSession> session, std::unique_ptr<IPacket> packet);
		void IDCreateDBResponseProcess(std::shared_ptr<network::IOCPSession> session, std::unique_ptr<IPacket> packet);

		std::unordered_map<std::string, std::string> CheckLoginUser( uint8_t*  uuid);
	private:
		std::shared_ptr<network::SessionManager<server::LoginSession>> mSessionManager;
		std::shared_ptr<sw::redis::Redis> mRedisConnection;

	 	const std::wstring mGameServerIP= L"192.168.123.106";
		const int mGameServerPort = 12239;


		sw::redis::ConnectionOptions connection_options;
	};

}

