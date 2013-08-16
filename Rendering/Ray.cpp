#include "Ray.h"


namespace Intersection
{

	Ray::Ray(D3DXVECTOR3 origin, D3DXVECTOR3 direction)
	{
		this->origin		= origin;
		this->direction		= direction;
	}

	Ray::~Ray(void)
	{
	}

	D3DXVECTOR3 Ray::GetPoint(float distance)
	{
		D3DXVECTOR3 dir;
		D3DXVec3Normalize(&dir, &direction);
		dir *= distance;

		return dir;
	}

}