#pragma once

#include "Platform.h"

#include "Ray.h"

namespace Intersection
{
	class AABB
	{
	private:
		SOC_Vector3 center;
		SOC_Vector3 size;
		SOC_Vector3 extents;
		SOC_Vector3 min;
		SOC_Vector3 max;

	public:
		AABB();
		AABB(SOC_Vector3 worldCenter, SOC_Vector3 size);
		~AABB(void);

	public:
		void SetMinMax(SOC_Vector3 min, SOC_Vector3 max);

		void Expand(float amount);
		void Expand(SOC_Vector3 amount);

		bool Intersects(AABB bounds);
		bool Contains(SOC_Vector3 point);
		
		float SqrDistance(SOC_Vector3 point);

		bool Intersects(Ray ray, SOC_Vector3 *outPickPoint = NULL, float gap = 0.0);

	public:
		bool operator!=(AABB &box);
		bool operator==(AABB &box);
	};

}