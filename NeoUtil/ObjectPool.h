#pragma once
#include<Windows.h>
#include<vector>
#include<memory>
namespace neo::util::system {
	
	template<class T>
	class ObjectPool
	{
	public:
		ObjectPool(const size_t& size)
		{
			for (int i = 0; i < size; i++)
				mFreeObjects.push_back(std::make_shared<T>());
			::InitializeCriticalSection(&mCriticalSection);
		}

		~ObjectPool()
		{
			::DeleteCriticalSection(&mCriticalSection);
			for (auto ptr : mFreeObjects)
			{
				ptr.reset();
			}
		}

		std::shared_ptr<T> GetSharedObject()
		{
			::EnterCriticalSection(&mCriticalSection);
			if (mFreeObjects.empty())
			{

			}
			
		    auto obj = mFreeObjects.back();
			mFreeObjects.pop_back();
			::LeaveCriticalSection(&mCriticalSection);
			return obj;
		}

		void ReleaseObject(std::shared_ptr<T> object)
		{
			::EnterCriticalSection(&mCriticalSection);
			mFreeObjects.push_back(object);
				::LeaveCriticalSection(&mCriticalSection);
		}

	private:
		std::vector<std::shared_ptr<T>> mFreeObjects;
		CRITICAL_SECTION mCriticalSection;
	};
}