#include "PacketProcess.h"
#include <thread>
neo::process::PacketProcess::PacketProcess(const size_t& threadCount) : mThreadCount(threadCount), mPacketQueue()
{
	mIsRunning = true;
	wcout << "Process Thread : " << threadCount << "...\n";
	for(int i=0; i < mThreadCount; i++)
	{
		mThreads.push_back(std::thread(&neo::process::PacketProcess::Process, this));
	}
}

neo::process::PacketProcess::~PacketProcess()
{
	mIsRunning = false;
	for(int i=0; i<mThreads.size(); i++)
	{
		mThreads[i].join();
	}
}

void neo::process::PacketProcess::Execute()
{
	IPacket* packet;
	if (mPacketQueue.try_pop(packet))
	{
		std::unique_ptr<IPacket> ptr {packet};
		const auto func= mFuncTables.find(packet->GetType());
		if(func!=mFuncTables.end())
		{
			func->second(packet->GetSession(),std::move(ptr));
		}
	}
	else
	{
		this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void neo::process::PacketProcess::Process()
{
	while(mIsRunning)
	{
		this->Execute();
	}
}

void neo::process::PacketProcess::PushPacket(std::unique_ptr<IPacket>&& packet)
{
	try
	{
		const auto ptr = packet.release();
		mPacketQueue.push(ptr);
	}
	catch (std::exception& e)
	{
		wcout <<"Push Packet exception "<<e.what() << "\n";
	}
	
}
