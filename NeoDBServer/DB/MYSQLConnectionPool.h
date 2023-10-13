#pragma once
//이름 그대로 connect pool
//미리 DB에 접속해둬어 사용하기
//

#include "ConnectionPool.h"
#include "MYSqlConnection.h"

namespace neo::db
{
	class MYSQLConnectionPool :public ConnectionPool<MYSqlConnection,MYSQLConnectionPool>
	{
	public:
	};

}
