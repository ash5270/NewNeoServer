//span 
//C# ó�� �޸𸮸� �Ҵ�޾Ƽ� ����ϴ� ���� �ƴ�
//�̹� �Ҵ�� ���۸� ��� ���� �Ⱓ���� ����ϴ� ��

#include<iostream>
#include"NeoLog.h"

namespace neo::system
{
	class Span {
	public:
		Span(char* buffer, const size_t& size) :mHead(0), mBuffer(buffer), mCapactiy(size)
		{

		}

		~Span()
		{

		}

	public:
		inline char* GetBuffer() const
		{
			//�����ϰ� �ִ� �����Ͱ� null�ϰ��
			if (mBuffer == nullptr)
			{
				LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"span pointer is null\n");
				return nullptr;
			}
			else
			{
				return mBuffer;
			}
		}
		//������ ����ߴ��� ��ȯ
		inline int32_t GetOffset() const
		{
			return static_cast<int32_t>(mHead);
		}
		//clear
		inline void Clear()
		{
			mHead = 0;
		}
		//ũ�� ��ȯ
		size_t GetCapactiy() const
		{
			return mCapactiy;
		}

		inline void SetOffset(const size_t& size)
		{
			mHead = size;
		}

	private:
		char* mBuffer;
		size_t mHead;
		const size_t mCapactiy;
	};
}