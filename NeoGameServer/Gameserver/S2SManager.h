#pragma once
#include <optional>
#include <Singleton.h>
#include <string>
#include <unordered_map>
#include "S2SClient.h"
#include <packetprocess/LogicProcess.h>
namespace neo::server
{
	class S2SManager: public Singleton<S2SManager> 
	{
	public:
		void AddS2SClient(const std::wstring& clientName,
			HANDLE* iocpHandle,
			const std::string& ip,
			const int& port);

		void RemoveS2SClient(const std::wstring& clientName);
		std::optional<std::weak_ptr<S2SClient>> GetClient(const std::wstring& clientName);

	private:
		std::unordered_map<std::wstring, std::shared_ptr<S2SClient>> mS2SClients;
	};

	#define S2SManagerIns neo::server::S2SManager::GetInstance()
}
