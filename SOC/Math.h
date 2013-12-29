#pragma once

#include "RenderingMath.h"

class Math
{
public:
	static SOC_Vector3 EulerNormalize(SOC_Vector3 eulerAngels);

	//static float DegreeToRadian(float degree);
	//static float RadianToDegree(float radian);

	//static void DegreeToRadian(SOC_Vector3 *out, SOC_Vector3 *degree);
	//static void RadianToDegree(SOC_Vector3 *out, SOC_Vector3 *radian);

	//http://xboxforums.create.msdn.com/forums/p/4574/23763.aspx
	static SOC_Vector3 QuaternionToEuler(SOC_Quaternion &quaternion);

public:
	static float Rad2Deg();
	static float Deg2Rad();
};

