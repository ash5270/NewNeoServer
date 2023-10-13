#include "S2SSession.h"
#include "../Process/GamePacketAnalyze.h"
void neo::server::S2SSession::OnClose()
{
	Terminal::OnClose();
}

neo::server::S2SSession::~S2SSession()
{
}

bool neo::server::S2SSession::OnAccept(network::TCPSocket* socket, network::SocketAddress* addrInfo)
{
	LOG_PRINT(LOG_LEVEL::LOG_DEBUG, L"OnAccept...\n");
	mTCPSocket = socket;
	mSocketAddress = addrInfo;

	mIsConnecting.store(true);
	mIsSending.store(false);
	return true;
}

void neo::server::S2SSession::OnSend(size_t transferSize)
{
	LOG_PRINT(LOG_LEVEL::LOG_DEBUG, L"send data size %d\n", transferSize);
	SendReady();
}

void neo::server::S2SSession::OnRecv(size_t transferSize)
{
	LOG_PRINT(LOG_LEVEL::LOG_DEBUG, L"OnRecv... %d\n", transferSize);
	transferSize += mRecvRemainSize;
	system::InputMemoryStream stream(mRecvBuffer->GetDataPtr(), mRecvBuffer->GetCapacity());
	int32_t id = {};
	int32_t size = {};
	int32_t fixSize = {};
	while (transferSize > 0 && transferSize > neo::packet::game::Packet::GetHeaderSize())
	{
		neo::packet::game::Packet::HeaderDeserialize(id, size, stream);
		transferSize -= neo::packet::game::Packet::GetHeaderSize();
		if (transferSize < size)
		{
			transferSize += neo::packet::game::Packet::GetHeaderSize();
			stream.SetOffset(stream.GetLength() - neo::packet::game::Packet::GetHeaderSize());
			break;
		}
		else
		{
			auto package = process::GamePacketAnalyze::GetInstance().CreatePackage(id, size, stream, shared_from_this());
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

void neo::server::S2SSession::SendPacket(neo::packet::game::Packet& packet)
{
	if (!mIsConnecting.load())
		return;
	auto memory = mMemoryPool->Aollocate();
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

void neo::server::S2SSession::SetProcess(const std::shared_ptr<process::LogicProcess>& process)
{
	mProcess = process;
}
