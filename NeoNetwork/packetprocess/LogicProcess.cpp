#include "LogicProcess.h"
#include <Windows.h>

neo::process::LogicProcess::LogicProcess(const size_t& fps, std::function<void(const double&)> update, std::function<void()> start)
	:mUpdateFunction(update), mStartFunction(start)
{
	mTime = std::make_unique<system::Time>();
	mIsThreadRun = false;
	mThreads.push_back(std::thread(
		&neo::process::LogicProcess::Process, this));
}

neo::process::LogicProcess::~LogicProcess()
{
	mIsRunning = false;
	mIsThreadRun = false;
	for (int i = 0; i < mThreads.size(); i++)
	{
		mThreads[i].join();
	}
	mThreads.clear();
}

void neo::process::LogicProcess::PushPacket(std::unique_ptr<IPacket>&& packet)
{
	try
	{
		const auto ptr = packet.release();
		mPacketQueue.push(ptr);
	}
	catch (std::exception& e)
	{
		wcout << "Push Packet exception " << e.what() << "\n";
	}
}

void neo::process::LogicProcess::Execute()
{
	IPacket* packet;
	if (mPacketQueue.try_pop(packet))
	{
		if (mFuncTables.find(packet->GetType()) != mFuncTables.end())
		{
			#ifdef _DEBUG
			try
			{
				std::unique_ptr<IPacket> ptr{ packet };
				mFuncTables.at(packet->GetType())(packet->GetSession(), std::move(ptr));
			}
			catch (std::exception& msg)
			{
				LOG_PRINT(system::LogType::LOG_ERROR, L"logic process execute function is error, msg is [%s]", msg.what());
			}

			#else

			std::unique_ptr<IPacket> ptr{ packet };
			mFuncTables[packet->GetType()](packet->GetSession(), std::move(ptr));

			#endif
		}
	}
}

void neo::process::LogicProcess::Process()
{
	while (!mIsThreadRun)
	{
		this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	const int TICK_PRE_SCOND = 25;
	const int SKIP_TICKS = 1000 / TICK_PRE_SCOND;
	const int MAX_FRAMESKIP = 5;

	ULONGLONG nextGameTick = GetTickCount64();
	int loops = {};
	float interpolation = {};
	float time = {};

	mStartFunction();

	while (mIsRunning)
	{
		while (!mPacketQueue.empty())
		{
			Execute();
		}

		loops = 0;
		while (GetTickCount64() > nextGameTick && loops < MAX_FRAMESKIP)
		{
			mTime->Update();
			//여기서 업데이트 처리
			mUpdateFunction(mTime->GetDeltaTime());
			nextGameTick += SKIP_TICKS;
			loops++;
		}

		interpolation = float(GetTickCount64() + SKIP_TICKS - nextGameTick) /
			float(SKIP_TICKS);
	}
}

void neo::process::LogicProcess::AddFuncTalbe(const int& id,
	const std::function<void(std::shared_ptr<network::IOCPSession>, std::unique_ptr<IPacket>)>& func)
{
	mFuncTables.insert({ id,func });
}

void neo::process::LogicProcess::RemoveFuncTable(const int& id)
{
	mFuncTables.erase(id);
}

void neo::process::LogicProcess::Start()
{
	mIsRunning = true;
	mIsThreadRun = true;
}

