#pragma once
#include "../Gameserver/GameSession.h"
#include <Object/GameObject.h>

namespace  neo::game::util
{
	class HeartBeatSystem : public neo::object::GameObject
	{
	public:
		HeartBeatSystem(const GameSessionManagerPtr& sessionManager);
		~HeartBeatSystem() override;
		void Start() override;
		void Update(const double& deltaTime) override;

	private:
		GameSessionManagerPtr mSessionManager;
		const long mHeartBeatTime = 30;
		float mCurTime = {};
	};
}
