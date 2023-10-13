#pragma once

namespace neo::db
{
	class IConnection
	{
	public:
		virtual void Connect() = 0;
		virtual void Close() = 0;
	};
}
