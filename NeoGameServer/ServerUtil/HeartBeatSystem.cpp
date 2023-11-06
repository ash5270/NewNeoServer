#include "HeartBeatSystem.h"

neo::game::util::HeartBeatSystem::HeartBeatSystem(const GameSessionManagerPtr& sessionManager) : GameObject(nullptr, L"HeartBeatSystem"),
mSessionManager(sessionManager)
{

}

neo::game::util::HeartBeatSystem::~HeartBeatSystem()
{

}

void neo::game::util::HeartBeatSystem::Start()
{

}

void neo::game::util::HeartBeatSystem::Update(const double& deltaTime)
{
	//현재 시각 측정
	chrono::time_point<chrono::steady_clock> curTime = chrono::steady_clock::now();
	for (const auto& session : mSessionManager->GetAllSession())
	{
		auto durationTime =   curTime - session.second->GetHeartBeat();
		auto duration = chrono::duration_cast<chrono::seconds>(durationTime);
		if (duration.count() > mHeartBeatTime)
		{
			session.second->CloseSession();
			session.second->UpdateHeartBeat();
		}
	}
}
