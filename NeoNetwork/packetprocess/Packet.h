#pragma once
#include "../network/IOCPSession.h"

namespace neo::process
{
	//패킷은 서버마다 다 다르게 적용될것
	class IPacket
	{
	public:
		virtual ~IPacket() = default;
		virtual int GetType() = 0;
		virtual std::shared_ptr<network::IOCPSession> GetSession() = 0;
	};

}
