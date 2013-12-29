#include "Math.h"


SOC_Vector3 Math::EulerNormalize(SOC_Vector3 eulerAngels)
{
	int x = (int)(eulerAngels.x / 360.0f);
	int y = (int)(eulerAngels.y / 360.0f);
	int z = (int)(eulerAngels.z / 360.0f);

	SOC_Vector3 e;//(eulerAngels.x - x * 360, eulerAngels.y - y * 360, eulerAngels.z - z * 360)
	e.x = eulerAngels.x - x * 360.0f + (int)(eulerAngels.x < 0) * 360.0f;
	e.y = eulerAngels.y - y * 360.0f + (int)(eulerAngels.y < 0) * 360.0f;
	e.z = eulerAngels.z - z * 360.0f + (int)(eulerAngels.z < 0) * 360.0f;

	return e;
}

//float Math::DegreeToRadian(float degree)
//{
//	return degree * (SOCM_PI / 180.0f);
//}
//
//float Math::RadianToDegree(float radian)
//{
//	return radian * 180.0f / SOCM_PI;
//}

float Math::Rad2Deg()
{
	return 180.0f / SOCM_PI;
}

float Math::Deg2Rad()
{
	return SOCM_PI / 180.0f;
}

//void Math::DegreeToRadian(SOC_Vector3 *out, SOC_Vector3 *degree)
//{
//	out->x = DegreeToRadian(degree->x);
//	out->y = DegreeToRadian(degree->y);
//	out->z = DegreeToRadian(degree->z);
//}
//
//void Math::RadianToDegree(SOC_Vector3 *out, SOC_Vector3 *radian)
//{
//	out->x = RadianToDegree(radian->x);
//	out->y = RadianToDegree(radian->y);
//	out->z = RadianToDegree(radian->z);
//}

SOC_Vector3 Math::QuaternionToEuler(SOC_Quaternion &quaternion)
{
	const float Epsilon = 0.0009765625f; 
	const float Threshold = 0.5f - Epsilon; 

	float yaw; 
	float pitch; 
	float roll; 

	float XY = quaternion.x * quaternion.y; 
	float ZW = quaternion.z * quaternion.w; 

	float TEST = XY + ZW; 

	if (TEST < -Threshold || TEST > Threshold)
	{ 
		int sign = TEST > 0 ? 1 : TEST == 0 ? 0 : -1;
		yaw  = sign * 2 * (float)atan2(quaternion.x, quaternion.w); 
		pitch = sign * SOCM_PI / 2.0f; 
		roll = 0; 
	}
	else
	{ 
		float XX = quaternion.x * quaternion.x; 
		float XZ = quaternion.x * quaternion.z; 
		float XW = quaternion.x * quaternion.w; 

		float YY = quaternion.y * quaternion.y; 
		float YW = quaternion.y * quaternion.w; 
		float YZ = quaternion.y * quaternion.z; 

		float ZZ = quaternion.z * quaternion.z; 

		yaw = (float)atan2(2 * YW - 2 * XZ, 1 - 2 * YY - 2 * ZZ); 

		pitch = (float)atan2(2 * XW - 2 * YZ, 1 - 2 * XX - 2 * ZZ); 

		roll = (float)asin(2 * TEST); 

	} 

	return SOC_Vector3(pitch, yaw, roll);
}