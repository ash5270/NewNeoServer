#pragma once
#include <network/IOCPServer.h>
#include "LoginSession.h"
#include<network/SessionManager.h>
#include "../PacketProcess/LoginProcess.h"
#include "S2SClient.h"

using namespace neo::network;

namespace neo::server
{
	class LoginServer : public IOCPServer<neo::server::LoginSession>
	{
	public:
		LoginServer();
		~LoginServer() override;

		void UpdateServer() override;
		LoginSession* OnAccept(TCPSocket* socket, SocketAddress* addrInfo) override;
		void OnCompleteInit() override;


		std::shared_ptr<SessionManager<LoginSession>> GetSessionManager();
	private:
		std::shared_ptr<SessionManager<LoginSession>> mSessionManager;
		//std::list<std::shared_ptr<LoginSession>> mSessions;
		std::shared_ptr<neo::process::LoginProcess> mLoginProcess;
	};
}


