#include "Frustum.h"

namespace Rendering
{
	Frustum::Frustum(float gap /*= 0.0*/)
	{
		this->gap = gap;
		isMake = false;
	}

	Frustum::~Frustum(void)
	{
	}

	void Frustum::Make(D3DXMATRIX *viewProjection)
	{
		D3DXMATRIX matInv;

		planeVertex[0].x = -1.0f;	planeVertex[0].y = -1.0f;	planeVertex[0].z = 0.0f;
		planeVertex[1].x =  1.0f;	planeVertex[1].y = -1.0f;	planeVertex[1].z = 0.0f;
		planeVertex[2].x =  1.0f;	planeVertex[2].y = -1.0f;	planeVertex[2].z = 1.0f;
		planeVertex[3].x = -1.0f;	planeVertex[3].y = -1.0f;	planeVertex[3].z = 1.0f;
		planeVertex[4].x = -1.0f;	planeVertex[4].y =  1.0f;	planeVertex[4].z = 0.0f;
		planeVertex[5].x =  1.0f;	planeVertex[5].y =  1.0f;	planeVertex[5].z = 0.0f;
		planeVertex[6].x =  1.0f;	planeVertex[6].y =  1.0f;	planeVertex[6].z = 1.0f;
		planeVertex[7].x = -1.0f;	planeVertex[7].y =  1.0f;	planeVertex[7].z = 1.0f;

		//determinat는 필요없음
		D3DXMatrixInverse(&matInv, NULL, viewProjection);
		D3DXVec3TransformCoordArray(planeVertex, sizeof(D3DXVECTOR3), planeVertex, sizeof(D3DXVECTOR3), &matInv, 8);

		position = (planeVertex[0] + planeVertex[5]) / 2.0f;

		D3DXPlaneFromPoints(&plane[0], planeVertex+4, planeVertex+7, planeVertex+6);	// 상 평면(top)
		D3DXPlaneFromPoints(&plane[1], planeVertex  , planeVertex+1, planeVertex+2);	// 하 평면(bottom)
		D3DXPlaneFromPoints(&plane[2], planeVertex  , planeVertex+4, planeVertex+5);	// 근 평면(near)
		D3DXPlaneFromPoints(&plane[3], planeVertex+2, planeVertex+6, planeVertex+7);	// 원 평면(far)
		D3DXPlaneFromPoints(&plane[4], planeVertex  , planeVertex+3, planeVertex+7);	// 좌 평면(left)
		D3DXPlaneFromPoints(&plane[5], planeVertex+1, planeVertex+5, planeVertex+6);	// 우 평면(right)

		isMake = true;
	}

	bool Frustum::In(D3DXVECTOR3 &v, float radius /* = 0.0*/)
	{
		if( isMake == false ) return false;

		float dist;

		for(int i=0; i<6; ++i)
		{
			dist = D3DXPlaneDotCoord( &plane[i], &v );
			if(dist > (radius + gap) ) return false;
		}

		return true;
	}

	bool Frustum::In(Object* obj)
	{
		return In(obj->GetWorldPosition(), obj->GetRadius());
	}

	D3DXVECTOR3 Frustum::GetPosition()
	{
		return position;
	}

}