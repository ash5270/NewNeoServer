#include "WorldManager.h"
#include"../Gameserver/S2SManager.h"
#include <json.hpp>
#include<fstream>
#include<FileRead.h>

#define AddPacketFunc(packet_id,funcName)\
process->AddFuncTalbe(static_cast<int>(packet::game::PacketID::packet_id),\
std::bind(&WorldManager::funcName, this,\
	std::placeholders::_1, std::placeholders::_2))\

neo::object::WorldManager::WorldManager(const std::shared_ptr<object::GameObjectManager>& gameManager,
	const std::shared_ptr<neo::process::LogicProcess>& process,
	const std::shared_ptr<sw::redis::Redis>& redis,
	const std::shared_ptr<network::SessionManager<game::GameSession>>& sessionManager) :GameObject(gameManager, L"")
{
	this->mGameObjectManager = gameManager;
	this->mRedisConnction = redis;
	this->mSessionManager = sessionManager;
	this->mLogicProcess = process;
	AddPacketFunc(PI_C_REQ_WORLD_ENTER_THE_SERVER, EnterTheWorld);
	AddPacketFunc(PI_S_RES_DB_ENTER_INGAME_CHAR_DATA, EnterTheWorldRespone);
	AddPacketFunc(PI_S_CLOSE_WORLD, LeaveTherWorld);
	AddPacketFunc(PI_C_UPDATE_CHAR_POSITION, CharacterPosUpdate);
	AddPacketFunc(PI_S_RES_DB_WORLD_MAP_INFO, CreateWorldMap);
	AddPacketFunc(PI_C_REQ_LEAVE_MAP, LeaveTheMap);
	AddPacketFunc(PI_C_REQ_PLAYER_ATTACK, PlayerAttackMap);
}

neo::object::WorldManager::~WorldManager()
{
	auto process = mLogicProcess.lock();
	process->RemoveFuncTable(static_cast<int>(packet::game::PacketID::PI_C_REQ_WORLD_ENTER_THE_SERVER));
	process->RemoveFuncTable(static_cast<int>(packet::game::PacketID::PI_C_REQ_WORLD_ENTER_THE_SERVER));
}

void neo::object::WorldManager::LeaveTherWorld(std::shared_ptr<network::IOCPSession> session,
	std::unique_ptr<process::IPacket> packet)
{
	NEW_PACKAGE(packet, P_S_CLOSE_WORLD, GameSession);
	//플레이어 종료 소식 알려주기
	auto playerObject = GetPlayerData(requestPacket->characterId);
	if (!playerObject.has_value())
	{
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"[LeaveTheRegion] user data is null...\n");
		return;
	}
	auto& userData = playerObject.value()->GetPlayerData();
	LOG_PRINT(LOG_LEVEL::LOG_INFO, L"user : %s, Leave the region.... id : %d, imageId : %d, position :{%d,%d}....\n ",
		userData.name.c_str(),
		userData.characterId,
		userData.characterImageId,
		userData.posX,
		userData.posY);

	RemovePlayer(requestPacket->characterId);
	mSessionManager->RemoveSession(requestSession->GetSessionId());
	//맵에서 등록 해제
	mMapObjects[userData.mapId]->RemovePlayer(playerObject.value());
	//오브젝트 해제
	mGameObjectManager->RemoveGameObject(playerObject.value());
	mRedisConnction->incrby("channel_user_count:1", -1);
}

void neo::object::WorldManager::CharacterPosUpdate(std::shared_ptr<network::IOCPSession> session,
	std::unique_ptr<process::IPacket> packet)
{
	NEW_PACKAGE(packet, P_C_UPDATE_CHAR_POSITION, GameSession);
	const auto player = GetPlayerData(requestPacket->playerPosition.characterId);
	if (!player.has_value())
		return;
	
	player.value()->SetPosition({ requestPacket->playerPosition.posX , 
		requestPacket->playerPosition.posY },
	requestPacket->playerPosition.animaionCode);
}

