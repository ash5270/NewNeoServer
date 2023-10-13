#include "GameObject.h"

neo::object::GameObject::GameObject(const std::shared_ptr<GameObjectManager>& worldManager, const std::wstring& name):transform()
{
	this->Name = name;
	this->Id = 0;
	mWorldManager = worldManager;
	mIsActive = true;
}

neo::object::GameObject::~GameObject()
{

}

void neo::object::GameObject::LastUpdate(const double& deltaTime)
{

}


bool neo::object::GameObject::GetIsActive() const
{
	return mIsActive;
}

void neo::object::GameObject::SetIsActive(const bool& active)
{
	this->mIsActive = active;
}

void neo::object::GameObject::Start()
{
	
}

void neo::object::GameObject::Update(const double& deltaTime)
{
	
}