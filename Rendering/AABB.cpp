#include "AABB.h"
#include "Utility.h"

namespace Intersection
{
	AABB::AABB()
	{
		center = D3DXVECTOR3(0, 0, 0);
		size = D3DXVECTOR3(1, 1, 1);

		extents = size / 2.0f;

		min = -extents;
		max =  extents;
	}

	AABB::AABB(D3DXVECTOR3 worldCenter, D3DXVECTOR3 size)
	{
		center = worldCenter;
		this->size = size;
		extents = size / 2.0f;

		min = (worldCenter - size) + extents;
		max = worldCenter + extents;
	}

	AABB::~AABB(void)
	{
	}

	void AABB::SetMinMax(D3DXVECTOR3 min, D3DXVECTOR3 max)
	{
		center -= (min + extents);

		this->min = min;
		this->max = max;

		size    = max - min;
		extents = size / 2.0f;
		center += min + extents;
	}

	void AABB::Expand(float amount)
	{
		size.x += amount; size.y += amount; size.z += amount;
		extents = size / 2.0f;
		min = center - extents;
		max = center + extents;
	}

	void AABB::Expand(D3DXVECTOR3 amount)
	{
		size += amount;
		extents = size / 2.0f;
		min = center - extents;
		max = center + extents;
	}

	bool AABB::Intersects(AABB bounds)
	{
		D3DXVECTOR3 realMin = center + min;
		D3DXVECTOR3 realMax = center + max;
		D3DXVECTOR3 otherMin = bounds.center + min;
		D3DXVECTOR3 otherMax = bounds.center + max;

		if(realMax.x < otherMin.x || realMin.x > otherMax.x) return false;
		if(realMax.y < otherMin.y || realMin.y > otherMax.y) return false;
		if(realMax.z < otherMin.z || realMin.z > otherMax.z) return false;

		return true;
	}

	float AABB::SqrDistance(D3DXVECTOR3 point)
	{
		D3DXVECTOR3 v = point - extents - center;
		return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
	}

	bool AABB::Contains(D3DXVECTOR3 point)
	{
		D3DXVECTOR3 realMin = center + min;
		D3DXVECTOR3 realMax = center + max;

		if(point.x < realMin.x || point.x > realMax.x) return false;
		if(point.y < realMin.y || point.y > realMax.y) return false;
		if(point.z < realMin.z || point.z > realMax.z) return false;

		return true;
	}

	bool AABB::IntersectRay(Ray ray, D3DXVECTOR3 *outPickPoint /*= NULL*/, float gap)
	{
		D3DXVECTOR3 realMin = center + min;
		D3DXVECTOR3 realMax = center + max;

		float rayMin = 0.0f;
		float rayMax = 100000.0f;

		for(int i=0; i<3; ++i)
		{
			if(abs(ray.direction[i]) < gap)
			{
				if(ray.origin[i] < realMin[i] || ray.origin[i] > realMax[i])
					return false;
			}
			else
			{
				float denom = 1.0f / ray.direction[i];
				float t1 = ( -ray.origin[i] - realMin[i]) * denom;
				float t2 = ( -ray.origin[i] - realMax[i]) * denom;

				if( t1 > t2 )
					Utility::Max(t1, t2);

				rayMin = Utility::Max(rayMin, t1);
				rayMax = Utility::Max(rayMax, t2);

				if(rayMin > rayMax)
					return false;
			}
		}

		if(outPickPoint)
			*outPickPoint = ray.origin + rayMin * ray.direction;

		return true;
	}

	bool AABB::operator !=(AABB &box)
	{
		if( this->center != box.center ) return true;
		if( this->extents != box.extents ) return true;

		return false;
	}

	bool AABB::operator ==(AABB &box)
	{
		if( this->center != box.center ) return false;
		if( this->extents != box.extents ) return false;

		return true;
	}
}