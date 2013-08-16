#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "Ray.h"

namespace Intersection
{
	class AABB
	{
	private:
		D3DXVECTOR3 center;
		D3DXVECTOR3 size;
		D3DXVECTOR3 extents;
		D3DXVECTOR3 min;
		D3DXVECTOR3 max;

	public:
		AABB();
		AABB(D3DXVECTOR3 worldCenter, D3DXVECTOR3 size);
		~AABB(void);

	public:
		void SetMinMax(D3DXVECTOR3 min, D3DXVECTOR3 max);

		void Expand(float amount);
		void Expand(D3DXVECTOR3 amount);

		bool Intersects(AABB bounds);
		bool Contains(D3DXVECTOR3 point);
		
		float SqrDistance(D3DXVECTOR3 point);

		bool IntersectRay(Ray ray, D3DXVECTOR3 *outPickPoint = NULL, float gap = 0.0);

	public:
		bool operator!=(AABB &box);
		bool operator==(AABB &box);
	};

}