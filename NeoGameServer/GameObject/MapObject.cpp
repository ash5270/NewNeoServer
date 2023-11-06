#include "MapObject.h"

neo::object::MapObject::MapObject(const std::shared_ptr<GameObjectManager>& worldManager, const nlohmann::json& mapDatajson)
	:GameObject(nullptr, L"")
{
	mMapId = mapDatajson["MapType"];
	mMapSize = math::Vector2(mapDatajson["MapX"], mapDatajson["MapY"]);
	nlohmann::json portals = mapDatajson["portals"];
	for (int i = 0; i < portals.size(); i++)
	{
		int enterMap = portals[i]["EnterMap"];
		int exitMap = portals[i]["ExitMap"];
		nlohmann::json spawnPoint = portals[i]["SpawnPoint"];
		const float spawnX = spawnPoint[0];
		const float spawnY= spawnPoint[1];
		const float spawnZ = spawnPoint[2];
		math::Vector3 spawnVec(spawnX, spawnY, spawnZ);
		mPortals.insert(
			{ exitMap,
			std::make_shared<Portal>(
				enterMap,
				exitMap,
				spawnVec
			) });
	}
}

neo::object::MapObject::~MapObject()
{
}

void neo::object::MapObject::Start()
{
	GameObject::Start();
}

void neo::object::MapObject::Update(const double& deltaTime)
{
	if (mPlayerList.empty())
		return;
	packet::game::P_S_NOTIFY_CHAR_POSITION positions;
	for (const auto& player : mPlayerList)
	{
		positions.playerPosition.push_back({
			player->GetPlayerData().characterId,
				player->GetPlayerData().mapId,
				player->transform.position.x,
				player->transform.position.y,
			0,0,player->GetPlayerData().animaionCode
			});
	}
	BroadcastingPacket(positions);
}

void neo::object::MapObject::LastUpdate(const double& deltaTime)
{

}

int neo::object::MapObject::MapInPlayerCount() const
{
	return mPlayerList.size();
}

void neo::object::MapObject::GetInMapPlayerDatas(vector<packet::game::PlayerData>& vec)
{
	for (auto i = mPlayerList.begin(); i != mPlayerList.end(); i++)
	{
		vec.push_back((*i)->GetPlayerData());
	}
}

void neo::object::MapObject::BroadcastingPacket(neo::packet::game::Packet& packet)
{
	for (auto i = mPlayerList.begin(); i != mPlayerList.end(); i++)
	{
		auto session = (*i)->GetSession();
		if (!session.expired())
		{
			session.lock()->SendPacket(packet);
		}
	}
}

void neo::object::MapObject::BroadcastingPacket(neo::packet::game::Packet& packet, int ExceptCharId)
{
	for (auto i = mPlayerList.begin(); i != mPlayerList.end(); i++)
	{
		auto session = (*i)->GetSession();
		const int playerId = (*i)->GetPlayerData().characterId;
		if (!session.expired()&&playerId!= ExceptCharId)
		{
			session.lock()->SendPacket(packet);
		}
	}
}

neo::math::Vector3 neo::object::MapObject::GetSpawnPoint(const int32_t& leaveMapid)
{
	if(mPortals.find(leaveMapid)!=mPortals.end())
	{
		return mPortals[leaveMapid]->GetSpawnPoint();
	}
	return math::Vector3();
}

void neo::object::MapObject::AddPlayer(const std::shared_ptr<PlayerObject>& playerObject)
{
	if (playerObject == nullptr)
		return;
	//현재 접속 중인 유저 데이터 보내기
	if (!mPlayerList.empty())
	{
		packet::game::P_S_RES_WORLD_CHARACTERS worldCharacters;
		GetInMapPlayerDatas(worldCharacters.playerDatas);
		playerObject->GetSession().lock()->SendPacket(worldCharacters);
	}
	//접속 한 유저 데이터 보내기
	packet::game::P_S_RES_WORLD_CHARACTERS registerUser;
	registerUser.playerDatas.push_back(playerObject->GetPlayerData());
	BroadcastingPacket(registerUser);
	mPlayerList.push_back(playerObject);
}

void neo::object::MapObject::RemovePlayer(const std::shared_ptr<PlayerObject>& playerObject)
{
	if (mPlayerList.empty())
		return;
	mPlayerList.remove(playerObject);
	neo::packet::game::P_S_NOTIFY_LEAVE_WORLD_PLAYER leavePlayer;
	leavePlayer.characterId = playerObject->GetPlayerData().characterId;
	BroadcastingPacket(leavePlayer);
}
