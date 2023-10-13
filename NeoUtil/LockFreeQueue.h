#pragma once

#include<iostream>
#include<atomic>
#include<memory>
using namespace std;

namespace neo::util::system
{
	template<class T> 
	class LockFreeQueue
	{
	public:
		LockFreeQueue()
		{
			Node* node = new Node();
			mHead.store(node);
			mTail.store(node);
		}

		~LockFreeQueue()
		{
			T output;
			
			delete mHead.load();
		}

		T Top()
		{
			if (!Empty())
			{
				Node* head = mHead.load(std::memory_order_relaxed);
				return head->Value;
			}
			else
				return nullptr;
		}

		void Enqueue(T item)
		{
			Node* node = new Node();
			node->Value = std::move(item);
			//�޸� ���� ��� �����ϰ�
			Node* tail = mTail.load(std::memory_order_relaxed);
			Node* next = nullptr;
			
			//tail�� next�� nullptr�� �ƴϸ� 
			//tail�� �ٸ� �����忡 ���� ������Ʈ�ǰ� �����Ƿ�,
			//�ڽŵ� ������Ʈ�� �õ���
			
			while (true)
			{
				//���⼭ tail�� ���� �Ÿ� ������ ��
				//tail�� ���� �����´�.
				//tail nullptr�̸� ���� ������ queue last back��� �ǹ��̴�.
				next = tail->Next.load(std::memory_order_acquire);
				if (!next)
				{
					if (tail->Next.compare_exchange_strong(next, node,
						std::memory_order_relaxed))
						break;
				}
				//tail nullptr�� �ƴ϶�� 
				//��� �����忡�� ���� ���� �ִٴ� �Ҹ��� �� �ڽŵ� tail ���� ������Ʈ ���Ѿ��Ѵ�.
				else
				{
					//tail�� mtail�� ���� ���ٸ� next ���� �־���
					mTail.compare_exchange_strong(tail, next);
				}
			}
			//���������� queue ���� �κ��� �ٲ��ش�.
			mTail.compare_exchange_strong(tail, node);
		}

		bool Empty()
		{
			Node* head = mHead.load(std::memory_order_relaxed);
			Node* tail = mTail.load(std::memory_order_relaxed);
			Node* next = head->Next.load(std::memory_order_acquire);

			//�������
			if (head == tail && next == nullptr)
				return true;
			else
				return false;
		}

		bool Dequeue(T& output)
		{
			Node* head = mHead.load(std::memory_order_relaxed);
			Node* tail = mTail.load(std::memory_order_relaxed);
			Node* next = head->Next.load(std::memory_order_acquire);


			//�������
			if (head == tail && next == nullptr)
				return false;

			//head�� tail�� ���� ���
			if (head == tail)
			{
				tail = mTail.load(std::memory_order_acquire);
				next = head->Next.load(std::memory_order_acquire);
				if (next == nullptr)
					return false;

				mTail.compare_exchange_strong(tail, next);
			}

			//head ������Ʈ
			mHead= next;
			output = std::move(next->Value);

			delete head;
			return true;
		}



	private:
		struct Node {
			Node() : Next(nullptr){}
			Node(const T& value):Value(value), Next(nullptr){}
			T Value;
			std::atomic<Node*> Next;
		};

		std::atomic<Node*> mHead;
		std::atomic<Node*> mTail;
		
	};
}
