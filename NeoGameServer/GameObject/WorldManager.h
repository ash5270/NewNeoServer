#pragma once
#include "MapObject.h"

#include <unordered_map>
#include <packetprocess/LogicProcess.h>
#include <sw/redis++/redis.h>



namespace neo::object
{
	class WorldManager : public GameObject
	{
	public:
		WorldManager(const std::shared_ptr<object::GameObjectManager>& gameManager,
			const std::shared_ptr<neo::process::LogicProcess>& process,
			const std::shared_ptr<sw::redis::Redis>& redis,
			const std::shared_ptr<network::SessionManager<game::GameSession>>& sessionManger);
		~WorldManager() override;
	public:
		//월드에 필요한 것은
		//1.맵에서 월드에 입장 요청시 플레이어 데이터 생성
		//2.mapManager에서는 현재 클래스를 알고 있어야함.
		//3.

		//게임에 처음 들어왔을때 
		void EnterTheWorld(std::shared_ptr<network::IOCPSession> session,
			std::unique_ptr<process::IPacket> packet);
		void EnterTheWorldRespone(std::shared_ptr<network::IOCPSession> session,
			std::unique_ptr<process::IPacket> packet);
		void LeaveTherWorld(std::shared_ptr<network::IOCPSession> session,
			std::unique_ptr<process::IPacket> packet);
		void CharacterPosUpdate(std::shared_ptr<network::IOCPSession> session,
			std::unique_ptr<process::IPacket> packet);
		void CreateWorldMap(std::shared_ptr<network::IOCPSession> session,
			std::unique_ptr<process::IPacket> packet);
		void EnterTheMap(std::shared_ptr<network::IOCPSession> session,
			std::unique_ptr<process::IPacket> packet);
		void LeaveTheMap(std::shared_ptr<network::IOCPSession> session,
			std::unique_ptr<process::IPacket> packet);
		void PlayerAttackMap(std::shared_ptr<network::IOCPSession> session,
			std::unique_ptr<process::IPacket> packet);

	public:
		std::optional<std::shared_ptr<object::PlayerObject>> GetPlayerData(const int& id);
		void RemovePlayer(const int& id);
		void Start() override;
		
	private:
		//맵 오브젝트 관리
		//게임 서버 도중 맵이 삭제되거나 추가되지 않는다.
		std::vector<std::shared_ptr<object::MapObject>> mMapObjects;
		//플레이어 데이터
		std::unordered_map<uint64_t, std::shared_ptr<object::PlayerObject>> mPlayerDatas;
		std::shared_ptr<object::GameObjectManager> mGameObjectManager;
		std::shared_ptr<sw::redis::Redis> mRedisConnction;
		std::shared_ptr<network::SessionManager<game::GameSession>> mSessionManager;
		std::weak_ptr<neo::process::LogicProcess> mLogicProcess;
	};
}
