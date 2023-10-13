#include "ChannelProcess.h"
#include "../packet/Packet.h"
neo::packet::process::ChannelProcess::ChannelProcess()
{

}

neo::packet::process::ChannelProcess::~ChannelProcess()
{

}

void neo::packet::process::ChannelProcess::Process(packet::PacketObject* packet)
{
	if (packet->packet->GetID() == PacketID::PI_C_REQ_CHANNEL_REGISTER)
	{
		//ä��
		auto registerPacket = dynamic_cast<P_C_REQ_CHANNEL_REGISTER*>(packet->packet);
		LOG_PRINT(LOG_LEVEL::LOG_INFO, L"id : %s enter channel id : %d\n",
			registerPacket->id.c_str(),
			registerPacket->channelID);

		//ä�ο� ���� �߰�
		object::ChannelManager::GetInstance().AddUser(registerPacket->channelID, packet->session);

		P_S_RES_CHANNEL_REGISTER respone;
		respone.channelID = registerPacket->channelID;
		respone.msg = L"success";
		respone.statusCode = 200;
		packet->session->SendPacket(respone);
	}

	delete packet->packet;
}

void neo::packet::process::ChannelProcess::ChannelInfoRespone(const  neo::packet::PacketObject* packet)
{

}

void neo::packet::process::ChannelProcess::ChannelRegister(const  neo::packet::PacketObject* packet)
{

}
