#pragma once

#include <d3d9.h>
#include <d3dx9.h>

namespace Intersection
{
	struct Ray
	{
	public:
		D3DXVECTOR3 origin;
		D3DXVECTOR3 direction;

	public:
		Ray(D3DXVECTOR3 origin, D3DXVECTOR3 direction);
		~Ray(void);

	public:
		D3DXVECTOR3 GetPoint(float distance);
	};
}