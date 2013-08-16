#include "Math.h"
#include <math.h>

namespace Math
{
	D3DXVECTOR3 Tool::QuaternionToEuler(D3DXQUATERNION quaternion)
	{
		float pitch, roll, yaw;

		float test = quaternion.x * quaternion.y + quaternion.z * quaternion.w;

		if(test > 0.499f) //위 보고 있을때
		{
			roll =  2 * atan2f(quaternion.x, quaternion.w);
			pitch = D3DX_PI / 2.0f;
			yaw = 0;

			return D3DXVECTOR3(pitch, yaw, roll);
		}

		else if(test < -0.499) //아래보고 있을때
		{
			roll = -2 * atan2f(quaternion.x, quaternion.w);
			pitch = - D3DX_PI / 2.0f;
			yaw = 0;

			return D3DXVECTOR3(pitch, yaw, roll);
		}

		D3DXVECTOR3 sq = D3DXVECTOR3(quaternion.x*quaternion.x, quaternion.y*quaternion.y, quaternion.z*quaternion.z);

		roll = atan2f( (2 * quaternion.y * quaternion.w) - (2 * quaternion.x * quaternion.z), 1 - (2 * sq.y - 2 * sq.z));
		pitch = asin(2 * test);
		yaw = atan2( (2 * quaternion.x * quaternion.w) - (2 * quaternion.y * quaternion.z), 1 - (2 * sq.x - 2 * sq.z));

		return D3DXVECTOR3(pitch, yaw, roll);

	}

	D3DXVECTOR3 Tool::EulerNormalize(D3DXVECTOR3 eulerAngels)
	{
		int x = (int)(eulerAngels.x / 360.0f);
		int y = (int)(eulerAngels.y / 360.0f);
		int z = (int)(eulerAngels.z / 360.0f);

		return D3DXVECTOR3(eulerAngels.x - x * 360, eulerAngels.y - y * 360, eulerAngels.z - z * 360);
	}

	float Tool::Lerp(float a, float b, float t)
	{
		return a - (a * t) + (b * t);
	}

	float Tool::Distance(D3DXVECTOR3 p1, D3DXVECTOR3 p2)
	{
		return sqrtf( powf((p2.x - p1.x), 2.0f) + powf((p2.y - p1.y), 2.0f) + powf((p2.z - p1.z), 2.0f) ); 
	}

}