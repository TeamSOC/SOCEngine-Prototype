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

float Math::DegreeToRadian(float degree)
{
	return degree * (SOCM_PI / 180.0f);
}

float Math::RadianToDegree(float radian)
{
	return radian * 180.0f / SOCM_PI;
}