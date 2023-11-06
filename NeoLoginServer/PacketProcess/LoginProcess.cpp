#include "LoginProcess.h"

#include "../LoginServer/LoginServer.h"
#include "../Packet/Packet.h"
#include "../Packet/PacketData.h"
#include "../Packet/PacketID.h"
#include "../LoginServer/S2SManager.h"
#include "../../NeoDBServer/Packet/Packet.h"
#include<rpcdce.h>
#pragma comment (lib, "Rpcrt4.lib")

#define NEW_PACKAGE(package,packet_type,session_type)\
const auto convertPackage = static_cast<::Package*>(package.get());\
const auto requestPacket = static_cast<::packet_type*>(convertPackage->packet.get());\
const auto requestSession = std::static_pointer_cast<neo::server::session_type>(session)\

using namespace neo::packet::login;

neo::process::LoginProcess::LoginProcess(const std::shared_ptr<SessionManager<server::LoginSession>>& manager)
	:PacketProcess(THREAD_COUNT), mSessionManager(manager)
{
	connection_options.host = "192.168.123.104";  // Required.
	connection_options.port = 6379; // Optional. The default port is 6379.
	mRedisConnection = std::make_shared<sw::redis::Redis>(connection_options);

	mFuncTables.insert({ static_cast<int>(PacketID::PI_C_REQ_LOGIN),
		std::bind(&LoginProcess::LoginUser, this, std::placeholders::_1, std::placeholders::_2) });

	mFuncTables.insert({ static_cast<int>(PacketID::PI_S_RES_DB_LOGIN),
		std::bind(&LoginProcess::LoginUserProcess, this, std::placeholders::_1, std::placeholders::_2) });

	mFuncTables.insert({ static_cast<int>(PacketID::PI_C_REQ_CHANNEL_INFO),
		std::bind(&LoginProcess::ChannelReqProcess, this, std::placeholders::_1, std::placeholders::_2) });

	mFuncTables.insert({ static_cast<int>(PacketID::PI_S_RES_DB_CHANNEL_INFO),
		std::bind(&LoginProcess::ChannelResProcess, this, std::placeholders::_1, std::placeholders::_2) });

	mFuncTables.insert({ static_cast<int>(PacketID::PI_C_REQ_CHAR_DATA),
		std::bind(&LoginProcess::CharacterReqProcess, this, std::placeholders::_1, std::placeholders::_2) });

	mFuncTables.insert({ static_cast<int>(PacketID::PI_S_RES_DB_CHAR_DATA),
		std::bind(&LoginProcess::CharacterResProcess, this, std::placeholders::_1, std::placeholders::_2) });

	mFuncTables.insert({ static_cast<int>(PacketID::PI_C_REQ_GAME_SERVER_INFO),
		std::bind(&LoginProcess::GameServerInfoReqProcess, this, std::placeholders::_1, std::placeholders::_2) });

	mFuncTables.insert({ static_cast<int>(PacketID::PI_C_REQ_CREATE_ID),
		std::bind(&LoginProcess::IDCreateProcess, this, std::placeholders::_1, std::placeholders::_2) });

	mFuncTables.insert({ static_cast<int>(PacketID::PI_C_REQ_CREATE_ID_CHECK),
		std::bind(&LoginProcess::IDCheckProcess, this, std::placeholders::_1, std::placeholders::_2) });

	mFuncTables.insert({ static_cast<int>(PacketID::PI_S_RES_DB_ID_CREATE),
		std::bind(&LoginProcess::IDCreateDBResponseProcess, this, std::placeholders::_1, std::placeholders::_2) });

}

neo::process::LoginProcess::~LoginProcess()
{
	mFuncTables.clear();
}

void neo::process::LoginProcess::LoginUser(std::shared_ptr<network::IOCPSession> session,
	std::unique_ptr<IPacket> packet)
{
	NEW_PACKAGE(packet, P_C_REQ_LOGIN, LoginSession);
	if (requestPacket->id.length() <= 6 || requestPacket->password.length() <= 6)
	{
		P_S_RES_LOGIN responPacket;
		responPacket.statusCode = -1;
		memset(responPacket.uuid, 0, 16);
		requestSession->SendPacket(responPacket);
		return;
	}

	LOG_PRINT(LOG_LEVEL::LOG_DEBUG, L"success login %s\n", requestPacket->id.c_str());
	std::string id = std::string().assign(requestPacket->id.begin(), requestPacket->id.end());
	std::unordered_map<std::string, std::string> user_;
	auto redisUUIDstr = mRedisConnection->hscan("login_user:" + id, 0, std::inserter(user_, user_.begin()));
	if (!user_.empty())
	{
		//이미 접속중인 아이디가 존재 한다
		const std::wstring ip = std::wstring().assign(user_["ip"].begin(), user_["ip"].end());
		const std::wstring time = std::wstring().assign(user_["time"].begin(), user_["time"].end());
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"아이디가 이미 존재합니다. id: %s, ip: %s, time: %s ....\n", requestPacket->id.c_str(), ip.c_str(), time.c_str());
		const std::string uuid(user_["uuid"], 0, 16);
		mRedisConnection->del("session_id:" + uuid);
	}

	UUID uuid;
	UuidCreate(&uuid);

	const auto dbServer = S2SManagerIns.GetClient(L"DBServer");
	if (dbServer && !dbServer->expired())
	{
		P_S_REQ_DB_LOGIN loginDB;
		loginDB.sessionId = requestSession->GetID();
		loginDB.id = requestPacket->id;
		loginDB.password = requestPacket->password;
		memcpy_s(loginDB.uuid, 16, &uuid, 16);
		dbServer->lock()->SendPacket(loginDB);
	}
}

