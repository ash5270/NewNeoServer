﻿#include "GameSession.h"

#include "../Packet/Packet.h"
#include "system/InputMemoryStream.h"
#include "../Process/GamePacketAnalyze.h"


neo::game::GameSession::GameSession(const uint64_t& id) :IOCPSession(id),mHeartBeat(std::chrono::steady_clock::now())
{

}

neo::game::GameSession::~GameSession()
{

}

void neo::game::GameSession::OnClose()
{
	LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"GameSession close...\n");
	auto packet = std::make_unique<neo::packet::game::P_S_CLOSE_WORLD>();
	packet->characterId = this->mCharId;
	auto package = std::make_unique<neo::packet::game::Package>();
	package->session = shared_from_this();
	package->packet = std::move(packet);

	mProcess->PushPacket(std::move(package));
}

bool neo::game::GameSession::OnAccept(network::TCPSocket* socket, network::SocketAddress* addrInfo)
{
	LOG_PRINT(LOG_LEVEL::LOG_DEBUG, L"OnAccept...\n");
	this->mTCPSocket = socket;
	this->mSocketAddress = addrInfo;
	this->mIsConnecting.store(true);
	this->mIsSending.store(false);
	return true;
}

void neo::game::GameSession::OnSend(size_t transferSize)
{
	//LOG_PRINT(LOG_LEVEL::LOG_DEBUG, L"send data size %d\n", transferSize);
	SendReady();
}

void neo::game::GameSession::OnRecv(size_t transferSize)
{
	using neo::packet::game::Packet;
	using neo::packet::game::Package;
	//LOG_PRINT(LOG_LEVEL::LOG_DEBUG, L"OnRecv... %d\n", transferSize);
	transferSize += mRecvRemainSize;
	system::InputMemoryStream stream(mRecvBuffer->GetDataPtr(), mRecvBuffer->GetCapacity());
	int32_t id = {};
	int32_t size = {};
	int32_t fixSize = {};
	while (transferSize > 0 && transferSize > Packet::GetHeaderSize())
	{
		Packet::HeaderDeserialize(id, size, stream);
		transferSize -= Packet::GetHeaderSize();
		if (transferSize < static_cast<size_t>(size))
		{
			transferSize += Packet::GetHeaderSize();
			stream.SetOffset(static_cast<size_t>(stream.GetLength()) - Packet::GetHeaderSize());
			break;
		}

		if (auto package = process::GamePacketAnalyze::GetInstance().CreatePackage(id, size, stream, shared_from_this()))
		{
			const int packetId = static_cast<int>(packet::game::PacketID::PI_C_NOTIFY_PING);
			if(package.value()->GetType() == packetId)
			{
				auto packet = static_cast<packet::game::P_C_NOTIFY_PING*>(package.value()->packet.get());
				packet::game::P_S_NOTIFY_PING pongPacket;
				pongPacket.time = packet->time;
				SendPacket(pongPacket);
			}else
			{
				mProcess->PushPacket(std::move(package.value()));
				
			}
			transferSize -= size;
		}
	}

	this->UpdateHeartBeat();

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

void neo::game::GameSession::SetProcess(const std::shared_ptr<neo::process::LogicProcess>& logicProcess)
{
	mProcess = logicProcess;
}

void neo::game::GameSession::SendPacket(neo::packet::game::Packet& packet)
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

uint64_t neo::game::GameSession::GetSessionId() const
{
	return mSessionId;
}

void neo::game::GameSession::SetPlayerData(const int& charId)
{
	mCharId = charId;
}

chrono::time_point<chrono::steady_clock> neo::game::GameSession::GetHeartBeat() const
{
	return mHeartBeat;
}

void neo::game::GameSession::UpdateHeartBeat()
{
	mHeartBeat = std::chrono::steady_clock::now();
}

