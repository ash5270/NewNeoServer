#pragma once
#include <system/NeoLog.h>
#include "IConnection.h"
#include "DBConfig.h"
namespace neo::db
{
	class MYSqlConnection : public IConnection
	{
	public:
		MYSqlConnection();
		~MYSqlConnection();
	public:
		void Connect() override;
		MYSQL* GetMYSQL()
		{
			return mConnection;
		}
		void Close() override;
	private:
		MYSQL* mConnection;
	};

}
