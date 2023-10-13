#include "IOCPClient.h"
#include"../system/NeoLog.h"
neo::network::IOCPClient::IOCPClient(const std::wstring& clientName,const std::string& ip, const int& port) 
	: IOCPSocket(),mServerAddr(ip, port),mClientName(clientName)
{
	mSocket = new TCPSocket();
}

neo::network::IOCPClient::~IOCPClient()
{
	delete mSocket;
	mSocket = nullptr;
}

bool neo::network::IOCPClient::InitializeClient( IOCPSession* session)
{
	//iocp ÃÊ±âÈ­
	WSAInit();
	system::LogSystem::GetInstance().InitSystem(mClientName);
	if (!system::LogSystem::GetInstance().StartSystem())
	{
		wprintf_s(L"LogSystem start Error\n");
		return false;
	}
	mIOCPHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE,
		NULL,
		0,
		0);

	const int threadCount = 2;
	if (!CreateIOThread(threadCount))
	{
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"Io thread error\n");
		return false;
	}

	mSocket->CreateSocket();
	if (!mSocket->SetNoDelay(true))
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"Socket nodelay set error\n");

	mSession = session;

	mSession->OnAccept(mSocket, &mServerAddr);
	LOG_PRINT(LOG_LEVEL::LOG_INFO, L"Client connecting...\n");
	if (mSocket->Connect(mServerAddr) == -1)
	{
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"Connect error msg:%d\n",WSAGetLastError());
		return false;
	}
	LOG_PRINT(LOG_LEVEL::LOG_INFO, L"Start Client...\n");
	mIOCPHandle = CreateIoCompletionPort(reinterpret_cast<HANDLE>(mSocket->GetSOCKET()),
		mIOCPHandle,
		reinterpret_cast<ULONG_PTR>(session),
		0);
	mSession->RecvReady();
	return true;
}
