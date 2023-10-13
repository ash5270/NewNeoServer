//IOCP 서버
//IOCP Server
//서버 시작과 종료, 그리고 세션을 가지고 있음
#pragma once

#include <list>
#include "SocketCommon.h"
#include "IOCPSocket.h"
#include "IOCPData.h"
#include "IOCPSession.h"

namespace neo::network
{

	template<class _TSession>
	class IOCPServer : public IOCPSocket
	{
	public:
		IOCPServer(const std::wstring& serverName):IOCPSocket(), mServerName(serverName)
		{
			mIOCPData = std::make_unique<neo::network::IOCPData>(neo::network::IO_TYPE::IO_ACCEPT);
			mIOCPBuffer = std::make_unique<char>(1024);
			mIOCPData->SetBuffer(mIOCPBuffer.get(), 1024);
			mListenSocket = 0;
		}

		virtual ~IOCPServer()
		{
			
		}

		virtual void OnCompleteInit()
		{
			
		}

		//server 초기화
		bool InitializeServer(const int& port ,const size_t& threadCount = 0)
		{
			//Log
			system::LogSystem::GetInstance().InitSystem(mServerName);
			if (!WSAInit())
				LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"INIT error\n");

			//IOCP handle 생성
			//thread 생성
			size_t threadNum = threadCount;
			if(threadNum == 0)
			{
				SYSTEM_INFO systemInfo;
				GetSystemInfo(&systemInfo);
				if (threadCount)
					mIOCPHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
				threadNum = systemInfo.dwNumberOfProcessors;
			}
			
			if (!CreateIOThread(threadNum))
			{
				LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"Io thread error\n");
				return false;
			}

			mListen.CreateSocket();
			mListen.SetNoDelay(true);

			SocketAddress address(INADDR_ANY, port);
			int result = mListen.Bind(address);
			if (result == SOCKET_ERROR)
			{
				LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"bind error %d\n", WSAGetLastError());
				CloseServer();
				return false;
			}

			mIOCPHandle = CreateIoCompletionPort((HANDLE)mListen.GetSOCKET(),
				mIOCPHandle,
				(u_long)0,
				0);

			if (mIOCPHandle == NULL)
			{
				LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"acceptex io completion port  error\n");
			}

			result = mListen.Listen();
			if (result == SOCKET_ERROR)
			{
				LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"bind error %d\n", WSAGetLastError());
				CloseServer();
				return false;
			}
			LOG_PRINT(LOG_LEVEL::LOG_INFO, L"Server Init...\n");
			OnCompleteInit();
			return true;
		}
		//server 시작
		void StartServer()
		{
			if (!system::LogSystem::GetInstance().StartSystem())
			{
				wprintf_s(L"LogSystem start Error\n");
			}
			//
			bool result = readyAccept();
			if (!result)
				return;
			LOG_PRINT(LOG_LEVEL::LOG_INFO, L"Server Start...\n");
		}
		//server 중지
		void StopServer()
		{
			closesocket(mListenSocket);
			WSACleanup();
		}
		//
		virtual _TSession* OnAccept(TCPSocket* socket, SocketAddress* addrInfo)
		{
			return nullptr;
		}
		virtual void UpdateServer()
		{
			
		}
		//CloseReady
		void CloseServer()
		{
			closesocket(mListenSocket);
			WSACleanup();
		}

	protected:
		void Accept(const size_t& transferSize) override
		{
			//세션 생성
			SOCKADDR* localAddr;
			int localAddrSize = 0;
			//remote 연결되는 대상
			SOCKADDR* remoteAddr;
			int remoteAddrSize = 0;

			//get sockaddr info
			//Socket정보를 알아옴
			GetAcceptExSockaddrs((void*)mIOCPData->GetBuffer(),
				0,
				(sizeof(SOCKADDR_IN) + 16),
				(sizeof(SOCKADDR_IN) + 16),
				&localAddr,
				&localAddrSize,
				&remoteAddr,
				&remoteAddrSize);


			SocketAddress* clientAddr = new SocketAddress(*remoteAddr);
			auto session = OnAccept(mClient, clientAddr);

			//register to session io completion port 
			mIOCPHandle = CreateIoCompletionPort(reinterpret_cast<HANDLE>(mIOCPData->GetSocket()),
				mIOCPHandle,
				reinterpret_cast<ULONG_PTR>(session),
				0);

			if (mIOCPHandle == NULL)
			{
				LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"session io completion port error\n");
			}

			session->RecvReady();
			readyAccept();
		}
		//accept 준비//callback 함수로 사용하기 위해
		bool readyAccept()
		{
			////client socket create 
			mClient = mListen.AcceptEX(mIOCPData->GetBuffer(), mIOCPData->GetOverlapped());
			if (mClient == nullptr)
			{
				return false;
			}
			mIOCPData->SetSocket(mClient->GetSOCKET());
			return true;
		}
	protected:
		SOCKET mListenSocket;

		SOCKADDR_IN mServerAddr;
		TCPSocket mListen;
		TCPSocket* mClient;
		bool mIsAccept;
		
		std::unique_ptr<IOCPData> mIOCPData;
		std::unique_ptr<char> mIOCPBuffer;

		std::wstring mServerName;
	};

	
}
