#pragma once
#include <thread>
#include <concurrent_queue.h>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include "Packet.h"
#include "../network/IOCPSession.h"

namespace neo::process
{
	////////////////////////////////////////////////////////////////////////////
	//패킷 프로세스(쓰레드들) 여러개의 쓰레드를 통해 동기화 될 필요없는 패킷 처리
	////////////////////////////////////////////////////////////////////////////
	class PacketProcess
	{
	public:
		PacketProcess(const size_t& threadCount);
		~PacketProcess();
	public:
		void PushPacket(std::unique_ptr<IPacket>&& packet);
	private:
		void Execute();
		void Process();
	protected:
		bool mIsRunning = { false };
		size_t mThreadCount = {};
		std::vector<std::thread> mThreads;
		::Concurrency::concurrent_queue<IPacket*> mPacketQueue;
		std::unordered_map<int, std::function<void(std::shared_ptr<network::IOCPSession>,
			std::unique_ptr<IPacket>)>> mFuncTables;
	};
}
