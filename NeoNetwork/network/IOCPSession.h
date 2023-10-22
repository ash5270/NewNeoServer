//IOCP Session
//

#pragma once
#include <memory>

#include "SocketCommon.h"
#include "IOCPData.h"
#include "TCPSocket.h"
#include "SocketAddress.h"
//
#include <LockFreeQueue.h>
#include <MPMCQueue.h>
#include <concurrent_queue.h>
#include "../system/MemoryPool.h"
#include"../system/Buffer.h"
#include"../system/OutputMemoryStream.h"

namespace neo::network {
	class IOCPSession : public std::enable_shared_from_this<IOCPSession>
	{
	public:
		IOCPSession();
		IOCPSession(const uint64_t& id);
		virtual ~IOCPSession();
	public:
		//순수가상함수로 정의
		virtual bool OnAccept(TCPSocket* socket, SocketAddress* addrInfo) =0;
		virtual void OnSend(size_t transferSize) = 0;
		virtual void OnRecv(size_t transferSize) = 0;
		virtual void OnClose();

		//데이터를 receive 하기 위한 전 단계
		void RecvReady();

		//남아 있는 사이즈 만큼 앞으로 밀어준뒤 recv 받기 준비
		void RecvReady(const size_t & offset, const size_t& haveRecvCount);
		void SendReady();
		//
		void SendIO();
		void SendTest(const size_t& byteSize);
		//연결되어있는지 확인
	    bool IsConnect();
		
	protected:
		std::queue<WSABUF> paddingBufs;
		//send,recv관련 overlapped datas
		std::shared_ptr<IOCPData> mRecvData;	
		std::shared_ptr<IOCPData> mSendData;
		//buffer 
		std::unique_ptr<system::Buffer> mRecvBuffer;
		std::unique_ptr<system::Buffer> mSendBuffer;
		
		//접속한 sock과 adddress
		TCPSocket* mTCPSocket={};
		SocketAddress* mSocketAddress={};
		//체크
		std::atomic_bool mIsConnecting={};
		std::atomic_bool mIsSending={};
		//메모리 풀
		std::unique_ptr<system::MemoryPool> mMemoryPool;
		//보낼 패킷 저장용
		util::system::MPMCQueue<WSABUF> mSendPacketQueue;
		std::deque<WSABUF> mPaddingPacketQueue;
		//송신용 
		std::unique_ptr<system::OutputMemoryStream> mOutputStream;
		//session 고유 아이디
		uint64_t mSessionId = {};
	};
}