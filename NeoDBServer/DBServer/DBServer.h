#pragma once
#include <network/IOCPServer.h>
#include "../Process/DBPacketProcess.h"
#include "DBSession.h"
#include"../DB/DBConfig.h"
#include <list>

namespace neo::server
{
	class DBServer :
		public neo::network::IOCPServer<DBSession>
	{
	public:
		DBServer();
		~DBServer() override;

		DBSession* OnAccept(neo::network::TCPSocket* socket, neo::network::SocketAddress* addrInfo) override;
		void UpdateServer() override;

	public:
		void OnCompleteInit() override;


	protected:
		//����� ����
		std::list<shared_ptr<DBSession>> mSessions;
		std::shared_ptr<process::DBPacketProcess> mProcess;
		
	};
}
