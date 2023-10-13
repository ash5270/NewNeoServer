#include "Terminal.h"

neo::network::Terminal::Terminal() : IOCPSession()
{
}

neo::network::Terminal::~Terminal()
{
}

bool neo::network::Terminal::OnAccept(TCPSocket* socket, SocketAddress* addrInfo)
{
	mTCPSocket = socket;
	mSocketAddress = addrInfo;
	mIsSending.store(false);
	mIsConnecting.store(true);
	LOG_PRINT(LOG_LEVEL::LOG_DEBUG, L"terminal connect\n");
	return true;
}

void neo::network::Terminal::OnSend(size_t transferSize)
{
	LOG_PRINT(LOG_LEVEL::LOG_DEBUG, L"terminal send %d\n",transferSize);
	SendReady();
}

void neo::network::Terminal::OnRecv(size_t transferSize)
{
	LOG_PRINT(LOG_LEVEL::LOG_DEBUG, L"terminal recv %d\n",transferSize);
	RecvReady();
}
