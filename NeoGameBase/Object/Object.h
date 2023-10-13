#pragma once
#include<string>
namespace neo::object
{
	struct Object
	{
	protected:
		~Object() = default;

	public:
		std::wstring Name;
		std::int32_t Id;
	};
}
