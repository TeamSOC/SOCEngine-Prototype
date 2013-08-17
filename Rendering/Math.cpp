#include "Math.h"
#include <math.h>

namespace Math
{
	SOC_Vector3 Tool::QuaternionToEuler(SOC_Quaternion quaternion)
	{
		float pitch, roll, yaw;

		float test = quaternion.x * quaternion.y + quaternion.z * quaternion.w;

		if(test > 0.499f) //위 보고 있을때
		{
			roll =  2 * atan2f(quaternion.x, quaternion.w);
			pitch = SOCM_PI / 2.0f;
			yaw = 0;

			return SOC_Vector3(pitch, yaw, roll);
		}

		else if(test < -0.499) //아래보고 있을때
		{
			roll = -2 * atan2f(quaternion.x, quaternion.w);
			pitch = - SOCM_PI / 2.0f;
			yaw = 0;

			return SOC_Vector3(pitch, yaw, roll);
		}

		SOC_Vector3 sq = SOC_Vector3(quaternion.x*quaternion.x, quaternion.y*quaternion.y, quaternion.z*quaternion.z);

		roll = atan2f( (2 * quaternion.y * quaternion.w) - (2 * quaternion.x * quaternion.z), 1 - (2 * sq.y - 2 * sq.z));
		pitch = asin(2 * test);
		yaw = atan2( (2 * quaternion.x * quaternion.w) - (2 * quaternion.y * quaternion.z), 1 - (2 * sq.x - 2 * sq.z));

		return SOC_Vector3(pitch, yaw, roll);

	}

	SOC_Vector3 Tool::EulerNormalize(SOC_Vector3 eulerAngels)
	{
		int x = (int)(eulerAngels.x / 360.0f);
		int y = (int)(eulerAngels.y / 360.0f);
		int z = (int)(eulerAngels.z / 360.0f);

		return SOC_Vector3(eulerAngels.x - x * 360, eulerAngels.y - y * 360, eulerAngels.z - z * 360);
	}

	float Tool::Lerp(float a, float b, float t)
	{
		return a - (a * t) + (b * t);
	}

	float Tool::Distance(SOC_Vector3 p1, SOC_Vector3 p2)
	{
		return sqrtf( powf((p2.x - p1.x), 2.0f) + powf((p2.y - p1.y), 2.0f) + powf((p2.z - p1.z), 2.0f) ); 
	}

}