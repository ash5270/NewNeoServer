#include "DBSession.h"
#include <system/InputMemoryStream.h>
#include "../Packet/Packet.h"
neo::server::DBSession::DBSession():IOCPSession()
{
}

neo::server::DBSession::~DBSession()
{
}

bool neo::server::DBSession::OnAccept(neo::network::TCPSocket* socket, neo::network::SocketAddress* addrInfo)
{
	LOG_PRINT(LOG_LEVEL::LOG_DEBUG, L"OnAccept...\n");
	mTCPSocket = socket;
	mSocketAddress = addrInfo;

	mIsConnecting.store(true);
	mIsSending.store(false);

	return true;
}

void neo::server::DBSession::OnSend(size_t transferSize)
{
	LOG_PRINT(LOG_LEVEL::LOG_DEBUG, L"send data size %d\n", transferSize);
	SendReady();
}

void neo::server::DBSession::OnRecv(size_t transferSize)
{
	LOG_PRINT(LOG_LEVEL::LOG_DEBUG, L"OnRecv... %d\n", transferSize);
	transferSize += mRecvRemainSize;
	system::InputMemoryStream stream(mRecvBuffer->GetDataPtr(), mRecvBuffer->GetCapacity());
	int32_t id = {};
	int32_t size = {};
	int32_t fixSize = {};
	while (transferSize > 0 && transferSize > neo::packet::db::Packet::GetHeaderSize())
	{
		neo::packet::db::Packet::HeaderDeserialize(id, size, stream);
		transferSize -= neo::packet::db::Packet::GetHeaderSize();
		if (transferSize < size)
		{
			transferSize += neo::packet::db::Packet::GetHeaderSize();
			stream.SetOffset(stream.GetLength() - static_cast<size_t>(neo::packet::db::Packet::GetHeaderSize()));
			break;
		}
		else
		{
			auto package = process::DBPacketAnalyze::GetInstance().CreatePackage(id, size, stream, shared_from_this());
			if (package)
			{
				transferSize -= size;
				mProcess->PushPacket(std::move(package.value()));
			}
			else
				break;
		}

	}

	if (transferSize != 0)
	{
		mRecvBuffer->SetOffset(stream.GetLength());
		mRecvBuffer->MoveUp();
		mRecvBuffer->SetOffset(transferSize);
		mRecvRemainSize = transferSize;
	}
	else {
		mRecvBuffer->SetOffset(0);
		mRecvRemainSize = 0;
	}
	RecvReady();
}

void neo::server::DBSession::SendPacket(neo::packet::db::Packet& packet)
{
	if (!mIsConnecting.load())
		return;
 	const auto memory = mMemoryPool->Aollocate();
	if (memory == nullptr)
		return;

	OutputMemoryStream stream(memory, mMemoryPool->GetBlockSize());
	packet.Serialize(stream);

	WSABUF buf;
	buf.buf = stream.GetStreamPtr();
	buf.len = stream.GetLength();
	mSendPacketQueue.enqueue(buf);
	bool check = false;
	if (mIsSending.compare_exchange_strong(check, true))
	{
		SendIO();
	}
}
