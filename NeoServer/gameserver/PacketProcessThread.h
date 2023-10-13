//������ �ʿ���� ��Ŷ���� ���� ó�� ������ 

#pragma once
#include"../BasePacketThread.h"

namespace neo::system
{
	class PacketProcessThread : public BasePacketThread
	{
	public:
		PacketProcessThread(const int& id);
		~PacketProcessThread();

	public:
		void Start() override;
		void Stop() override;
		std::shared_ptr<util::system::LockFreeQueue<packet::PacketObject*>> GetPacketQueue() override
		{
			return mPacketQueue;
		}

		packet::PacketProcess* GetPacketProcess() override
		{
			return mPacketProcess.get();
		}
	private:
		void ThreadUpdate() override;
	};
}
