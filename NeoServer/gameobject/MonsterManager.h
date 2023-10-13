#pragma once
#include<list>
#include<json.hpp>
#include"GameObject.h"
#include"../ObjectManager.h"
#include"../database/DataBaseManager.h"
#include"MonsterObject.h"
namespace neo::object
{
	class MapData;
	class MonsterManager : public GameObject ,public std::enable_shared_from_this<MonsterManager>
	{
	public:
		MonsterManager(const std::weak_ptr<MapData>& mapData);
		~MonsterManager();

	public:
		void CreateMonster(const int& id);
		void Update(const double& deltaTime) override;
		void Start() override;
		void End() override;

		//���� objects 
		std::weak_ptr<MonsterObject> GetMonsterObject(const std::wstring& name);
		//
		std::unordered_map<std::wstring, std::weak_ptr<MonsterObject>>& GetMonsterDatas();
		nlohmann::json GetJsonGameObject();
		nlohmann::json GetJsonResponeGameObject();
		std::weak_ptr<MapData> GetMapData();
		int32_t monsterCode;
	private:
		//������Ʈ�� �� ������Ʈ �Ŵ������� ������ ��
		std::unordered_map<std::wstring,std::weak_ptr<MonsterObject>> mMonsters;
		std::weak_ptr<server::ObjectManager> mObjectManager;

		std::weak_ptr<MapData> mMap;
		MYSQL* db;
		double time =0 ;
		double resettime = 0;

	};
}
 