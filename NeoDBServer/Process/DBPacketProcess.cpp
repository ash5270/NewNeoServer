#include "DBPacketProcess.h"

#include "../../NEOGameServer/Packet/PacketData.h"
#include "../DBServer/DBServer.h"
#include "../Packet/Packet.h"
#include "../Packet/PacketData.h"
#include "../Packet/PacketID.h"

#include "../DB/MYSQLConnectionPool.h"
#define NEW_PACKAGE(package,packet_type,session_type)\
const auto convertPackage = static_cast<neo::packet::db::Package*>(package.get());\
const auto requestPacket = static_cast<neo::packet::db::packet_type*>(convertPackage->packet.get());\
const auto requestSession = std::static_pointer_cast<neo::server::session_type>(session)\

neo::process::DBPacketProcess::DBPacketProcess() :PacketProcess(THREAD_COUNT),mRedisConnection("tcp://192.168.123.104:6379"){
	mFuncTables.insert({ static_cast<int>(packet::db::PacketID::PI_S_REQ_DB_LOGIN),
		std::bind(&DBPacketProcess::LoginUserProcess, this, std::placeholders::_1, std::placeholders::_2) });
	mFuncTables.insert({ static_cast<int>(packet::db::PacketID::PI_S_REQ_DB_CHANNEL_INFO),
			std::bind(&DBPacketProcess::ChannelReqProcess, this, std::placeholders::_1, std::placeholders::_2) });
	mFuncTables.insert({ static_cast<int>(packet::db::PacketID::PI_S_REQ_DB_CHAR_DATA),
			std::bind(&DBPacketProcess::CharacterReqProcess, this, std::placeholders::_1, std::placeholders::_2) });
	mFuncTables.insert({ static_cast<int>(packet::db::PacketID::PI_S_REQ_DB_ENTER_INGAME_CHAR_DATA),
		std::bind(&DBPacketProcess::InGamePlayerDataReqProcess, this, std::placeholders::_1, std::placeholders::_2) });
	mFuncTables.insert({ static_cast<int>(packet::db::PacketID::PI_S_REQ_DB_WORLD_MAP_INFO),
		std::bind(&DBPacketProcess::WorldMapReqProcess, this, std::placeholders::_1, std::placeholders::_2) });

	mFuncTables.insert({ static_cast<int>(packet::db::PacketID::PI_S_REQ_DB_ID_CREATE),
		std::bind(&DBPacketProcess::IDCreateProcess, this, std::placeholders::_1, std::placeholders::_2) });
	mFuncTables.insert({ static_cast<int>(packet::db::PacketID::PI_S_REQ_DB_ID_CHECK),
		std::bind(&DBPacketProcess::IDCheckProcess, this, std::placeholders::_1, std::placeholders::_2) });

}

neo::process::DBPacketProcess::~DBPacketProcess()
{
	
}

void neo::process::DBPacketProcess::LoginUserProcess(std::shared_ptr<network::IOCPSession> session,
	std::unique_ptr<IPacket> packet)
{
	NEW_PACKAGE(packet, P_S_REQ_DB_LOGIN, DBSession);
	LOG_PRINT(LOG_LEVEL::LOG_DEBUG, L"login  id : %s, password : %d\n", requestPacket->id.c_str(), requestPacket->password);
	auto idStr = std::string().assign(requestPacket->id.begin(),
		requestPacket->id.end());
	//여기서 이제 
	auto buffer = std::make_unique<char[]>(150);
	auto len = sprintf_s(buffer.get(), 150,
		"SELECT * FROM neo_server.user_info WHERE user_id  = \"%s\"",
		idStr.c_str());
	auto mysql = db::MYSQLConnectionPool::GetInstance().GetConnection();
	int result = mysql_query(mysql.GetMYSQL(), buffer.get());
	if (result)
	{
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"MYSQL SELECT ERROR\n");
		return;
	}

	MYSQL_RES* res = mysql_store_result(mysql.GetMYSQL());
	MYSQL_ROW row;
	string id;
	string name;
	string userID;
	string email;
	string password;
	while (row = mysql_fetch_row(res))
	{
		id = row[0];
		name = row[1];
		userID = row[2];
		email = row[3];
		password = row[4];
	}

	std::string loginPassword = std::string().assign(requestPacket->password.begin(), requestPacket->password.end());
	packet::db::P_S_RES_DB_LOGIN loginDB;
	loginDB.sessionId = requestPacket->sessionId;
	if(password== loginPassword)
	{
		const char* uuid = reinterpret_cast<char*>(&requestPacket->uuid);
		const string uuidStr = std::string(uuid,16);
		//mRedisConnection.set(sw::redis::StringView(uuid, sizeof(loginPacket->uuid)),userID );
		mRedisConnection.hset("login_user:"+userID, { "ip","192.168.123.101","time","xxxxxxxxxxxxx","uuid",uuid });
		mRedisConnection.hset("session_id:" + uuidStr, { "user_id",userID });
		
		memcpy_s(loginDB.uuid, sizeof(loginDB.uuid), requestPacket->uuid, sizeof(requestPacket->uuid));
		auto uudiStr = sw::redis::StringView(uuid, sizeof(requestPacket->uuid));
		loginDB.isLogin = true;
	}
	else
	{
		loginDB.isLogin = false;
	}
	 
	requestSession->SendPacket(loginDB);
	//해제
	mysql_free_result(res);
	db::MYSQLConnectionPool::GetInstance().FreeConnection(std::move(mysql));
	
}

