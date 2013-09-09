#include "Sphere.h"

namespace Intersection
{
	Sphere::Sphere(void)
	{
		center = SOC_Vector3(0, 0, 0);
		radius = 0.0f;
	}

	Sphere::Sphere(SOC_Vector3 center, float radius)
	{
		this->center = center;
		this->radius = radius;
	}

	bool Sphere::Intersection(Sphere &sphere1, Sphere &sphere2)
	{
		SOC_Vector3 between = sphere1.center - sphere2.center;
		float distance = SOCVec3Length(&between);

		if(distance < (sphere1.radius + sphere2.radius) )
			return false;

		return true;
	}

	bool Sphere::Intersection(SOC_Vector3 p1, float radius1, SOC_Vector3 p2, float radius2)
	{
		SOC_Vector3 between = p1 - p2;
		float distance = SOCVec3Length(&between);

		if(distance < (radius1 + radius2) )
			return false;

		return true;
	}

	bool Sphere::Intersection(Sphere &sphere)
	{
		return Sphere::Intersection( (*this), sphere );
	}

	bool Sphere::Intersection(SOC_Vector3 center, float radius)
	{
		return Sphere::Intersection( (*this), Sphere(center, radius) );
	}
}