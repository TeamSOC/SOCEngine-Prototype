#pragma once

#include <d3dx9.h>

namespace Math
{
	class Tool
	{
	public:
		static D3DXVECTOR3 QuaternionToEuler(D3DXQUATERNION quaternion);
		static D3DXVECTOR3 EulerNormalize(D3DXVECTOR3 eulerAngels);

		static float Lerp(float a, float b, float t);

		static float Distance(D3DXVECTOR3 p1, D3DXVECTOR3 p2);
	};
};