void neo::process::DBPacketProcess::ChannelReqProcess(std::shared_ptr<network::IOCPSession> session,
	std::unique_ptr<IPacket> packet)
{
	NEW_PACKAGE(packet, P_S_RES_DB_CHANNEL_INFO, DBSession);
	auto buffer = std::make_unique<char[]>(150);
	auto len = sprintf_s(buffer.get(), 150,
		"SELECT * FROM neo_server.channel_info");

	auto mysql = db::MYSQLConnectionPool::GetInstance().GetConnection();
	const int result = mysql_query(mysql.GetMYSQL(), buffer.get());
	if (result)
	{
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"MYSQL SELECT ERROR\n");
	}

	MYSQL_RES* res = mysql_store_result(mysql.GetMYSQL());
	MYSQL_ROW row;
	vector<pair<string,string>> channel;
	while (row = mysql_fetch_row(res))
	{
		const std::string channelName(row[1]);
		const std::string channelID(row[0]);
		channel.push_back({ channelName,channelID });
		mRedisConnection.hset("channel_info:"+channelName,{"id",channelID.c_str(),"name",channelName.c_str()});
	}

	neo::packet::db::P_S_RES_DB_CHANNEL_INFO respone;
	respone.sessionId = requestPacket->sessionId;
	for(int i=0; i<channel.size(); i++)
	{
		const std::wstring channelName = std::wstring().assign(channel[i].first.begin(), channel[i].first.end());
		const std::wstring channelID = std::wstring().assign(channel[i].second.begin(), channel[i].second.end());
		respone.channelInfos.push_back({channelName,channelID});
	}
	requestSession->SendPacket(respone);

	mysql_free_result(res);
	db::MYSQLConnectionPool::GetInstance().FreeConnection(std::move(mysql));
}

void neo::process::DBPacketProcess::CharacterReqProcess(std::shared_ptr<network::IOCPSession> session,
	std::unique_ptr<IPacket> packet)
{
	NEW_PACKAGE(packet, P_S_REQ_DB_CHAR_DATA, DBSession);
	auto buffer = std::make_unique<char[]>(250);
	std::string id = std::string().assign(requestPacket->userId.begin(), requestPacket->userId.end());
	auto len = sprintf_s(buffer.get(), 250,
		"SELECT char_info_id ,char_weapon_id ,char_level, char_name,id  FROM  neo_server.user_character WHERE user_id IN(SELECT id FROM user_info WHERE user_id = '%s') AND channel_id  = %d",
		id.c_str(),requestPacket->channelId);

	auto mysql = db::MYSQLConnectionPool::GetInstance().GetConnection();
	const int result = mysql_query(mysql.GetMYSQL(), buffer.get());
	if (result)
	{
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"MYSQL SELECT ERROR\n");
	}

	MYSQL_RES* res = mysql_store_result(mysql.GetMYSQL());
	MYSQL_ROW row;
	std::vector<packet::db::DBCharSelectVeiwData> characterDatas;
	while (row = mysql_fetch_row(res))
	{
		const std::string charInfoId(row[0]);
		const std::string charWepaonId(row[1]);
		const std::string charLevel(row[2]);
		const std::string charName(row[3]);
		const std::string id(row[4]);
		const std::wstring name = std::wstring().assign(charName.begin(), charName.end());
		characterDatas.push_back({name,stoi(id),stoi(charInfoId),stoi(charWepaonId),stoi(charLevel)});
	}

	packet::db::P_S_RES_DB_CHAR_DATA responePacket;
	responePacket.sessionId = requestPacket->sessionId;
	responePacket.charViewDatas = characterDatas;
	requestSession->SendPacket(responePacket);

	mysql_free_result(res);
	db::MYSQLConnectionPool::GetInstance().FreeConnection(std::move(mysql));
}

void neo::process::DBPacketProcess::InGamePlayerDataReqProcess(std::shared_ptr<network::IOCPSession> session,
	std::unique_ptr<IPacket> packet)
{
	NEW_PACKAGE(packet, P_S_REQ_DB_ENTER_INGAME_CHAR_DATA, DBSession);
	auto buffer = std::make_unique<char[]>(250);
	auto len = sprintf_s(buffer.get(), 250,
		"SELECT char_info_id ,char_weapon_id ,char_level, char_name,char_pos_x ,char_pos_y ,char_exp ,char_hp ,char_max_hp,id,map_id  FROM  neo_server.user_character WHERE id = %d",requestPacket->characterId);
	auto mysql = db::MYSQLConnectionPool::GetInstance().GetConnection();
	const int result = mysql_query(mysql.GetMYSQL(), buffer.get());
	if (result)
	{
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"MYSQL SELECT ERROR\n");
	}

	MYSQL_RES* res = mysql_store_result(mysql.GetMYSQL());
	MYSQL_ROW row;
	neo::packet::db::P_S_RES_DB_ENTER_INGAME_CHAR_DATA respone;
	respone.sessionId = requestPacket->sessionId;

	while (row = mysql_fetch_row(res))
	{
		const std::string charName(row[3]);
		const std::wstring name = std::wstring().assign(charName.begin(), charName.end());
		respone.characterImageId = stoi(row[0]);
		respone.characterWeaponId = stoi(row[1]);
		respone.Level = stoi(row[2]);
		respone.characterName = name;
		respone.posX = stoi(row[4]);
		respone.posY = stoi(row[5]);
		respone.Hp = stoi(row[7]);
		respone.MaxHP = stoi(row[8]);
		respone.characterId = stoi(row[9]);
		respone.mapId = stoi(row[10]) ;
	}

	requestSession->SendPacket(respone);
	mysql_free_result(res);
	db::MYSQLConnectionPool::GetInstance().FreeConnection(std::move(mysql));
}

