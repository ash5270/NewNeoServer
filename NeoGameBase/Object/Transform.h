#pragma once
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
namespace neo::object
{
	struct Transform
	{
		math::Vector3 position;
		math::Vector3 rotation;
		math::Vector2 veloctiy;
	};
}
