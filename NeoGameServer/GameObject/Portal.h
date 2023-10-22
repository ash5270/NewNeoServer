#pragma once
#include <Math/Vector3.h>
namespace  neo::object
{
	class Portal
	{
	public:
		Portal(const int32_t& enter,const int32_t& exit, const math::Vector3& spawnPoint)
			:mEnterMap(enter),mExitMap(exit),mSpawnPoint(spawnPoint)
		{
			
		}
		~Portal() = default;

		math::Vector3 GetSpawnPoint() const
		{
			return mSpawnPoint;		}

	private:
		int32_t mEnterMap;
		int32_t mExitMap;
		math::Vector3 mSpawnPoint;
	};
}
