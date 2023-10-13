//#include "PlayersManager.h"
//#include "../Gameserver/GameSession.h"
//#include "../Packet/PacketID.h"
//#include "../Packet/PacketData.h"
//#include"../Gameserver/S2SManager.h"
//
//
//neo::object::PlayersManager::PlayersManager(const std::shared_ptr<object::GameObjectManager>& world,
//	const std::shared_ptr<neo::process::LogicProcess>& process, const std::shared_ptr<sw::redis::Redis>& redis,
//	const std::shared_ptr<network::SessionManager<game::GameSession>>& sessionManger) : GameObject(world, L"")
//{
//
//	process->AddFuncTalbe(static_cast<int>(packet::game::PacketID::PI_C_UPDATE_CHAR_POSITION),
//		std::bind(&PlayersManager::CharacterPosUpdate, this,
//			std::placeholders::_1, std::placeholders::_2));
//
//	
//
//
//	mSessionManager = sessionManger;
//	mWorld = world;
//	mRedisConnction = redis;
//}
//
//neo::object::PlayersManager::~PlayersManager()
//{
//}
//
//std::shared_ptr<neo::packet::game::PlayerData> neo::object::PlayersManager::GetPlayerData(const int& id)
//{
//	if (mPlayerDatas.find(id) != mPlayerDatas.end())
//		return mPlayerDatas[id];
//	else
//		return std::shared_ptr<neo::packet::game::PlayerData>(nullptr);
//}
//
//void neo::object::PlayersManager::RemovePlayer(const int& id)
//{
//	mPlayerDatas.erase(id);
//}
//
//void neo::object::PlayersManager::AddPlayerData(const std::shared_ptr<neo::packet::game::PlayerData>& data)
//{
//	LOG_PRINT(LOG_LEVEL::LOG_INFO, L"insert player : %s, id : %d \n", data->name.c_str(), data->characterId);
//	mPlayerDatas.insert({ data->characterId,data });
//}
//
//void neo::object::PlayersManager::Start()
//{
//	GameObject::Start();
//}
//
//void neo::object::PlayersManager::Update(const double& deltaTime)
//{
//	if (mPlayerDatas.empty())
//		return;
//	packet::game::P_S_NOTIFY_CHAR_POSITION positions;
//	for (const auto& player : mPlayerDatas)
//	{
//		positions.playerPosition.push_back({
//			player.second->characterId,
//			player.second->posX,
//			player.second->posY,
//			0,0,0
//			});
//	}
//
//	for (const auto& session : mSessionManager->GetAllSession())
//	{
//		if (session.second->IsConnect())
//		{
//			session.second->SendPacket(positions);
//		}
//	}
//}
//
//void neo::object::PlayersManager::LastUpdate(const double& deltaTime)
//{
//	GameObject::LastUpdate(deltaTime);
//}
//
//void neo::object::PlayersManager::EnterTheRegion(std::shared_ptr<network::IOCPSession> session,
//	std::unique_ptr<process::IPacket> packet)
//{
//	NEW_PACKAGE(packet, P_C_REQ_WORLD_ENTER_THE_SERVER, GameSession);
//	packet::game::P_S_RES_WORLD_CHARACTERS playerDatas;
//	const auto dbServer = S2SManagerIns.GetClient(L"DBServer");
//	if (!dbServer->expired())
//	{
//		mRedisConnction->incr("channel_user_count:1");
//		packet::game::P_S_REQ_DB_ENTER_INGAME_CHAR_DATA request;
//		request.sessionId = requestSession->GetSessionId();
//		request.characterId = requestPacket->characterId;
//		dbServer->lock()->SendPacket(request);
//	}
//}
//
//void neo::object::PlayersManager::EnterTheRegionData(std::shared_ptr<network::IOCPSession> session,
//	std::unique_ptr<process::IPacket> packet)
//{
//	NEW_S2S_PACKAGE(packet, P_S_RES_DB_ENTER_INGAME_CHAR_DATA, S2SSession);
//	const size_t currentUserCount = mPlayerDatas.size();
//	auto gameSession = mSessionManager->GetSession(requestPacket->sessionId);
//	if (gameSession && !gameSession.value().expired())
//	{
//		gameSession->lock()->SetPlayerData(requestPacket->characterId);
//
//		neo::packet::game::P_S_RES_WORLD_PLAYER_DATA respone;
//		respone.playerData = packet::game::PlayerData(
//			requestPacket->characterId,
//			requestPacket->characterName,
//			requestPacket->characterImageId,
//			requestPacket->characterWeaponId,
//			requestPacket->posX,
//			requestPacket->posY,
//			0, 0, 0,
//			requestPacket->Level,
//			requestPacket->Hp,
//			requestPacket->MaxHP
//		);
//
//		LOG_PRINT(LOG_LEVEL::LOG_INFO, L"user : %s, enter the region.... id : %d, imageId : %d, position :{%d,%d}....\n ",
//			respone.playerData.name.c_str(),
//			respone.playerData.characterId,
//			respone.playerData.characterImageId,
//			respone.playerData.posX,
//			respone.playerData.posY);
//		gameSession.value().lock()->SendPacket(respone);
//		AddPlayerData(std::make_shared<neo::packet::game::PlayerData>(respone.playerData));
//
//		//접속 유저가 없고 내가 처음이라면 보낼 데이터가 없음으로 바로 종료
//		if (currentUserCount == 0)
//			return;
//		//접속중인 유저 데이터 보내기
//		packet::game::P_S_RES_WORLD_CHARACTERS worldCharacters;
//		for (const auto& player : mPlayerDatas)
//		{
//			worldCharacters.playerDatas.push_back({ player.second->characterId,
//			player.second->name,
//			player.second->characterImageId,
//			player.second->characterWeaponId,
//			player.second->posX,
//			player.second->posY,0,0,0,
//			player.second->Level,
//			player.second->Hp,
//			player.second->MaxHP });
//		}
//		gameSession.value().lock()->SendPacket(worldCharacters);
//		//방금 접속한 유저 데이터 싹 보내기
//		packet::game::P_S_RES_WORLD_CHARACTERS registerUser;
//		registerUser.playerDatas.push_back(respone.playerData);
//		for (const auto& session : mSessionManager->GetAllSession())
//		{
//			if (session.first != requestPacket->sessionId)
//			{
//				session.second->SendPacket(registerUser);
//			}
//		}
//	}
//}
//
//void neo::object::PlayersManager::CharacterPosUpdate(std::shared_ptr<network::IOCPSession> session,
//	std::unique_ptr<process::IPacket> packet)
//{
//	NEW_PACKAGE(packet, P_C_UPDATE_CHAR_POSITION, GameSession);
//	const auto player = GetPlayerData(requestPacket->playerPosition.characterId);
//	if (player == nullptr)
//		return;
//	player->posX = requestPacket->playerPosition.posX;
//	player->posY = requestPacket->playerPosition.posY;
//}
//
//void neo::object::PlayersManager::LeaveTheRegion(std::shared_ptr<network::IOCPSession> session,
//	std::unique_ptr<process::IPacket> packet)
//{
//	NEW_PACKAGE(packet, P_S_CLOSE_WORLD, GameSession);
//	//플레이어 종료 소식 알려주기
//	auto userData = GetPlayerData(requestPacket->characterId);
//	if (userData == nullptr)
//	{
//		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"[LeaveTheRegion] user data is null...\n");
//		return;
//	}
//	LOG_PRINT(LOG_LEVEL::LOG_INFO, L"user : %s, Leave the region.... id : %d, imageId : %d, position :{%d,%d}....\n ",
//		userData->name.c_str(),
//		userData->characterId,
//		userData->characterImageId,
//		userData->posX,
//		userData->posY);
//
//	RemovePlayer(requestPacket->characterId);
//	mSessionManager->RemoveSession(requestSession->GetSessionId());
//
//	neo::packet::game::P_S_NOTIFY_LEAVE_WORLD_PLAYER leaveWorld;
//	leaveWorld.characterId = requestPacket->characterId;
//	for (const auto& session : mSessionManager->GetAllSession())
//	{
//		session.second->SendPacket(leaveWorld);
//	}
//
//	mRedisConnction->incrby("channel_user_count:1", -1);
//}
