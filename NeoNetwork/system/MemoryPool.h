#pragma once
#include <concurrent_queue.h>
#include <atomic>

namespace neo::system {
	class MemoryPool
	{
	public:
		//block size,block count;
		MemoryPool(const size_t& blockSize, const size_t& blokcCount);
		~MemoryPool();
	public:
		//할당
		char* const Aollocate();
		//해제
		void Free(char* const buffer);
		size_t GetBlockSize() const;
		size_t GetBlockCount() const;
	private:
		//neo::util::system::MPMCQueue<char*> mQueue;
		Concurrency::concurrent_queue<char*> mQueue;
		char* mBuffer = nullptr;
		//블록사이즈
		size_t mBlockSize = 0;
		//블록 갯수
		size_t mBlockCount = 0;
		//총 사이즈
		size_t mTotalSize = 0;

		std::atomic<int> mUseCount = 0;
		std::atomic<int> mFreeCount = 0;
	};
}

