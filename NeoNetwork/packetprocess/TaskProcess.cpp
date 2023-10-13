#include "TaskProcess.h"

neo::task::TaskProcess::TaskProcess(const size_t& threadCount) : mThreadCount(threadCount)
{
	mIsRunning = true;
	for(int i=0; i < mThreadCount; i++)
	{
		auto thread_ = std::thread(&TaskProcess::Process, this);
	}

}

neo::task::TaskProcess::~TaskProcess()
{

}

void neo::task::TaskProcess::Execute()
{
	ITask* task = nullptr;
	if(mTaskQueue.try_pop(task))
	{
		//

	}
	else
	{
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"Task Queue empty...\n");
	}
}

void neo::task::TaskProcess::Process()
{
	while(mIsRunning)
	{
		this->Execute();
	}
}
