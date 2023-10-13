//이걸 서버에 연결 시켜야함.
#pragma once
#include <string>
#include "Terminal.h"
namespace neo::network
{
	template<typename _TSession>
	class TerminalClient
	{
	public:
		TerminalClient(HANDLE* iocpHandle,const std::string& ip,const int port): mSocketAddr(ip, port), mIOCPHandle(iocpHandle)
		{
			mTerminal = std::make_shared<_TSession>();
			mSocket = new TCPSocket();
			mSocket->CreateSocket();

			mTerminal->OnAccept(mSocket, &mSocketAddr);
		}

		virtual ~TerminalClient()
		{
			delete mSocket;
		}

	public:
		bool StartConnect()
		{
			if (mSocket->Connect(mSocketAddr) == -1)
			{
				LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"Connect error msg:%d\n", WSAGetLastError());
				mSocket->CloseSocket();
				return false;
			}

			*mIOCPHandle = CreateIoCompletionPort(
				reinterpret_cast<HANDLE>(mSocket->GetSOCKET()),
				*mIOCPHandle,
				reinterpret_cast<ULONG_PTR>(mTerminal.get()),
				0);

			if (*mIOCPHandle == NULL)
			{
				LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"CreateIoCompletionPort error msg:%d\n", WSAGetLastError());
				return false;
			}
			LOG_PRINT(LOG_LEVEL::LOG_DEBUG, L"terminal connect success\n");
			mTerminal->RecvReady();
		}

		void SendTest()
		{
			mTerminal->SendTest(12);
		}
	protected:
		TCPSocket* mSocket;	
		std::shared_ptr <_TSession> mTerminal;
		SocketAddress mSocketAddr;
		HANDLE* mIOCPHandle;
	};

}
