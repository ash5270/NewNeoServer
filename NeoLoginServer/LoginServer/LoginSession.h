#pragma once
#include <network/IOCPSession.h>
#include <packetprocess/PacketProcess.h>
#include <Windows.h>

#include "../Packet/Packet.h"


using namespace neo::network;

namespace neo::server
{
	class LoginServer;
	class LoginSession : public IOCPSession
	{
	public:
		LoginSession(const uint64_t& id);
		~LoginSession() override;
	public:
		//override function
		bool OnAccept(TCPSocket* socket, SocketAddress* addrInfo) override;
		void OnSend(size_t transferSize) override;
		void OnRecv(size_t transferSize) override;
		void OnClose() override;

		//set process
		void SetProcess(std::shared_ptr<neo::process::PacketProcess> process);
		//set server
		void SetServer(const LoginServer* server);
		//send packet 
		void SendPacket(neo::packet::login::Packet& packet);
		

		int64_t GetID() const;
	private:
		//세션 구별을 위한 id값.
		//uuid 대신 사용하는 이유는 나중에 세션풀을 만들면 훨씬 관리하기 편해짐
		//또한 사이즈가 더 작음 int64_t -> 8byte, uuid -> 16byte
		size_t mRecvRemainSize = {};
		uint64_t mID = {}; 
		std::shared_ptr<neo::process::PacketProcess> mProcess;
		const LoginServer* mLoginServer;
	};

}

