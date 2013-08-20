#pragma once

#include "Rendering.h"

namespace Intersection
{
	struct Sphere
	{
	public:
		SOC_Vector3 p;
		float radius;

	public:
		Sphere(void)
		{
			p = SOC_Vector3(0, 0, 0);
			radius = 0.0f;
		}

		Sphere(SOC_Vector3 p, float radius)
		{
			this->p = p;
			this->radius = radius;
		}

	public:
		static bool Intersection(Sphere &sphere1, Sphere &sphere2)
		{
			SOC_Vector3 between = sphere1.p - sphere2.p;
			float distance = SOCVec3Length(&between);

			if(distance < (sphere1.radius + sphere2.radius) )
				return false;

			return true;
		}
		static bool Intersection(SOC_Vector3 p1, float radius1, SOC_Vector3 p2, float radius2)
		{
			SOC_Vector3 between = p1 - p2;
			float distance = SOCVec3Length(&between);

			if(distance < (radius1 + radius2) )
				return false;

			return true;
		}

		bool Intersection(Sphere &sphere)
		{
			return Sphere::Intersection( (*this), sphere );
		}
	};

}