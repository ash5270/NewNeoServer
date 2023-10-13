#pragma once
#include <network/IOCPClient.h>

using namespace neo::network;

namespace neo::test
{
	class TestClient : public IOCPClient
	{
	public:
		TestClient(const std::string& ip, const int& port);
		~TestClient() override;
	};

}
