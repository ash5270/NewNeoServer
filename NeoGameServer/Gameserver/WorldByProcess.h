#pragma once
#include <Object/GameObjectManager.h>
#include <packetprocess/LogicProcess.h>
#include <memory>
#include <sw/redis++/redis++.h>
#include "../GameObject/WorldManager.h"
#include "../ServerUtil/HeartBeatSystem.h"
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
		//re
		std::shared_ptr<sw::redis::Redis> mRedis;

	private:
		GameSessionManagerPtr mSessionManager;
		std::shared_ptr<object::WorldManager> mWorldManager;
		std::shared_ptr<util::HeartBeatSystem> mHeartBeat;
		const std::string redisConfig = "tcp://192.168.123.104:6379";
	};

	inline WorldByProcess::WorldByProcess(const GameSessionManagerPtr& sessionManager) : mSessionManager(sessionManager)
	{
		//init
		CurWorld = std::make_shared<neo::object::GameObjectManager>(L"GameObjectManager");
		mRedis = std::make_shared<sw::redis::Redis>(redisConfig);
		auto func = std::bind(&object::GameObjectManager::Update, CurWorld.get(), std::placeholders::_1);
		auto startFunction = std::bind(&object::GameObjectManager::Start, CurWorld.get());
		LogicProcess = std::make_shared<neo::process::LogicProcess>(25, func,startFunction);

		mWorldManager = std::make_shared<object::WorldManager>(
			CurWorld,
			LogicProcess,
			mRedis,
			mSessionManager
		);

		mHeartBeat = std::make_shared<util::HeartBeatSystem>(sessionManager);
		//object add
		CurWorld->AddGameObject(mHeartBeat);
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
