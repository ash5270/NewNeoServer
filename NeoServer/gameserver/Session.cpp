#include "Session.h"
#include <system/OutputMemoryStream.h>
#include <system/InputMemoryStream.h>
#include "../packet/PacketObject.h"
#include "../packet/PacketAnalyzeAndCreate.h"
#include"../manager/ChannelManager.h"
#include "GameServer.h"


neo::server::Session::Session() : IOCPSession(), mChannelId(0),mGameServer(nullptr), mRecvOffset(0)
{

}

neo::server::Session::~Session()
{

}

bool neo::server::Session::OnAccept(TCPSocket* socket, SocketAddress* addrInfo)
{
	LOG_PRINT(LOG_LEVEL::LOG_INFO, L"OnAccept\n");

	mTCPSocket = socket;
	mSocketAddress = addrInfo;

	mIsConnecting.store(true);
	mIsSending.store(false);

	return true;
}

void neo::server::Session::SetGameServer( GameServer* gameServer)
{
	mGameServer = gameServer;
}

void neo::server::Session::OnSend(size_t transferSize)
{
	//LOG_PRINT(LOG_LEVEL::LOG_INFO, L"--OnSend %d \n", transferSize);
	//����� ���� �ٽ� ����
	auto buf = mSendData->GetBuffer();
	mMemoryPool->Free(buf);
	
	if (mSendPacketQueue.IsEmpty())
	{
		bool check = true;
		mIsSending.compare_exchange_strong(check,false);
	}
	else
	{
		SendIO();
	}

	//LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"missending %d\n", mIsSending.load());
}

void neo::server::Session::OnRecv(size_t transferSize)
{
	//LOG_PRINT(LOG_LEVEL::LOG_INFO, L"--OnRecv %d \n", transferSize);
	InputMemoryStream inputStream(mRecvData->GetBuffer(), Memory_Pool_Block_Size);
	while (inputStream.GetLength() < transferSize)
	{
		//packet create
		auto newPacket = packet::PacketAnalyzeAndCreate::GetInstance().Analyzer(inputStream,transferSize);
		//��Ŷ�� �ؼ��� �� ���ų�, ���� ������ ����� ��Ŷ ũ�⺸�� ���� ��� 
		if (newPacket == nullptr)
		{
			//���� ��Ŷ�� �ص� �� �� ����
			//�ٵ� ���� �̹� ��Ŷ�� new �߱⶧���� �����ϵ� 
			//���� ��Ŷ ������ ��ŭ �����صΰ� �������� ������ �Ű� �α�
			auto leftSize = transferSize - inputStream.GetLength();
			LOG_PRINT(LOG_LEVEL::LOG_DEBUG, L"left size ==  %d\n", leftSize);
			mRecvOffset = leftSize;
			break;

		}	
		else {
			packet::PacketObject* packetObj = new packet::PacketObject();
			packetObj->packet = newPacket;
			packetObj->session = this;

			//Packet�� queue�� ����
			auto channel = static_cast<int>(newPacket->Channel);
			mGameServer->GetChannelThread()[channel]->GetPacketQueue()->Enqueue(packetObj);
			//LOG_PRINT(LOG_LEVEL::LOG_INFO, L"Recv Packet id : %d,  size : %d, channel : %d\n", (int)newPacket->GetID(), newPacket->GetSize(), channel);
			mRecvOffset = 0;
		}
	}
	
	if (mRecvOffset!=0)
		this->RecvReady(inputStream.GetLength(), mRecvOffset);
	else
		this->RecvReady();  
}

void neo::server::Session::OnClose ()
{
	LOG_PRINT(LOG_LEVEL::LOG_INFO, L"OnClosed\n");
	neo::object::ChannelManager::GetInstance().RemoveUser(mChannelId, this);
	mIsConnecting.exchange(false);
}



void neo::server::Session::SendPacket(Packet& packet)
{
	//�޸�Ǯ���� �ϳ� ������
	if (!mIsConnecting.load())
		return;

	auto buffer = mMemoryPool->Aollocate();
	system::OutputMemoryStream output(buffer, mMemoryPool->GetBlockSize());
	packet.Serialize(output);
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