void neo::object::WorldManager::CreateWorldMap(std::shared_ptr<network::IOCPSession> session,
	std::unique_ptr<process::IPacket> packet)
{
	NEW_S2S_PACKAGE(packet, P_S_RES_DB_WORLD_MAP_INFO, S2SSession);

	for (int i = 0; i < requestPacket->worldMapDatas.size(); i++)
	{
		auto& res = requestPacket->worldMapDatas;
		mMapObjects.push_back(std::make_shared<MapObject>(mGameObjectManager, res[i].id));
		mGameObjectManager->AddGameObject(mMapObjects.back());
		mMapObjects.back()->SetIsActive(true);
		LOG_PRINT(LOG_LEVEL::LOG_INFO, L"Create World Map %s: id[%d], monster id[%d], monster count[%d]\n", res[i].name.c_str(), res[i].id, res[i].monsterCode, res[i].monsterCount);
	}
}

void neo::object::WorldManager::EnterTheMap(std::shared_ptr<network::IOCPSession> session,
	std::unique_ptr<process::IPacket> packet)
{
	LOG_PRINT(LOG_LEVEL::LOG_DEBUG, L"error packet \n");
}


void neo::object::WorldManager::LeaveTheMap(std::shared_ptr<network::IOCPSession> session,
	std::unique_ptr<process::IPacket> packet)
{
	NEW_S2S_PACKAGE(packet, P_C_REQ_LEAVE_MAP, S2SSession);
	mMapObjects[requestPacket->leaveMapId]->RemovePlayer(mPlayerDatas[requestPacket->characterId]);
	auto spawnPoint= mMapObjects[requestPacket->enterMapId]->GetSpawnPoint(requestPacket->leaveMapId);

	LOG_PRINT(LOG_LEVEL::LOG_DEBUG, L"leave characeter id : %d, spwan point : {%f,%f}\n",requestPacket->characterId,
		spawnPoint.x,spawnPoint.y);
	math::Vector2 vec2(spawnPoint.x, spawnPoint.y);
	mPlayerDatas[requestPacket->characterId]->SetPosition(vec2);

	packet::game::P_S_RES_ENTER_MAP enterPacket;
	enterPacket.posX = spawnPoint.x;
	enterPacket.posY = spawnPoint.y;
	enterPacket.enterMapId = requestPacket->enterMapId;
	requestSession->SendPacket(enterPacket);

	mMapObjects[requestPacket->enterMapId]->AddPlayer(mPlayerDatas[requestPacket->characterId]);
}

void neo::object::WorldManager::PlayerAttackMap(std::shared_ptr<network::IOCPSession> session,
	std::unique_ptr<process::IPacket> packet)
{
	NEW_PACKAGE(packet, P_C_REQ_PLAYER_ATTACK, GameSession);
	LOG_PRINT(LOG_LEVEL::LOG_DEBUG, L"player attack ... player id : [%d], player attack type : [%d], map id : [%d], ani code : [%d]\n",
		requestPacket->characterId, requestPacket->attackType, requestPacket->mapId, requestPacket->animaionCode);

	packet::game::P_S_RES_PLAYER_ATTACK responeAttackPacket;
	responeAttackPacket.animaionCode = requestPacket->animaionCode;
	responeAttackPacket.attackType = requestPacket->attackType;
	responeAttackPacket.characterId = requestPacket->characterId;
	//공격한 캐릭터 제외하고 맵에 있는 모든 유저들한테 전송
	mMapObjects[requestPacket->mapId]->BroadcastingPacket(responeAttackPacket, requestPacket->characterId);
}

std::optional<std::shared_ptr<neo::object::PlayerObject>> neo::object::WorldManager::GetPlayerData(const int& id)
{
	if (mPlayerDatas.find(id) != mPlayerDatas.end())
		return mPlayerDatas[id];
	else
		return std::nullopt;
}

