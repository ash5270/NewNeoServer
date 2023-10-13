#include "TestClient.h"

neo::test::TestClient::TestClient(const std::string& ip, const int& port) : IOCPClient(ip,port)
{

}

neo::test::TestClient::~TestClient()
{

}

