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
		//�Ҵ�
		char* const Aollocate();
		//����
		void Free(char* const buffer);
		size_t GetBlockSize() const;
		size_t GetBlockCount() const;
	private:
		//neo::util::system::MPMCQueue<char*> mQueue;
		Concurrency::concurrent_queue<char*> mQueue;
		char* mBuffer = nullptr;
		//��ϻ�����
		size_t mBlockSize = 0;
		//��� ����
		size_t mBlockCount = 0;
		//�� ������
		size_t mTotalSize = 0;

		std::atomic<int> mUseCount = 0;
		std::atomic<int> mFreeCount = 0;
	};
}

