#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "Object.h"

namespace Rendering
{
	class Frustum
	{
	private:
		D3DXVECTOR3			planeVertex[8];
		D3DXVECTOR3			position;
		D3DXPLANE			plane[6];
		float				gap;
		bool				isMake;

	public:
		Frustum(float gap = 0.0);
		~Frustum(void);

	public:
		void Make(D3DXMATRIX *viewProjection);
		bool In(D3DXVECTOR3 &v, float radius = 0.0);
		bool In(Object* obj);

	public:
		D3DXVECTOR3 GetPosition();
	};

}