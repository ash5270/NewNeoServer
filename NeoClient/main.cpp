#include "Client/TestClient.h"
#include "Client/TestSession.h"

#include<PerformanceTest/StopWatch.h>

#include<thread>

using namespace neo::network;
using namespace neo::test;
using namespace neo;

int main()
{
	TestSession session;
	TestClient client("127.0.0.1",6889);
	client.InitializeClient(&session);
	std::thread logThread([&]()
		{
			system::LogSystem::GetInstance().Update();
		});
	session.SendBuffer();
	//util::StopWatch stopWatch;
	//int count = 0;
	//while (stopWatch.Timer(1))
	//{
	//	//std::this_thread::sleep_for(std::chrono::microseconds(10));
	//	session.SendBuffer();
	//	count++;
	//}

	//wprintf_s(L"%d\n", count);
	
	while(true)
	{
		
	}
	system::LogSystem::GetInstance().StopSystem();
	logThread.join();

	return 0;
}