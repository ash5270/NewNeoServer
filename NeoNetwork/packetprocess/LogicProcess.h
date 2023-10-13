#pragma once
#include <thread>
#include <concurrent_queue.h>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include "Packet.h"
#include "../network/IOCPSession.h"
#include "../system/Time.h"

namespace neo::process
{
	////////////////////////////////////////////////////////////////////////////
	//로직 프로세스(쓰레드) 하나의 로직만을 담당하는 한개의 쓰레드, 동기화가 필요한 패킷 처리
	////////////////////////////////////////////////////////////////////////////
	class LogicProcess
	{
	public:
		LogicProcess(const size_t& fps, std::function<void(const double&)> update, std::function<void()> start );
		~LogicProcess();
	public:
		void PushPacket(std::unique_ptr<IPacket>&& packet);
		void AddFuncTalbe(const int& id, const std::function<void(std::shared_ptr<network::IOCPSession>,
			std::unique_ptr<IPacket>)>& func);
		void RemoveFuncTable(const int& id);
		void Start();
	private:
		void Execute();
		void Process();
	
	protected:
		bool mIsRunning = { false };
		bool mIsThreadRun = { false };
		size_t mThreadCount = {};
		std::vector<std::thread> mThreads;
		::Concurrency::concurrent_queue<IPacket*> mPacketQueue;
		std::unordered_map<int, std::function<void(std::shared_ptr<network::IOCPSession>,
			std::unique_ptr<IPacket>)>> mFuncTables;

		//델타 타임을 위한 타이머 
		std::unique_ptr<system::Time> mTime;
		std::function<void(const double&)> mUpdateFunction;
		std::function<void()> mStartFunction;
	};
}
