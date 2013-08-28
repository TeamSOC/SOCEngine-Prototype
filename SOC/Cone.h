#pragma once

#include "Rendering.h"
#include "Sphere.h"

namespace Intersection
{
	class Cone
	{
	public:
		float angle;
		float range;
		SOC_Vector3 axis;
		SOC_Vector3 center; //vertex

	public:
		Cone(void)
		{
			angle = 0.0f;
			range = 0.0f;

			axis = SOC_Vector3(0, 0, 0);
			center = SOC_Vector3(0, 0, 0);
		}

		~Cone(void)
		{

		}

	public:
		bool Intersection(Sphere &sphere)
		{
			float sinAngle = sin(angle);
			float cosAngle = cos(angle);

			float invSin = 1.0f / sinAngle;
			float cosSqr = cosAngle * cosAngle;

			SOC_Vector3 CmV = sphere.center - center;

			if(SOCVec3Length(&Cmv) < range)
				return false;

			SOC_Vector3 D = CmV + (sphere.radius * invSin) * axis;

			float DSqrLen = SOCVec3Length(&D);
			float e = SOCVec3Dot(&D, &axis);

			if( e > 0.0f && e * e >= DSqrLen * cosSqr )
			{
				float sinSqr = sinAngle * sinAngle;
				DSqrLen = CmV.x * CmV.x + CmV.y * CmV.y + CmV.z * CmV.z;
				e = -SOCVec3Dot(&CmV, &axis);

				if( e > 0.0f && e * e >= DSqrLen * sinSqr )
				{
					float rSqr = sphere.radius * sphere.radius;
					return DSqrLen <= rSqr;
				}

				return true;
			}

			return false;
		}

	};

}