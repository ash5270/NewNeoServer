#include "MonsterManager.h"

#include"MapData.h"

neo::object::MonsterManager::MonsterManager(const std::weak_ptr< object::MapData>& mapData):mMap(mapData),monsterCode(0),resettime(0)
{
	db = db::DataBaseManager::GetInstance().GetNewConnection();
}

neo::object::MonsterManager::~MonsterManager()
{
	mysql_close(db);
}

void neo::object::MonsterManager::CreateMonster(const int& id)
{
	if (db)
	{
		std::string query = "SELECT monster_count,monster_info.monster_code,monster_name,monster_damage,monster_hp,monster_exp FROM map_info INNER JOIN monster_info ON map_info.monster_code = monster_info.id where map_info.id =";
		query += to_string(id);

		MYSQL_RES* res;
		MYSQL_ROW row;

		int result = mysql_query(db, query.c_str());
		if (!result)
		{
			res = mysql_store_result(db);
			row = mysql_fetch_row(res);
			std::string monsterCount = row[0];
			std::string monsterCodestr = row[1];
			std::string monsterName = row[2];
			std::string monsterDamage = row[3];
			std::string monsterHp = row[4];
			std::string monsterExp = row[5];
			
			auto count = std::stoi(monsterCount);
			auto damage = std::stoi(monsterDamage);
			auto hp = std::stoi(monsterHp);

			/*LOG_PRINT(LOG_LEVEL::LOG_INFO, L"map name : %s, monster code : %s, monster count : %d, hp : %d\n",
				monsterName.c_str(),monsterCode.c_str(), count,hp);*/
			
			std::wstring wmonsterName;
			wmonsterName.assign(monsterName.begin(), monsterName.end());
			monsterCode = std::stoi(monsterCodestr);
			auto objectManagerPtr = this->Manager.lock();
			for (int i = 0; i < count; i++)
			{
				wstring name = wmonsterName;
				name.append(to_wstring(i));
				std::shared_ptr<GameObject> monster =
					std::make_shared<MonsterObject>();
				objectManagerPtr->RegisterObject(name, monster);
				auto monsterPtr =
					std::dynamic_pointer_cast<MonsterObject>(monster);
				mMonsters.insert({ name,monsterPtr });
				monsterPtr->SetHp(hp);
				monsterPtr->SetDamage(damage);
				monsterPtr->MonsterManager = weak_from_this();
				monsterPtr->SetExp(std::stoi(monsterExp));
			}
		}

		
	}
	else
	{
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"db not connect....\n");
	}
}

void neo::object::MonsterManager::Update(const double& deltaTime)
{
	bool respone = false;
	resettime += deltaTime;

	P_S_NOTIFY_MONSTER_POSITION positions;
	for (const auto& monster : mMonsters)
	{ 
		if (!monster.second.lock()->GetActive())
			continue;

		MonsterData data;
		data.animation = 0;
		data.name = monster.second.lock()->Name;
		data.position = monster.second.lock()->transform.position.GetPVector3();
		data.veleocity = Vector2(0, 0).GetPVector2();
		data.speed = 10;
		positions.monsterDatas.push_back(data);
	}



	if (resettime > 20.0f)
	{
		resettime = 0.0f;
		for (const auto& monster : mMonsters)
		{
			if (!monster.second.lock()->GetActive())
			{
				monster.second.lock()->ResetMonster();
				respone = true;
			}
		}
	}

	P_S_NOTIFY_MONSTER_INFO monsterInfos;
	if (respone)
	{
		monsterInfos.monsterCode = monsterCode;
		monsterInfos.msg = L"success";

		for(const auto& monster : mMonsters)
		{
			MonsterInfo info;
			if(!monster.second.expired())
				break;
			auto monsterPtr = monster.second.lock();
			info.hp = monsterPtr->GetHp();
			info.name = monsterPtr->Name;
			info.x = monsterPtr->transform.position.x;
			info.y = monsterPtr->transform.position.y;
			monsterInfos.monsterDatas.push_back(info);
		}
	}
	
	for (const auto& player : mMap.lock()->GetInMapPlayers())
	{
		auto copyPacket = positions;
		player.second.lock()->Session->SendPacket(copyPacket);

		if (respone)
		{
			auto copyMonsterNewPacket = monsterInfos;
			player.second.lock()->Session->SendPacket(copyMonsterNewPacket);
		}
	}
}

void neo::object::MonsterManager::Start()
{

}

void neo::object::MonsterManager::End()
{

}

std::weak_ptr<neo::object::MonsterObject> neo::object::MonsterManager::GetMonsterObject(const std::wstring& name)
{
	if (mMonsters.find(name) != mMonsters.end())
		return mMonsters[name];
	else
		return	std::weak_ptr<neo::object::MonsterObject>();
}

std::unordered_map<std::wstring, std::weak_ptr<neo::object::MonsterObject>>& neo::object::MonsterManager::
GetMonsterDatas()
{
	return  mMonsters;
}

nlohmann::json neo::object::MonsterManager::GetJsonGameObject()
{
	nlohmann::json root;
	nlohmann::json array;
	for (auto const& object : mMonsters)
	{
		auto monster = object.second.lock();
		nlohmann::json Monster;
		Monster["name"] = std::string().assign(
			monster->Name.begin(),
			monster->Name.end());
		Monster["posX"] = monster->transform.position.x;
		Monster["posY"] = monster->transform.position.y;
		Monster["hp"] = monster->GetHp();
		array.push_back(std::move(Monster));

	}
	root["array"] = array;
	return root;
}

nlohmann::json neo::object::MonsterManager::GetJsonResponeGameObject()
{
	nlohmann::json root;
	nlohmann::json array;
	for (auto const& object : mMonsters)
	{
		if (!object.second.lock()->GetActive())
		{
			auto monster = object.second.lock();
			nlohmann::json Monster;
			Monster["name"] = std::string().assign(
				monster->Name.begin(),
				monster->Name.end());
			Monster["posX"] = monster->transform.position.x;
			Monster["posY"] = monster->transform.position.y;
			Monster["hp"] = monster->GetHp();
			object.second.lock()->SetActive(true);
			array.push_back(std::move(Monster));
		}
	}
	root["array"] = array;
	return root;
}

std::weak_ptr<neo::object::MapData> neo::object::MonsterManager::GetMapData()
{
	return mMap;
}