void neo::process::DBPacketProcess::WorldMapReqProcess(std::shared_ptr<network::IOCPSession> session,
	std::unique_ptr<IPacket> packet)
{
	NEW_PACKAGE(packet, P_S_REQ_DB_WORLD_MAP_INFO, DBSession);
	const char* query = "SELECT * FROM map_info";
	auto mysql = db::MYSQLConnectionPool::GetInstance().GetConnection();
	const int result = mysql_query(mysql.GetMYSQL(), query);
	if (result)
	{
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"MYSQL SELECT ERROR\n");
	}

	MYSQL_RES* res = mysql_store_result(mysql.GetMYSQL());
	MYSQL_ROW row;
	neo::packet::db::P_S_RES_DB_WORLD_MAP_INFO responePacket;
	while (row = mysql_fetch_row(res))
	{
		string id = row[0];
		string name = row[1];
		string monsterId = row[2];
		string monsterCount = row[3];

		std::wstring mapName = std::wstring().assign(name.begin(), name.end());
		responePacket.worldMapDatas.push_back({ stoi(id)-1,mapName,stoi(monsterId),stoi(monsterCount) });
	}

	requestSession->SendPacket(responePacket);
	mysql_free_result(res);
	db::MYSQLConnectionPool::GetInstance().FreeConnection(std::move(mysql));
}

void neo::process::DBPacketProcess::IDCheckProcess(std::shared_ptr<network::IOCPSession> session,
	std::unique_ptr<IPacket> packet)
{
	NEW_PACKAGE(packet, P_S_REQ_DB_ID_CHECK, DBSession);
	string idString = string().assign(requestPacket->id.begin(), requestPacket->id.end());
	auto buffer = std::make_unique<char[]>(250);
	auto len = sprintf_s(buffer.get(), 250,
		"SELECT user_id FROM user_info where user_id = '%s'", idString.c_str());
	auto mysql = db::MYSQLConnectionPool::GetInstance().GetConnection();
	const int result = mysql_query(mysql.GetMYSQL(), buffer.get());
	if (result)
	{
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"MYSQL SELECT ERROR\n");
	}

	MYSQL_RES* res = mysql_store_result(mysql.GetMYSQL());
	MYSQL_ROW row;

	packet::db::P_S_RES_DB_ID_CREATE response;
	response.sessionId = requestPacket->sessionId;
	if(res->row_count != 0 )
	{
		response.msg = L"ID Found...";
		response.statusCode = -1;
	}
	else
	{
		response.msg = L"ID Not Found...";
		response.statusCode = 0;
	}

	LOG_PRINT(LOG_LEVEL::LOG_INFO, L"respone packet : %s, status code : %d\n", response.msg.c_str(), response.statusCode);
	requestSession->SendPacket(response);
}

void neo::process::DBPacketProcess::IDCreateProcess(std::shared_ptr<network::IOCPSession> session,
	std::unique_ptr<IPacket> packet)
{
	NEW_PACKAGE(packet, P_S_REQ_DB_ID_CREATE, DBSession);
	string idString = string().assign(requestPacket->id.begin(), requestPacket->id.end());
	string pwString = string().assign(requestPacket->password.begin(), requestPacket->password.end());
	string nameString = string().assign(requestPacket->name.begin(), requestPacket->name.end());
	string emailString = string().assign(requestPacket->email.begin(), requestPacket->email.end());

	auto buffer = std::make_unique<char[]>(250);
	auto len = sprintf_s(buffer.get(), 250,
		"INSERT INTO user_info (user_name,user_id,user_email,user_password) VALUES ('%s','%s','%s','%s')", nameString.c_str(),idString.c_str(),emailString.c_str(), pwString.c_str());
	auto mysql = db::MYSQLConnectionPool::GetInstance().GetConnection();
	const int result = mysql_query(mysql.GetMYSQL(), buffer.get());
	if (result)
	{
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"MYSQL SELECT ERROR\n");
	}

	packet::db::P_S_RES_DB_ID_CREATE response;
	response.sessionId = requestPacket->sessionId;
	response.statusCode = 1;
	response.msg = L"id create success...";
	requestSession->SendPacket(response);
}

