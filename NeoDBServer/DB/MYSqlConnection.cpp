#include "MYSqlConnection.h"


neo::db::MYSqlConnection::MYSqlConnection()
{
	mConnection = mysql_init(0);
}

neo::db::MYSqlConnection::~MYSqlConnection()
{
	
}

void neo::db::MYSqlConnection::Connect()
{
	mConnection = mysql_real_connect(mConnection, MYSQL_IP.c_str(), MYSQL_ID.c_str(), MYSQL_PASSWORD.c_str(), MYSQL_DB.c_str(), MYSQL_PORT, NULL, 0);
	if(mConnection==nullptr)
	{
		LOG_PRINT(LOG_LEVEL::LOG_ERROR, L"mysql not connecting...\n");
	}
}

void neo::db::MYSqlConnection::Close()
{
	mysql_close(mConnection);
}
