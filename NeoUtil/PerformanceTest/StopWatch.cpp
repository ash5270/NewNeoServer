#include "StopWatch.h"

neo::util::StopWatch::StopWatch() : mStartTime(), mStopTime(), mPauseStartTime(), mPauseStopTime()
{
}

neo::util::StopWatch::~StopWatch()
{

}

void neo::util::StopWatch::Start()
{
	if (!mIsRunning)
	{
		mStartTime = std::chrono::high_resolution_clock::now();
		mIsRunning = true;
	}
}

void neo::util::StopWatch::Stop()
{
	if (mIsRunning)
	{
		mStopTime = std::chrono::high_resolution_clock::now();
		mIsRunning = false;
	}
}

void neo::util::StopWatch::StartPause()
{
	if (!mIsRunning)
	{
		mPauseStartTime = std::chrono::high_resolution_clock::now();
		mIsPause = true;
	}
}

void neo::util::StopWatch::StopPause()
{
	if (mIsRunning)
	{
		mPauseStopTime = std::chrono::high_resolution_clock::now();
		mIsPause = false;
	}
}

bool neo::util::StopWatch::Reset()
{
	if (mIsPause || mIsRunning)
		return false;

	mStartTime = time_point<steady_clock>();
	mStopTime = time_point<steady_clock>();
	mPauseStopTime = time_point<steady_clock>();
	mPauseStartTime = time_point<steady_clock>();
	return true;
}

bool neo::util::StopWatch::Timer(int seconds)
{
	if (mIsRunning)
	{
		mStopTime = std::chrono::high_resolution_clock::now();
		const auto duration = mStopTime - mStartTime;
		const auto result = std::chrono::duration_cast<milliseconds>(duration);
		if(result.count()>= seconds * 1000)
		{
			return false;
		}
		return true;
	}
	else
	{
		mStartTime = std::chrono::high_resolution_clock::now();
		mIsRunning = true;
		mTimerCount = seconds;
		return true;
	}
}
