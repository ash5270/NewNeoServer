#include "LogSystem.h"
#include <Windows.h>

neo::system::LogSystem::~LogSystem()
{
	::DeleteCriticalSection(&mCritical);
}

bool neo::system::LogSystem::InitSystem(const std::wstring& name)
{
	mLogName = name;
	mIsUpdating = false;
	::InitializeCriticalSection(&mCritical);
	this->OutPutLog(LogType::LOG_INFO, L"LogSystem Init...\n");
	//포트포워딩 안해서 서버 접속 불가


	//init console font color
	mConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mConsole, static_cast<WORD>(FontColor::Default_White));

	return true;
}

bool neo::system::LogSystem::StartSystem()
{
	mIsUpdating = true;
	this->OutPutLog(LogType::LOG_INFO, L"LogSystem Start...\n");
	return true;
}

void neo::system::LogSystem::StopSystem()
{
	mIsUpdating = false;
	::DeleteCriticalSection(&mCritical);
}

void neo::system::LogSystem::OutPutLog(LogType type, const std::wstring& log)
{
	EmplaceLogData(type, log);
}

void neo::system::LogSystem::AddLogData(LogData&& logData)
{
	::EnterCriticalSection(&mCritical);
	mLogDatas.push(std::move(logData));
	::LeaveCriticalSection(&mCritical);
}

void neo::system::LogSystem::EmplaceLogData(LogType type, const std::wstring& log)
{
	::EnterCriticalSection(&mCritical);
	mLogDatas.emplace(type, log);
	::LeaveCriticalSection(&mCritical);
}

void neo::system::LogSystem::Update()
{
	while (mIsUpdating)
	{
		//비어있을때 의미없는 사용을 막기 위해 
		//context switch 해줌
		if (mLogDatas.empty()) 
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
			continue;
		}

		::EnterCriticalSection(&mCritical);
		const LogData  log = mLogDatas.front();
		mLogDatas.pop(); 
		TypeSelectAndPrintLog(log);
		::LeaveCriticalSection(&mCritical);
	}
}

void neo::system::LogSystem::TypeSelectAndPrintLog(const LogData& logData)
{
	switch (logData.Type)
	{
	case LogType::LOG_INFO:
		SetConsoleTextAttribute(mConsole, static_cast<WORD>(FontColor::Green));
		wprintf_s(L"|| %s || LOG_INFO ==> %s", mLogName.c_str(), logData.LogMessage.c_str());
		break;
	case LogType::LOG_DEBUG:
		wprintf_s(L"|| %s || LOG_DEBUG ==> %s", mLogName.c_str(), logData.LogMessage.c_str());
		break;
	case LogType::LOG_ERROR:
		SetConsoleTextAttribute(mConsole, static_cast<WORD>(FontColor::Red));
		wprintf_s(L"|| %s || LOG_ERROR ==> %s", mLogName.c_str(), logData.LogMessage.c_str());
		break;
	case LogType::LOG_WARNING:
		SetConsoleTextAttribute(mConsole, static_cast<WORD>(FontColor::Yellow));
		wprintf_s(L"|| %s || LOG_WARNING ==> %s", mLogName.c_str(), logData.LogMessage.c_str());
		break;
	default:
		wprintf_s(L"|| %s || Type Error ==> %s", mLogName.c_str(), logData.LogMessage.c_str());
		break;
	}

	SetConsoleTextAttribute(mConsole, static_cast<WORD>(FontColor::Default_White));
}
