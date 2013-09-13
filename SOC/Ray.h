#pragma once

#include "Platform.h"

namespace Intersection
{
	struct Ray
	{
	public:
		SOC_Vector3 origin;
		SOC_Vector3 direction;

	public:
		Ray(SOC_Vector3 origin, SOC_Vector3 direction);
		~Ray(void);

	public:
		SOC_Vector3 GetPoint(float distance);
	};
}