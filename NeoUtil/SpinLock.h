#pragma once
#include<atomic>

namespace neo::util::system
{
	class SpinLock {
	public:
		SpinLock() : lock(ATOMIC_FLAG_INIT) {

		}

		void Lock()
		{
			//�� ��ɾ� �Ʒ� �ִ� ���� ���� ���� ��ɾ ���ġ �Ǵ°� ������
			//�÷��׸� true�� ���� �ʱ� �÷��� ���� ��ȯ
			while (lock.test_and_set(std::memory_order_acquire))
			{

			}
		}

		bool TryLock()
		{
			return !lock.test_and_set(std::memory_order_acquire);
		}
		
		void UnLock()
		{
			//���� ��ɾ ���� ��ɾ� ���� �ʰ� ����
			lock.clear(std::memory_order_release);
		}

		void Clear()
		{
			UnLock();
		}

	private:
		std::atomic_flag lock;
	};

	template<typename T>
	class SpinLockGraud
	{
	public:
		SpinLockGraud(T& lock) :mLock(lock)
		{
			mLock.Lock();
		}

		~SpinLockGraud()
		{
			mLock.UnLock();
		}
	private	:
		T& mLock;
	};
}