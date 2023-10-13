//이름 그대로 시간 측정을 위한 클래스
#pragma once
#include <chrono>
using namespace std::chrono;

namespace neo::util
{
	class StopWatch
	{
	public:
		StopWatch();
		~StopWatch();

	public:
		//시간 측정
		void Start();
		void Stop();
		//일시 정지
		void StartPause();
		void StopPause();
		//초기화
		bool Reset();

		//쓰레드 사용률이 올라갈 경우 정확하지 않는다.
		bool Timer(int time);

		//스탑워치 시작 결과
		template<class T>
		long long GetDuration()
		{
			if (mIsPause || mIsRunning)
				return -1;

			const auto totalDuration = mStopTime - mStartTime;
			const auto pauseDuration = mPauseStopTime - mPauseStartTime;
			const auto realDuration = totalDuration - pauseDuration;
			const auto result = std::chrono::duration_cast<T>(realDuration);
			mIsPause = mIsRunning = mIsTimer = false;
			return result.count();
		}

	private:
		time_point<steady_clock> mStartTime;
		time_point<steady_clock> mStopTime;
		time_point<steady_clock> mPauseStartTime;
		time_point<steady_clock> mPauseStopTime;

		//
		bool mIsRunning = false;
		bool mIsPause = false;
		bool mIsTimer = false;

		//
		long long mTimerCount = 0;
	};


}

