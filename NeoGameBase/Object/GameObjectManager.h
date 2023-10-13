#pragma once
#include <memory>
#include <vector>
#include <queue>
#include <string>

namespace neo::object
{
	//월드당 오브젝트
	class GameObject;
	class GameObjectManager
	{
	public:
		GameObjectManager(const std::wstring& name);
		~GameObjectManager();
	public:
		void Start();
		void Update(const double& deltaTime);
		
		void AddGameObject(const std::shared_ptr<GameObject>& gameObject);
		void RemoveGameObject(const std::shared_ptr<GameObject>& gameObject);
		void RemoveGameobject(const int& id);
		std::vector<std::shared_ptr<GameObject>>& GetGameObjects();
	private:
		std::vector<std::shared_ptr<GameObject>> mGameObjects;
		std::queue<int> mRemoveObjectIds;
		std::wstring mName;

	};
}