void neo::process::LoginProcess::LoginUserProcess(std::shared_ptr<network::IOCPSession> session,
	std::unique_ptr<IPacket> packet)
{
	NEW_PACKAGE(packet, P_S_RES_DB_LOGIN, LoginSession);
	LOG_PRINT(LOG_LEVEL::LOG_DEBUG, L"login Success\n\n");

	const auto SendSession = mSessionManager->GetSession(requestPacket->sessionId);
	if (SendSession.has_value())
	{
		P_S_RES_LOGIN responPacket;
		if (requestPacket->isLogin)
		{
			memcpy_s(responPacket.uuid, sizeof(responPacket.uuid), requestPacket->uuid, sizeof(requestPacket->uuid));
			responPacket.statusCode = 1;
		}
		else
		{
			responPacket.statusCode = -1;
		}
		SendSession.value().lock()->SendPacket(responPacket);
	}
}

void neo::process::LoginProcess::ChannelReqProcess(std::shared_ptr<network::IOCPSession> session,
	std::unique_ptr<IPacket> packet)
{
	NEW_PACKAGE(packet, P_C_REQ_CHANNEL_INFO, LoginSession);
	//client uuid
	const char* clientUUIDstr = reinterpret_cast<const char*>(&requestPacket->uuid);
	std::string uuidStr(clientUUIDstr, 16);

	//아이디가 있다면
	std::unordered_map<std::string, std::string> user_;
	auto redisUUIDstr = mRedisConnection->hscan("session_id:" + uuidStr, 0, std::inserter(user_, user_.begin()));
	if (user_.empty())
	{
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"id in redis does not exist...\n");
		return;
	}

	UUID* clientUUID = (UUID*)(&clientUUIDstr);
	std::vector<std::string> channels;
	//scan으로 키값 확인하기
	mRedisConnection->scan(0, "channel_info:*", std::back_inserter(channels));
	if (!channels.empty())
	{
		//레디즈에 캐싱한 데이터가 있다면
		P_S_RES_CHANNEL_INFO responePacket;
		for (int i = 0; i < channels.size(); i++)
		{
			std::unordered_map<string, string> channelInfos;
			mRedisConnection->hscan(channels[i], 0, std::inserter(channelInfos, channelInfos.begin()));
			const std::wstring channelName = wstring().assign(channelInfos["name"].begin(), channelInfos["name"].end());
			const int channelID = stoi(channelInfos["id"]);
			const std::string idStr = "channel_user_count:" + channelInfos["id"];
			sw::redis::Optional<int> count = mRedisConnection->incrby(idStr, 0);
			responePacket.channelInfos.push_back({ channelName,channelID,count.value() });
		}
		requestSession->SendPacket(responePacket);
	}
	else
	{
		const auto dbServer = server::S2SManager::GetInstance().GetClient(L"DBServer");
		if (dbServer && !dbServer->expired())
		{
			P_S_REQ_DB_CHANNEL_INFO info;
			info.sessionId = requestSession->GetID();
			dbServer->lock()->SendPacket(info);
		}
	}
}

void neo::process::LoginProcess::ChannelResProcess(std::shared_ptr<network::IOCPSession> session,
	std::unique_ptr<IPacket> packet)
{
	NEW_PACKAGE(packet, P_S_RES_DB_CHANNEL_INFO, LoginSession);
	const auto SendSession = mSessionManager->GetSession(requestPacket->sessionId);
	if (SendSession.has_value())
	{
		P_S_RES_CHANNEL_INFO responPacket;
		for (int i = 0; i < requestPacket->channelInfos.size(); i++)
		{
			auto& data = requestPacket->channelInfos[i];
			std::string id = std::string().assign(data.channelId.begin(), data.channelId.end());
			sw::redis::Optional<int> count = mRedisConnection->incrby("channel_user_count:" + id, 0);
			responPacket.channelInfos.push_back({ data.name,stoi(id),count.value() });
		}
		SendSession.value().lock()->SendPacket(responPacket);
	}
}

