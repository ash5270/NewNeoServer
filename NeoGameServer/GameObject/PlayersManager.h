//#pragma once
//#include "../Gameserver/GameSession.h"
//#include "network/SessionManager.h"
//
//#include <Object/GameObject.h>
//#include <unordered_map>
//#include <packetprocess/LogicProcess.h>
//#include <Object/GameObjectManager.h>
//#include <sw/redis++/redis.h>
//
//namespace neo::object
//{
//	class PlayersManager :public GameObject
//	{
//	public:
//		PlayersManager(const std::shared_ptr<object::GameObjectManager>& world,
//			const std::shared_ptr<neo::process::LogicProcess>& process,
//			const std::shared_ptr<sw::redis::Redis>& redis,
//			const std::shared_ptr<network::SessionManager<game::GameSession>>& sessionManger);
//		~PlayersManager() override;
//
//	public:
//		std::shared_ptr<packet::game::PlayerData> GetPlayerData(const int& id);
//		void RemovePlayer(const int& id);
//		void AddPlayerData(const std::shared_ptr<packet::game::PlayerData>& data);
//		void Start() override;
//		void Update(const double& deltaTime) override;
//		void LastUpdate(const double& deltaTime) override;
//
//	public:
//		//packet process
//		void EnterTheRegion(std::shared_ptr<network::IOCPSession> session,
//			std::unique_ptr<process::IPacket> packet);
//		void EnterTheRegionData(std::shared_ptr<network::IOCPSession> session,
//			std::unique_ptr<process::IPacket> packet);
//		void CharacterPosUpdate(std::shared_ptr<network::IOCPSession> session,
//			std::unique_ptr<process::IPacket> packet);
//		void LeaveTheRegion(std::shared_ptr<network::IOCPSession> session,
//			std::unique_ptr<process::IPacket> packet);
//
//	private:
//		std::unordered_map<uint64_t,std::shared_ptr<packet::game::PlayerData>> mPlayerDatas;
//		std::shared_ptr<object::GameObjectManager> mWorld;
//		std::shared_ptr<sw::redis::Redis> mRedisConnction;
//		std::shared_ptr<network::SessionManager<game::GameSession>> mSessionManager;
//	};
//}
//
