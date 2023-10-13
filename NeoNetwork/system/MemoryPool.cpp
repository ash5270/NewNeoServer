#include "MemoryPool.h"

#include "NeoLog.h"

neo::system::MemoryPool::MemoryPool(const size_t& blockSize, const size_t& blokcCount) : mBlockSize(blockSize), mBlockCount(blokcCount)
{
	mTotalSize = blokcCount * blockSize;
	mBuffer = new char[mTotalSize];

	auto curPos = mBuffer;
	for (size_t i = 0; i < mBlockCount; i++)
	{
		mQueue.push(curPos);
		curPos += mBlockSize;
	}

	mFreeCount.store(mBlockCount);
}

neo::system::MemoryPool::~MemoryPool()
{
	delete[] mBuffer;
	mBuffer = nullptr;
}

char* const neo::system::MemoryPool::Aollocate()
{
	char* buffer;
	if (mQueue.try_pop(buffer))
	{
		--mFreeCount;
		++mUseCount;
		return buffer;
	}
	else
	{
		return nullptr;
	}
}

void neo::system::MemoryPool::Free(char* const buffer)
{
	//if(buffer>=mBuffer && buffer <= mBuffer + mTotalSize)
	if(buffer!= nullptr)
	{
		++mFreeCount;
		--mUseCount;
		mQueue.push(buffer);
	}
	else
	{
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"free error\n");
	}
}

size_t neo::system::MemoryPool::GetBlockSize() const
{
	return mBlockSize;
}

size_t neo::system::MemoryPool::GetBlockCount() const
{
	return mBlockCount;
}