void neo::process::LoginProcess::CharacterReqProcess(std::shared_ptr<network::IOCPSession> session,
	std::unique_ptr<IPacket> packet)
{
	NEW_PACKAGE(packet, P_C_REQ_CHAR_DATA, LoginSession);
	//로그인한 유저인지 확인하고
	auto userData = CheckLoginUser(requestPacket->uuid);
	if (userData.empty())
		return;
	std::string id = userData["user_id"];
	std::unordered_map<string, string> redisCharacterDatas;
	//캐싱된 데이터가 있는지 확인하고
	mRedisConnection->hscan("characters_id:" + id, 0, std::inserter(redisCharacterDatas, redisCharacterDatas.begin()));
	//없다면 DB서버에 문의
	if (redisCharacterDatas.empty() == true)
	{
		if (const auto dbServer = server::S2SManager::GetInstance().GetClient(L"DBServer"); !dbServer->expired())
		{
			P_S_REQ_DB_CHAR_DATA responePacket;
			responePacket.sessionId = requestSession->GetID();
			responePacket.channelId = requestPacket->channelID;
			responePacket.userId = std::wstring().assign(id.begin(), id.end());
			dbServer.value().lock()->SendPacket(responePacket);
		}
		else
		{
			LOG_PRINT(LogType::LOG_ERROR, L"DBServer does not exist...\n");
		}
	}
	//캐싱이 되어있다면 여기서 데이터 다시 조립해서 보내기
	else
	{
		vector<CharSelectVeiwInfo> characterInfos;
		for (int i = 0; i < redisCharacterDatas.size(); i++)
		{

		}
	}
}


void neo::process::LoginProcess::CharacterResProcess(std::shared_ptr<network::IOCPSession> session,
	std::unique_ptr<IPacket> packet)
{
	NEW_PACKAGE(packet, P_S_RES_DB_CHAR_DATA, LoginSession);
	const auto SendSession = mSessionManager->GetSession(requestPacket->sessionId);
	if (SendSession.has_value())
	{
		P_S_RES_CHAR_DATA responPacket;
		for (int i = 0; i < requestPacket->charViewDatas.size(); i++)
		{
			const auto& characters = requestPacket->charViewDatas;
			responPacket.charViewInfos.push_back({
				characters[i].name,
				characters[i].id,
				characters[i].characterWeaponId,
				characters[i].characterLevel
				});
		}
		SendSession.value().lock()->SendPacket(responPacket);
	}
	else
	{
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"Session does not exist..\n");
	}
}

void neo::process::LoginProcess::GameServerInfoReqProcess(std::shared_ptr<network::IOCPSession> session,
	std::unique_ptr<IPacket> packet)
{
	NEW_PACKAGE(packet, P_C_REQ_GAME_SERVER_INFO, LoginSession);
	P_S_RES_GAME_SERVER_INFO respone;
	respone.ip = mGameServerIP;
	respone.port = mGameServerPort;
	requestSession->SendPacket(respone);
}

void neo::process::LoginProcess::IDCreateProcess(std::shared_ptr<network::IOCPSession> session,
	std::unique_ptr<IPacket> packet)
{
	NEW_PACKAGE(packet, P_C_REQ_CREATE_ID, LoginSession);
	if(requestPacket->password!=requestPacket->passwordCheck)
	{
		P_S_RES_CREATE_ID response;
		response.statusCode = -1;
		response.msg = L"password not compare...";
		requestSession->SendPacket(response);
	}
	else if (const auto dbServer = server::S2SManager::GetInstance().GetClient(L"DBServer"); !dbServer->expired())
	{
		P_S_REQ_DB_ID_CREATE responsePacket;
		responsePacket.id = requestPacket->id;
		responsePacket.email = requestPacket->email;
		responsePacket.name = requestPacket->name;
		responsePacket.password = requestPacket->password;
		responsePacket.sessionId = requestSession->GetID();
		dbServer.value().lock()->SendPacket(responsePacket);
	}
}

void neo::process::LoginProcess::IDCheckProcess(std::shared_ptr<network::IOCPSession> session,
	std::unique_ptr<IPacket> packet)
{
	NEW_PACKAGE(packet, P_C_REQ_CREATE_ID_CHECK, LoginSession);
	if (const auto dbServer = server::S2SManager::GetInstance().GetClient(L"DBServer"); !dbServer->expired())
	{
		P_S_REQ_DB_ID_CHECK responsePacket;
		responsePacket.id = requestPacket->id;
		responsePacket.sessionId = requestSession->GetID();
		dbServer.value().lock()->SendPacket(responsePacket);
	}
}

void neo::process::LoginProcess::IDCreateDBResponseProcess(std::shared_ptr<network::IOCPSession> session,
	std::unique_ptr<IPacket> packet)
{
	NEW_PACKAGE(packet, P_S_RES_DB_ID_CREATE, S2SSession);
	const auto clientSession = mSessionManager->GetSession(requestPacket->sessionId);
	if (clientSession.has_value())
	{
		P_S_RES_CREATE_ID responsePacket;
		responsePacket.msg = requestPacket->msg;
		responsePacket.statusCode = requestPacket->statusCode;
		clientSession->lock()->SendPacket(responsePacket);
	}
}

std::unordered_map<std::string, std::string> neo::process::LoginProcess::CheckLoginUser(uint8_t* uuid)
{
	std::string uuidStr(reinterpret_cast<char*>(uuid), 16);
	std::unordered_map<std::string, std::string> user_;
	auto redisUUIDstr = mRedisConnection->hscan("session_id:" + uuidStr, 0, std::inserter(user_, user_.begin()));
	if (user_.empty())
	{
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"id nothing in redis...\n");
	}
	return user_;
}
