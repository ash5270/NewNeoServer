#include "IOCPSession.h"
#include"../system/InputMemoryStream.h"
#include"../system/OutputMemoryStream.h"
#include<memory.h>

neo::network::IOCPSession::IOCPSession() : mSendPacketQueue(16384), mMemoryPool(std::make_unique<system::MemoryPool>(Memory_Pool_Block_Size, Memory_Pool_Block_Count))
{
	mSendData = std::make_shared<IOCPData>(IO_TYPE::IO_SEND);
	mRecvData = std::make_shared<IOCPData>(IO_TYPE::IO_READ);

	//iocp data recv setting
	mRecvBuffer = std::make_unique<system::Buffer>(system::MAX_BUFFER_SIZE);
	mRecvData->SetBuffer(
		mRecvBuffer->GetDataPtr(),
		mRecvBuffer->GetCapacity()
	);

	//iocp data send setting
	mSendBuffer = std::make_unique<system::Buffer>(system::MAX_BUFFER_SIZE);
	mOutputStream = std::make_unique< system::OutputMemoryStream>(*mSendBuffer.get());

	/*mCurSendBuffer = mSendBuffers[0];
	mSendData->SetBuffer(
		mSendBuffers[0]->GetDataPtr(),
		mSendBuffers[0]->GetCapacity()
	);*/
}

neo::network::IOCPSession::IOCPSession(const uint64_t& id) : mSendPacketQueue(16384), mMemoryPool(std::make_unique<system::MemoryPool>(Memory_Pool_Block_Size, Memory_Pool_Block_Count)),
	mSessionId(id)
{
	mSendData = std::make_shared<IOCPData>(IO_TYPE::IO_SEND);
	mRecvData = std::make_shared<IOCPData>(IO_TYPE::IO_READ);

	//iocp data recv setting
	mRecvBuffer = std::make_unique<system::Buffer>(system::MAX_BUFFER_SIZE);
	mRecvData->SetBuffer(
		mRecvBuffer->GetDataPtr(),
		mRecvBuffer->GetCapacity()
	);

	//iocp data send setting
	mSendBuffer = std::make_unique<system::Buffer>(system::MAX_BUFFER_SIZE);
	mOutputStream = std::make_unique< system::OutputMemoryStream>(*mSendBuffer.get());

}

neo::network::IOCPSession::~IOCPSession()
{
	mSocketAddress = nullptr;
}


void neo::network::IOCPSession::OnClose()
{
	LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"IOCPSession close...\n");
}


void neo::network::IOCPSession::RecvReady()
{
	mRecvData->GetWSABuf()->buf = mRecvBuffer->GetDataPtr() + mRecvBuffer->GetOffset();
	mRecvData->GetWSABuf()->len = mRecvBuffer->GetCapacity() - mRecvBuffer->GetOffset();
	const auto result = mTCPSocket->WSARecv(
		mRecvData->GetWSABuf(),
		1,
		mRecvData->GetOverlapped(),
		NULL);
	if (result == SOCKET_ERROR && WSA_IO_PENDING != ::WSAGetLastError())
	{
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"recv ready error code : %d, buf len : %d\n" , ::WSAGetLastError(),mRecvBuffer->GetCapacity() - mRecvBuffer->GetOffset());
	}
}

void neo::network::IOCPSession::RecvReady(const size_t& offset, const size_t& haveRecvCount)
{
	auto leftBuf = mRecvData->GetBuffer() + offset;
	//LOG_PRINT(LOG_LEVEL::LOG_INFO, L"left buf size %d\n", Memory_Pool_Block_Size - haveRecvCount);
	//memmove
	memmove_s(mRecvData->GetBuffer(), haveRecvCount, mRecvData->GetBuffer() + offset, haveRecvCount);
	mRecvData->GetSpan()->SetOffset(haveRecvCount);

	WSABUF buf;
	buf.buf = mRecvData->GetBuffer() + mRecvData->GetSpan()->GetOffset();
	buf.len = mRecvData->GetSpan()->GetCapactiy() - mRecvData->GetSpan()->GetOffset();
	const auto result = mTCPSocket->WSARecv(
		&buf,
		1,
		mRecvData->GetOverlapped(),
		NULL);
	if (result == SOCKET_ERROR && WSA_IO_PENDING != ::WSAGetLastError())
	{
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"recv ready error : %d\n", ::WSAGetLastError());
	}
}


void neo::network::IOCPSession::SendReady()
{
	mOutputStream->Clear();
	if (mSendPacketQueue.IsEmpty())
	{
		bool check = true;
		mIsSending.compare_exchange_strong(check, false);
	}
	else
	{
		SendIO();
	}
}


void neo::network::IOCPSession::SendIO()
{
	//굳이 여러개 일 이유가 있나?
	//여기서 생기는게 메모리 단편화 내부 단편화
	if (mPaddingPacketQueue.empty() && mSendPacketQueue.IsEmpty())
	{
		bool check = true;
		mIsSending.compare_exchange_strong(check, false);
		return;
	}
	//보내다 실패한 데이터가 존재하는지
	while (!mPaddingPacketQueue.empty())
	{
		auto front = mPaddingPacketQueue.front();
		mPaddingPacketQueue.pop_front();
		if (!mOutputStream->Write(front.buf, front.len))
		{
			mPaddingPacketQueue.push_front(front);
			break;
		}
		else
		{
			mMemoryPool->Free(front.buf);
		}
	}
	//보낼려고 한 데이터가 존재하는지
	while (!mSendPacketQueue.IsEmpty())
	{
		WSABUF buf;
		if (mSendPacketQueue.dequeue(buf))
		{
			if (!mOutputStream->Write(buf.buf, buf.len))
			{
				mPaddingPacketQueue.push_back(buf);
				break;
			}
			else
			{
				mMemoryPool->Free(buf.buf);
			}
		}
	}

	mSendData->SetBuffer(mOutputStream->GetStreamPtr(), mOutputStream->GetLength());
	int result = mTCPSocket->WSASend(mSendData->GetWSABuf(),
		1,
		mSendData->GetOverlapped());
	if (result == SOCKET_ERROR && (::WSAGetLastError() != ERROR_IO_PENDING))
	{
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"WSASend error : %d\n", ::WSAGetLastError());
		return;
	}
}

void neo::network::IOCPSession::SendTest(const size_t& byteSize)
{
	if (!mIsConnecting.load())
		return;

	auto buffer = mMemoryPool->Aollocate();
	if (buffer == nullptr)
		return;

	system::OutputMemoryStream output(buffer, mMemoryPool->GetBlockSize());

	//1200byte
	for (int i = 0; i < byteSize/4; i++)
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

bool neo::network::IOCPSession::IsConnect()
{
	return mIsConnecting.load();
}

