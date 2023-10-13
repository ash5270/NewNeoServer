#pragma once
#include <list>
#include <memory>
#include <optional>
#include <unordered_map>
#include <Windows.h>

namespace neo::network
{
	template<typename Session>
	class SessionManager 
	{
	public:
		//세션 관리
		//세션별 고유 아이디 할당 
		SessionManager()
		{
			::InitializeCriticalSection(&mCriticalSection);
		}
		~SessionManager()
		{
			::DeleteCriticalSection(&mCriticalSection);
			mSessionDir.clear();
		}

	public:
		std::weak_ptr<Session> CreateSession()
		{
			::EnterCriticalSection(&mCriticalSection);
			auto newSession = std::make_shared<Session>(mCurrentID);
			mSessionDir.insert({ mCurrentID, newSession });
			mCurrentID++;
			::LeaveCriticalSection(&mCriticalSection);
			return newSession;
		}
		
		void RemoveSession(const uint64_t& id)
		{
			::EnterCriticalSection(&mCriticalSection);
			if(mSessionDir.find(id)!=mSessionDir.end())
			{
				mSessionDir.erase(id);
			}
			::LeaveCriticalSection(&mCriticalSection);
		}

		std::optional<std::weak_ptr<Session>> GetSession(const uint64_t& id)
		{
			::EnterCriticalSection(&mCriticalSection);
			if (mSessionDir.find(id) != mSessionDir.end())
			{
				::LeaveCriticalSection(&mCriticalSection);
				return mSessionDir[id];
			}
			else
			{
				::LeaveCriticalSection(&mCriticalSection);
				return std::nullopt;
			}
		}

		std::unordered_map<uint64_t, std::shared_ptr<Session>> GetAllSession()
		{
			return mSessionDir;
		}

	private:
		uint64_t mCurrentID = {};
		std::unordered_map<uint64_t, std::shared_ptr<Session>> mSessionDir;
		::CRITICAL_SECTION mCriticalSection;
	};
}

