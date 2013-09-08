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
		Cone(void);

	public:
		bool Intersection(Sphere &sphere);
	};

}