void neo::object::WorldManager::RemovePlayer(const int& id)
{
	mPlayerDatas.erase(id);
}

void neo::object::WorldManager::Start()
{
	auto fileNames = GetFilesInDir(L"F:\\Code\\NewNeoServer\\NeoGameServer\\LoadData\\MapData\\", L"*.json");
	if(fileNames)
	{
		//TODO : 수정해야할 곳 +5 
		mMapObjects.resize(fileNames.value().size() + 5);
		auto& vec = fileNames.value();
		for(int i=0; i<vec.size(); i++)
		{
			//TODO : Json 읽어오기
			//폴더 내 에서 모든 데이터를 읽어와야함
			std::ifstream stream(L"F:\\Code\\NewNeoServer\\NeoGameServer\\LoadData\\MapData\\"+vec[i]);
			nlohmann::json mapJson = nlohmann::json::parse(stream);
			int mapType = mapJson["MapType"];
			mMapObjects[mapType] = std::make_shared<MapObject>(mGameObjectManager, mapJson);
			mGameObjectManager->AddGameObject(mMapObjects[mapType]);
		}
	}
}


void neo::object::WorldManager::EnterTheWorld(std::shared_ptr<network::IOCPSession> session,
                                              std::unique_ptr<process::IPacket> packet)
{
	NEW_PACKAGE(packet, P_C_REQ_WORLD_ENTER_THE_SERVER, GameSession);
	packet::game::P_S_RES_WORLD_CHARACTERS playerDatas;
	const auto dbServer = S2SManagerIns.GetClient(L"DBServer");
	if (!dbServer->expired())
	{
		mRedisConnction->incr("channel_user_count:1");
		packet::game::P_S_REQ_DB_ENTER_INGAME_CHAR_DATA request;
		request.sessionId = requestSession->GetSessionId();
		request.characterId = requestPacket->characterId;
		dbServer->lock()->SendPacket(request);
	}
}


void neo::object::WorldManager::EnterTheWorldRespone(std::shared_ptr<network::IOCPSession> session,
	std::unique_ptr<process::IPacket> packet)
{
	NEW_S2S_PACKAGE(packet, P_S_RES_DB_ENTER_INGAME_CHAR_DATA, S2SSession);
	const size_t currentUserCount = mPlayerDatas.size();
	auto gameSession = mSessionManager->GetSession(requestPacket->sessionId);
	if (gameSession && !gameSession.value().expired())
	{
		gameSession->lock()->SetPlayerData(requestPacket->characterId);
		neo::packet::game::P_S_RES_WORLD_PLAYER_DATA respone;
		respone.playerData = packet::game::PlayerData(
			requestPacket->characterId,
			requestPacket->mapId,
			requestPacket->characterName,
			requestPacket->characterImageId,
			requestPacket->characterWeaponId,
			requestPacket->posX,
			requestPacket->posY,
			requestPacket->animaionCode, 
			0, 0,
			requestPacket->Level,
			requestPacket->Hp,
			requestPacket->MaxHP
		);

		LOG_PRINT(LOG_LEVEL::LOG_INFO, L"user : %s, enter the region.... id : %d, imageId : %d, position :{%d,%d}....\n ",
			respone.playerData.name.c_str(),
			respone.playerData.characterId,
			respone.playerData.characterImageId,
			respone.playerData.posX,
			respone.playerData.posY);
			
		gameSession.value().lock()->SendPacket(respone);

		//플레이어 데이터 생성
		std::shared_ptr<object::PlayerObject> playerObject = std::make_shared<object::PlayerObject>(
			mGameObjectManager, gameSession.value());
		mPlayerDatas.insert({ requestPacket->characterId, playerObject });
		playerObject->SetPlayerData(respone.playerData);
		mGameObjectManager->AddGameObject(playerObject);

		//접속 유저가 없고 내가 처음이라면 보낼 데이터가 없음으로 바로 종료
		mMapObjects[requestPacket->mapId]->AddPlayer(playerObject);
	}
}
