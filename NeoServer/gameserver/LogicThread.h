//������ ó���ϱ� ���� ������
//���� ƽ�� ������ ��Ŷ�� ó����

#pragma once
#include<vector>
#include"../gameobject/GameObject.h"

#include<system/LogSystem.h>
#include"../BasePacketThread.h"
#include"../ObjectManager.h"

#include"Time.h"

namespace neo::system {
	class LogicThread : public BasePacketThread
	{
	public:
		LogicThread(const int& id);
		~LogicThread();

	public:
		void Start() override;
		void Stop() override;

	public:
		inline std::shared_ptr<util::system::LockFreeQueue<packet::PacketObject*>> GetPacketQueue() override
		{
			return mPacketQueue;
		}

		inline packet::PacketProcess* GetPacketProcess() override
		{
			return mPacketProcess.get();
		}

		std::weak_ptr<server::ObjectManager> GetObjectManager() const
		{
			return mObjectManager;
		}

	protected:
		void ThreadUpdate() override;
	private:
		void ComponentUpdate(const double& deltaTime);

	private:
		std::shared_ptr<server::ObjectManager> mObjectManager;
		//time
		std::unique_ptr<Time> mTime;
	};
}
