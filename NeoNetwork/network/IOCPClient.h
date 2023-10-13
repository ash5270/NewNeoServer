//iocp client
//iocp Ŭ���̾�Ʈ
#pragma once

#include "SocketCommon.h"
#include "IOCPSocket.h"
#include "IOCPData.h"
#include "IOCPSession.h"

#include<memory>


namespace neo::network
{
	class IOCPClient : public IOCPSocket
	{
	public:
		IOCPClient(const std::wstring& clientName,const std::string& ip, const int& port);
		virtual ~IOCPClient();

		//client �ʱ�ȭ
		bool InitializeClient( IOCPSession* session);
		//
	private:
		TCPSocket* mSocket;
		IOCPSession* mSession;
		SocketAddress mServerAddr;
		std::wstring mClientName;
	};

}

