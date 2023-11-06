#pragma once
#include "../Gameserver/GameSession.h"
#include "../Packet/PacketData.h"
#include<Math/Vector2.h>
#include <Object/GameObject.h>


namespace neo::object
{
	class PlayerObject :public GameObject
	{
	public:
		PlayerObject(const std::shared_ptr<GameObjectManager>& worldManager, const std::weak_ptr<neo::game::GameSession> session);
		~PlayerObject() override;
	public:
		void SetPosition(math::Vector2 pos,const int& animationCode);
		void SetPosition(math::Vector2 pos);
		void SetPlayerData(const packet::game::PlayerData& data);

		packet::game::PlayerData& GetPlayerData();
		std::weak_ptr<neo::game::GameSession> GetSession();
		  
	private:
		packet::game::PlayerData mPlayerData;
		std::weak_ptr<neo::game::GameSession> mSession;
	};
}
