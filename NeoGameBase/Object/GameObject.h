#pragma once
#include <memory>
#include <Windows.h>
#include "Object.h"
#include "GameObjectManager.h"
#include "Transform.h"

namespace neo::object
{
	class GameObject :public Object, public std::enable_shared_from_this<GameObject>
	{
	public:
		GameObject(const std::shared_ptr<GameObjectManager>& worldManager , const std::wstring& name);
		virtual ~GameObject();
	public:
		Transform transform;
	public:
		virtual void Start();
		virtual void Update(const double& deltaTime);
		virtual void LastUpdate(const double& deltaTime);

		const ::UUID& GetObjectUUID() const;
		bool GetIsActive() const;
		void SetIsActive(const bool& active);
	protected:
		std::weak_ptr<GameObjectManager> mWorldManager;
	private:
		bool mIsActive ={};
	};
}
