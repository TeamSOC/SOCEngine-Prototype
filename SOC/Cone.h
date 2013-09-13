#pragma once

#include "Platform.h"
#include "Sphere.h"

namespace Intersection
{
	class Cone
	{
	public:
		float angle;
		float range;
		SOC_Vector3 axis;
		SOC_Vector3 vertex; //vertex

	public:
		Cone(void);
		Cone(float angle, float range, SOC_Vector3 axis, SOC_Vector3 vertex);

	public:
		static bool Intersection(Sphere &sphere, Cone &cone);

		bool Intersection(Sphere &sphere);
	};

}