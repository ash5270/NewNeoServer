#include "GameObjectManager.h"
#include "GameObject.h"
#include "../../NeoNetwork/system/NeoLog.h"

neo::object::GameObjectManager::GameObjectManager(const std::wstring& name) :mName(name)
{
}

neo::object::GameObjectManager::~GameObjectManager()
{
}

void neo::object::GameObjectManager::Start()
{
	try
	{
		for (const auto& obj : mGameObjects)
		{
			obj->Start();
		}
	}
	catch (std::exception& e)
	{
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"%s\n", e.what());
	}
	
}

void neo::object::GameObjectManager::Update(const double& deltaTime)
{
	for (const auto& obj : mGameObjects)
	{
		if(obj->GetIsActive())
			obj->Update(deltaTime);
	}
}

void neo::object::GameObjectManager::AddGameObject(const std::shared_ptr<GameObject>& gameObject)
{
	mGameObjects.push_back(gameObject);
}

void neo::object::GameObjectManager::RemoveGameObject(const std::shared_ptr<GameObject>& gameObject)
{
	int i = {};
	for(i=0; i<mGameObjects.size(); i++)
	{
		if(mGameObjects[i]==gameObject)
		{
			break;
		}
	}
	mGameObjects.erase(mGameObjects.begin() + i);
}

void neo::object::GameObjectManager::RemoveGameobject(const int& id)
{
	mGameObjects.erase(mGameObjects.begin() + id);
}

std::vector<std::shared_ptr<neo::object::GameObject>>& neo::object::GameObjectManager::GetGameObjects()
{
	return mGameObjects;
}
