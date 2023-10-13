//�⺻���� ��Ʈ�� Ŭ����
//���۶� ����� �����̶�� ����

#pragma once
#include <memory>
namespace neo::system
{
	const int32_t MAX_BUFFER_SIZE = 65536;

	class Buffer
	{
	public:
		Buffer(const size_t& size) : mCapacity(size),mHead(0)
		{
			mBuf = std::make_unique<char[]>(size);
		}

		~Buffer()
		{
			
		}

		Buffer(const Buffer& buffer) : mCapacity(buffer.GetCapacity())
		{
			//memory copy
			mBuf = std::make_unique<char[]>(buffer.GetCapacity());
			memcpy_s(mBuf.get(),
				mCapacity,
				buffer.GetDataPtr(),
				buffer.GetCapacity());
			mHead = buffer.mHead;
		}

		Buffer( Buffer&& buffer) noexcept: mCapacity(buffer.GetCapacity())
		{
			mBuf = std::move(buffer.mBuf);
			mHead = buffer.mHead;
		}

	public:
		inline char* GetDataPtr() const
		{
			return mBuf.get();
		}

		inline size_t GetCapacity() const
		{
			return mCapacity;
		}

		inline size_t GetSize() const
		{
			return mCapacity - mHead;
		}

		inline size_t GetOffset() const
		{
			return mHead;
		}

		inline void SetOffset(const size_t& offset)
		{
			mHead = offset;
		}

		//앞에 사용한 offset 만큼 밀어버리기
		inline void MoveUp()
		{
			memmove_s(mBuf.get(),mCapacity,mBuf.get() + mHead, mCapacity - mHead);
		}
	private:
		//ũ��
		size_t mCapacity;
		//buf
		std::unique_ptr<char[]> mBuf;
		//offset
		size_t mHead = 0;
	};
}
