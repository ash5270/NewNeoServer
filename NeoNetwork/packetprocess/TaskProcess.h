#pragma once
#include <vector>
#include <thread>
#include <concurrent_queue.h>
#include <unordered_map>
#include <functional>

#include "Task.h"
#include "../network/IOCPSession.h"

//packet 처리를 위한 클래스
namespace neo::task
{
	class TaskProcess
	{
	public:
		TaskProcess(const size_t& threadCount);
		~TaskProcess();
	public:


	private:
		void Execute();
		void Process();
	private:
		bool mIsRunning = { false };
		size_t mThreadCount = {};

		std::vector<std::thread> mThreads;

		::Concurrency::concurrent_queue<::neo::task::ITask*> mTaskQueue;
		std::unordered_map<int, std::function<void(network::IOCPSession*, task::ITask*)>> mTaskProcessMap;
	};
}
