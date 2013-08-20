#include "Ray.h"


namespace Intersection
{

	Ray::Ray(SOC_Vector3 origin, SOC_Vector3 direction)
	{
		this->origin		= origin;
		this->direction		= direction;
	}

	Ray::~Ray(void)
	{
	}

	SOC_Vector3 Ray::GetPoint(float distance)
	{
		SOC_Vector3 dir;
		SOCVec3Normalize(&dir, &direction);
		dir *= distance;

		return dir;
	}

}