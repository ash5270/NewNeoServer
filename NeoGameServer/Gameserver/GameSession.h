#pragma once
#include <network/IOCPSession.h>
#include <packetprocess/LogicProcess.h>
#include "../Packet/PacketData.h"
#include "network/SessionManager.h"

#define NEW_PACKAGE(package,packet_type,session_type)\
const auto convertPackage = static_cast<neo::packet::game::Package*>(package.get());\
const auto requestPacket = static_cast<neo::packet::game::packet_type*>(convertPackage->packet.get());\
const auto requestSession = std::static_pointer_cast<neo::game::session_type>(session)\


#define NEW_S2S_PACKAGE(package,packet_type,session_type)\
const auto convertPackage = static_cast<neo::packet::game::Package*>(package.get());\
const auto requestPacket = static_cast<neo::packet::game::packet_type*>(convertPackage->packet.get());\
const auto requestSession = std::static_pointer_cast<neo::server::session_type>(session)\


namespace neo::game
{
	class GameSession: public network::IOCPSession
	{
	public:
		GameSession(const uint64_t& id);
		~GameSession() override;
	public:
		void OnClose() override;
		bool OnAccept(network::TCPSocket* socket, network::SocketAddress* addrInfo) override;
		void OnSend(size_t transferSize) override;
		void OnRecv(size_t transferSize) override;
		void SetProcess(const std::shared_ptr<neo::process::LogicProcess>& logicProcess);
		void SendPacket(neo::packet::game::Packet& packet);

		uint64_t GetSessionId()const;
		//
		void SetPlayerData(const int& charId);
	private:
		size_t mRecvRemainSize = {};
		std::shared_ptr<neo::process::LogicProcess> mProcess;

		//플레이어 정보
		int mCharId = {};

	};
	typedef std::shared_ptr<network::SessionManager<game::GameSession>> GameSessionManagerPtr;
}

