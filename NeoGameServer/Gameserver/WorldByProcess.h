#pragma once
#include <Object/GameObjectManager.h>
#include <packetprocess/LogicProcess.h>
#include <memory>
#include <sw/redis++/redis++.h>
#include "../GameObject/WorldManager.h"
namespace neo::game
{
	class WorldByProcess
	{
	public:
		WorldByProcess(const GameSessionManagerPtr& sessionManager);
		~WorldByProcess();
	public:
		void Start();


	public:
		//패킷 업데이트 
		std::shared_ptr<process::LogicProcess> LogicProcess;
		std::shared_ptr<object::GameObjectManager> CurWorld;
		//패킷 처리 관련
		std::shared_ptr<sw::redis::Redis> mRedis;
		//게임 오브젝트를 생성해서 넣어야할 경우가 문제가 생김
		//std::shared_ptr<object::PlayersManager> playersManager;




	private:
		GameSessionManagerPtr mSessionManager;
		std::shared_ptr<object::WorldManager> mWorldManager;
	};

	inline WorldByProcess::WorldByProcess(const GameSessionManagerPtr& sessionManager) : mSessionManager(sessionManager)
	{
		//
		CurWorld = std::make_shared<neo::object::GameObjectManager>(L"GameObjectManager");
		mRedis = std::make_shared<sw::redis::Redis>("tcp://192.168.123.104:6379");
		auto func = std::bind(&object::GameObjectManager::Update, CurWorld.get(), std::placeholders::_1);
		auto startFunction = std::bind(&object::GameObjectManager::Start, CurWorld.get());
		LogicProcess = std::make_shared<neo::process::LogicProcess>(25, func,startFunction);

		//playersManager = std::make_shared<object::PlayersManager>(CurWorld,LogicProcess,mRedis,sessionManager);
		mWorldManager = std::make_shared<object::WorldManager>(
			CurWorld,
			LogicProcess,
			mRedis,
			mSessionManager
		);

		//CurWorld->AddGameObject(playersManager);
		CurWorld->AddGameObject(mWorldManager);
	}

	inline WorldByProcess::~WorldByProcess()
	{
	}

	inline void WorldByProcess::Start()
	{
		LogicProcess->Start();
	}
}
