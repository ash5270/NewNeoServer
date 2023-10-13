#pragma once
#include<system/InputMemoryStream.h>
#include<system/OutputMemoryStream.h>
using namespace neo::system;namespace neo::packet::db {


enum class PacketID : int32_t {

	PI_C_NOTIFY_PING=1,
	PI_S_NOTIFY_PING=2,
	PI_C_NOTIFY_RTT=3,
	PI_S_NOTIFY_RTT=4,
	PI_C_REQ_GAME_SERVER_INFO=10,
	PI_S_RES_GAME_SERVER_INFO=11,
	PI_C_UPDATE_CHAR_POSITION=100,
	PI_S_NOTIFY_CHAR_POSITION=200,
	PI_S_NOTIFY_CHAR_UPDATE=201,
	PI_S_NOTIFY_MONSTER_POSITION=300,
	PI_S_CLOSE_WORLD=400,
	PI_S_RES_LOGOUT=1000,
	PI_C_REQ_LOGOUT=1001,
	PI_C_REQ_LOGIN=1002,
	PI_S_RES_LOGIN=1100,
	PI_C_REQ_CHANNEL_INFO=3000,
	PI_S_RES_CHANNEL_INFO=3001,
	PI_C_REQ_CHAR_DATA=3010,
	PI_S_RES_CHAR_DATA=3011,
	PI_C_REQ_ENTER_INGAME_CHAR_DATA=3020,
	PI_S_RES_ENTER_INGAME_CHAR_DATA=3021,
	PI_C_REQ_CHAR_DATA_DEL=3030,
	PI_S_RES_CHAR_DATA_DEL=3031,
	PI_C_REQ_CHAR_DATA_CRE=3032,
	PI_S_RES_CHAR_DATA_CRE=3033,
	PI_C_REQ_WORLD_ENTER_THE_SERVER=4000,
	PI_S_RES_WORLD_CHARACTERS=4001,
	PI_S_RES_WORLD_MONSTERS=4002,
	PI_S_RES_WORLD_PLAYER_DATA=4003,
	PI_S_NOTIFY_LEAVE_WORLD_PLAYER=4004,
	PI_C_REQ_LEAVE_MAP=4011,
	PI_C_REQ_ENTER_MAP=4012,
	PI_C_RES_ENTER_MAP=4013,
	PI_S_REQ_DB_LOGIN=10000,
	PI_S_RES_DB_LOGIN=10001,
	PI_S_REQ_DB_CHANNEL_INFO=20010,
	PI_S_RES_DB_CHANNEL_INFO=20011,
	PI_S_REQ_DB_CHAR_DATA=20020,
	PI_S_RES_DB_CHAR_DATA=20021,
	PI_S_REQ_DB_CHAR_DATA_DEL=20022,
	PI_S_RES_DB_CHAR_DATA_DEL=20023,
	PI_S_REQ_DB_CHAR_DATA_CRE=20024,
	PI_S_RES_DB_CHAR_DATA_CRE=20025,
	PI_S_REQ_DB_ENTER_INGAME_CHAR_DATA=20100,
	PI_S_RES_DB_ENTER_INGAME_CHAR_DATA=20101,
	PI_S_REQ_DB_WORLD_MAP_INFO=20110,
	PI_S_RES_DB_WORLD_MAP_INFO=20111,
};
}
