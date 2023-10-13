#include<cmath>
#include "Vector2.h"
neo::math::Vector2::Vector2()
{
	x = y = 0;
}

neo::math::Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

neo::math::Vector2::Vector2(const Vector2& vector2)
{
	this->x = vector2.x;
	this->y = vector2.y;
}

neo::math::Vector2::Vector2(const neo::math::Vector3& vector3)
{
	this->x = vector3.x;
	this->y = vector3.y;
}

void neo::math::Vector2::operator+=(const Vector2& vector2)
{
	this->x += vector2.x;
	this->y += vector2.y;
}

void neo::math::Vector2::operator-=(const Vector2& vector2)
{
	this->x += vector2.x;
	this->y += vector2.y;
}

neo::math::Vector2 neo::math::Vector2::operator+(const Vector2& vector2)
{
	Vector2 new_vec = Vector2(x + vector2.x, y + vector2.y);
	return  new_vec;
}

neo::math::Vector2 neo::math::Vector2::operator-(const Vector2& vector2)
{
	Vector2 new_vec = Vector2(x + vector2.x, y + vector2.y);
	return  new_vec;
}

float neo::math::Vector2::Distance(const Vector2& a, const Vector2& b)
{
	float dis = ((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y));
	return sqrt(dis);
	//return 0;
}

neo::math::Vector2 neo::math::Vector2::Lerp(const Vector2& start, const Vector2 target, const float& d1)
{
	Vector2 result;
	result.x = (1 - d1) * start.x + d1 * target.x;
	result.y = (1 - d1) * start.y + d1 * target.y;
	return result;
}
