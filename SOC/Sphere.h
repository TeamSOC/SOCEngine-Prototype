#pragma once

#include "Rendering.h"

namespace Intersection
{
	struct Sphere
	{
	public:
		SOC_Vector3 center;
		float radius;

	public:
		Sphere(void);
		Sphere(SOC_Vector3 center, float radius);

	public:
		static bool Intersection(Sphere &sphere1, Sphere &sphere2);
		static bool Intersection(SOC_Vector3 p1, float radius1, SOC_Vector3 p2, float radius2);

		bool Intersection(Sphere &sphere);
	};

}