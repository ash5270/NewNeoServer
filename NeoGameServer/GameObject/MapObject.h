#pragma once
#include <list>
#include "PlayerObject.h"
#include "../Packet/Packet.h"
#include "Portal.h"
#include <Math/Vector2.h>
#include<json.hpp>

namespace  neo::object
{
	//맵에 존재하는 데이터만 참조하기 
	class MapObject : public GameObject
	{
	public:
		MapObject(const std::shared_ptr<GameObjectManager>& worldManager, const nlohmann::json& mapDatajson);
		~MapObject() override;

		void AddPlayer(const std::shared_ptr<PlayerObject>& playerObject);
		void RemovePlayer(const std::shared_ptr<PlayerObject>& playerObject);
		void Start() override;
		void Update(const double& deltaTime) override;
		void LastUpdate(const double& deltaTime) override;
		int MapInPlayerCount() const;

		void GetInMapPlayerDatas(__out vector<packet::game::PlayerData>& vec);
		//맵에 있는 유저한테 브로드 캐스팅
		void BroadcastingPacket(neo::packet::game::Packet& packet);
		math::Vector3 GetSpawnPoint(const int32_t& leaveMapid);
	private:
		std::unordered_map<int32_t, std::shared_ptr<Portal>> mPortals;
		std::list<std::shared_ptr<PlayerObject>> mPlayerList;
		//map data
		int32_t mMapId = {};
		math::Vector2 mMapSize;
		std::wstring mName;
	};
}
