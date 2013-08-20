#pragma once

#include "Rendering.h"

namespace Math
{
	class Tool
	{
	public:
		static SOC_Vector3 QuaternionToEuler(SOC_Quaternion quaternion);
		static SOC_Vector3 EulerNormalize(SOC_Vector3 eulerAngels);

		static float Lerp(float a, float b, float t);

		static float Distance(SOC_Vector3 p1, SOC_Vector3 p2);
	};
};