#include "S2SManager.h"

void neo::server::S2SManager::AddS2SClient(const std::wstring& clientName, HANDLE* iocpHandle, const std::string& ip,
	const int& port)
{
	if (mS2SClients.find(clientName) == mS2SClients.end())
	{
		auto client = std::make_shared<S2SClient>(iocpHandle, ip, port);
		mS2SClients.insert({clientName,client });
		client->StartConnect();
	}
}

void neo::server::S2SManager::RemoveS2SClient(const std::wstring& clientName)
{
	if (mS2SClients.find(clientName) != mS2SClients.end())
	{
		mS2SClients.erase(clientName);
	}
}

std::optional<std::weak_ptr<neo::server::S2SClient>> neo::server::S2SManager::GetClient(const std::wstring& clientName)
{
	if (mS2SClients.find(clientName) != mS2SClients.end())
	{
		return mS2SClients[clientName];
	}
	else
	{
		return nullopt;
	}
}
