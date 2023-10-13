#pragma once
//이름 그대로 connect pool
//미리 DB에 접속해둬어 사용하기
//
#include <Singleton.h>
#include <vector>
#include <queue>
namespace neo::db
{
	template<class _Connection,class _Pool>
	class ConnectionPool : public Singleton<_Pool>
	{
	public:
		void Init(size_t connectionSize);
		void Stop();
		_Connection GetConnection();
		void FreeConnection(_Connection&& connection);
	private:
		std::queue<_Connection> mConnections;
	};

	template <class _Connection, class _Pool>
	inline void ConnectionPool<_Connection, _Pool>::Init(size_t connectionSize)
	{
		for(int i=0; i<connectionSize; i++)
		{
			_Connection connection;
			mConnections.push(connection);
			connection.Connect();
		}
	}

	template <class _Connection, class _Pool>
	inline void ConnectionPool<_Connection, _Pool>::Stop()
	{
		for(int i=0; i<mConnections.size(); i++)
		{
			auto connection = mConnections.front();
			connection.Close();
			mConnections.pop();
		}
	}

	template <class _Connection, class _Pool>
	_Connection ConnectionPool<_Connection, _Pool>::GetConnection()
	{
		auto connection = mConnections.front();
		mConnections.pop();
		return std::move(connection);
	}

	template <class _Connection, class _Pool>
	void ConnectionPool<_Connection, _Pool>::FreeConnection(_Connection&& connection)
	{
		mConnections.push(std::move(connection));
	}
}
