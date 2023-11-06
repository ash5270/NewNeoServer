#include "PlayerObject.h"


neo::object::PlayerObject::PlayerObject(const std::shared_ptr<GameObjectManager>& worldManager,
	const std::weak_ptr<neo::game::GameSession> session) :GameObject(worldManager, L""), mSession(session)
{
	//worldManager->AddGameObject(shared_from_this());
}

neo::object::PlayerObject::~PlayerObject()
{

}

void neo::object::PlayerObject::SetPosition(math::Vector2 pos,const int&  animationCode)
{
	this->transform.position = { pos.x,pos.y,0 };
	this->mPlayerData.animaionCode= animationCode;
}

void neo::object::PlayerObject::SetPosition(math::Vector2 pos)
{
	this->transform.position = { pos.x,pos.y,0 };
}


void neo::object::PlayerObject::SetPlayerData(const packet::game::PlayerData& data)
{
	this->transform.position = { data.posX,data.posY,0 };
	this->mPlayerData = data;
}

neo::packet::game::PlayerData& neo::object::PlayerObject::GetPlayerData()
{
	mPlayerData.posX = transform.position.x;
	mPlayerData.posY = transform.position.y;
	return mPlayerData;
}

std::weak_ptr<neo::game::GameSession> neo::object::PlayerObject::GetSession()
{
	return mSession;
}