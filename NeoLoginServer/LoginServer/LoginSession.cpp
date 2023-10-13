#include "LoginSession.h"
#include <system/InputMemoryStream.h>

#include "LoginServer.h"
#include "../../NeoServer/packet/PacketID.h"
#include "../../NeoServer/packetprocess/ChannelProcess.h"
#include "../PacketProcess/PacketAnalyze.h"
#include "../Packet/Packet.h"

neo::server::LoginSession::LoginSession(const uint64_t &id) : IOCPSession(), mID(id)
{
}

neo::server::LoginSession::~LoginSession()
{
}

bool neo::server::LoginSession::OnAccept(TCPSocket *socket, SocketAddress *addrInfo)
{
	LOG_PRINT(LOG_LEVEL::LOG_DEBUG, L"OnAccept...\n");
	mTCPSocket = socket;
	mSocketAddress = addrInfo;

	mIsConnecting.store(true);
	mIsSending.store(false);

	return true;
}

void neo::server::LoginSession::OnSend(size_t transferSize)
{
	LOG_PRINT(LOG_LEVEL::LOG_DEBUG, L"send data size %d\n", transferSize);
	SendReady();
}

void neo::server::LoginSession::OnRecv(size_t transferSize)
{
	LOG_PRINT(LOG_LEVEL::LOG_DEBUG, L"OnRecv... %d\n", transferSize);
	transferSize += mRecvRemainSize;
	system::InputMemoryStream stream(mRecvBuffer->GetDataPtr(), mRecvBuffer->GetCapacity());
	int32_t id = {};
	int32_t size = {};
	int32_t fixSize ={};
	while (transferSize>0&&transferSize> neo::packet::login::Packet::GetHeaderSize())
	{
		neo::packet::login::Packet::HeaderDeserialize(id, size, stream);
		transferSize -= neo::packet::login::Packet::GetHeaderSize();
		if (transferSize < size)
		{	
			transferSize += neo::packet::login::Packet::GetHeaderSize();
			stream.SetOffset(stream.GetLength()- neo::packet::login::Packet::GetHeaderSize());
			break;
		}
		else
		{
			auto package = process::PacketAnalyze::GetInstance().CreatePackage(id, size, stream, shared_from_this());
			if (package)
			{
				transferSize -= size;
				mProcess->PushPacket(std::move(package.value()));
			}
			else
				break;
		}
	}

	if(transferSize !=0)
	{	
		mRecvBuffer->SetOffset(stream.GetLength());
		mRecvBuffer->MoveUp();
		mRecvBuffer->SetOffset(transferSize);
		mRecvRemainSize = transferSize;
	}else{
		mRecvBuffer->SetOffset(0);
		mRecvRemainSize = 0;
	}
	RecvReady();
}

void neo::server::LoginSession::OnClose()
{
	LOG_PRINT(LOG_LEVEL::LOG_INFO, L"sessionId : %d OnClose...\n",mID);
}

void neo::server::LoginSession::SetProcess(std::shared_ptr<neo::process::PacketProcess> process)
{
	mProcess = process;
}

void neo::server::LoginSession::SetServer(const LoginServer* server)
{
	mLoginServer = server;
}

void neo::server::LoginSession::SendPacket(neo::packet::login::Packet &packet)
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

int64_t neo::server::LoginSession::GetID() const
{
	return mID;
}
