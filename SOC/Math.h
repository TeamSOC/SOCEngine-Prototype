#pragma once

#include "RenderingMath.h"

class Math
{
public:
	static SOC_Vector3 EulerNormalize(SOC_Vector3 eulerAngels);
	static float DegreeToRadian(float degree);
	static float RadianToDegree(float radian);
};

