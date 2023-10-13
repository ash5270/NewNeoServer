#include "TestSession.h"


bool neo::test::TestSession::OnAccept(TCPSocket* socket, SocketAddress* addrInfo)
{
	mTCPSocket = socket;
	mSocketAddress = addrInfo;

	mIsSending.store(false);
	mIsConnecting.store(true);
	mRecvTotalSize = 0;
	return false;
}

void neo::test::TestSession::OnRecv(size_t transferSize)
{
	LOG_PRINT(LOG_LEVEL::LOG_INFO, L"--OnRecv %d , recv size %d\n", transferSize, mRecvTotalSize.load());
	mRecvTotalSize += transferSize;
	RecvReady();
}

void neo::test::TestSession::OnSend(size_t transferSize)
{
	LOG_PRINT(LOG_LEVEL::LOG_INFO, L"--OnSend %d \n", transferSize);
	SendReady();
}

void neo::test::TestSession::SendBuffer()
{
	if (!mIsConnecting.load())
		return;

	auto buffer = mMemoryPool->Aollocate();
	if (buffer == nullptr)
		return;

	system::OutputMemoryStream output(buffer, mMemoryPool->GetBlockSize());

	//1200byte
	for(int i=0; i<1;i++)
	{
		int x = 12345;
		output.Write(x);
	}
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

