#include "TestSession.h"
#include <PerformanceTest/StopWatch.h>
neo::test::TestSession::TestSession() : IOCPSession()
{
}

neo::test::TestSession::~TestSession()
{
}

bool neo::test::TestSession::OnAccept(TCPSocket* socket, SocketAddress* addrInfo)
{
	mTCPSocket = socket;
	mSocketAddress = addrInfo;

	mIsSending.store(false);
	mIsConnecting.store(true);

	LOG_PRINT(LOG_LEVEL::LOG_INFO, L"New connection Client ...\n");
	return false;
}


void neo::test::TestSession::OnSend(size_t transferSize)
{
	LOG_PRINT(LOG_LEVEL::LOG_INFO, L"--OnSend %d\n", transferSize);
	SendReady();
}

void neo::test::TestSession::OnRecv(size_t transferSize)
{
	LOG_PRINT(LOG_LEVEL::LOG_INFO, L"%s transfersize : %d\n", __FUNCTION__,transferSize);
	RecvReady();
}
int x[32];
void neo::test::TestSession::SendTestData()
{
	if (!mIsConnecting.load())
		return;

	auto buffer = mMemoryPool->Aollocate();
	if (buffer == nullptr)
		return;

	system::OutputMemoryStream output(buffer, mMemoryPool->GetBlockSize());

	//1200byte
	output.Write(x, sizeof(int) * 2);
	WSABUF buf;
	buf.buf = buffer;
	buf.len = output.GetLength();
	mSendPacketQueue.enqueue(buf);
	bool check = false;
	if (mIsSending.compare_exchange_strong(check, true))
	{
		SendIO();
	}
}
