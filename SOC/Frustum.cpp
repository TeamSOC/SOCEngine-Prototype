#include "Frustum.h"

namespace Rendering
{
	Frustum::Frustum(float gap)
	{
		this->gap = gap;
		isMake = false;
	}

	Frustum::~Frustum(void)
	{
	}

	void Frustum::Make(SOC_Matrix *viewProjection)
	{
		SOC_Matrix matInv;

		planeVertex[0].x = -1.0f;	planeVertex[0].y = -1.0f;	planeVertex[0].z = 0.0f;
		planeVertex[1].x =  1.0f;	planeVertex[1].y = -1.0f;	planeVertex[1].z = 0.0f;
		planeVertex[2].x =  1.0f;	planeVertex[2].y = -1.0f;	planeVertex[2].z = 1.0f;
		planeVertex[3].x = -1.0f;	planeVertex[3].y = -1.0f;	planeVertex[3].z = 1.0f;
		planeVertex[4].x = -1.0f;	planeVertex[4].y =  1.0f;	planeVertex[4].z = 0.0f;
		planeVertex[5].x =  1.0f;	planeVertex[5].y =  1.0f;	planeVertex[5].z = 0.0f;
		planeVertex[6].x =  1.0f;	planeVertex[6].y =  1.0f;	planeVertex[6].z = 1.0f;
		planeVertex[7].x = -1.0f;	planeVertex[7].y =  1.0f;	planeVertex[7].z = 1.0f;

		//determinat는 필요없음
		SOCMatrixInverse(&matInv, NULL, viewProjection);
		SOCVec3TransformCoordArray(planeVertex, sizeof(SOC_Vector3), planeVertex, sizeof(SOC_Vector3), &matInv, 8);

		position = (planeVertex[0] + planeVertex[5]) / 2.0f;

		SOCPlaneFromPoints(&plane[0], planeVertex+4, planeVertex+7, planeVertex+6);	// 상 평면(top)
		SOCPlaneFromPoints(&plane[1], planeVertex  , planeVertex+1, planeVertex+2);	// 하 평면(bottom)
		SOCPlaneFromPoints(&plane[2], planeVertex  , planeVertex+4, planeVertex+5);	// 근 평면(near)
		SOCPlaneFromPoints(&plane[3], planeVertex+2, planeVertex+6, planeVertex+7);	// 원 평면(far)
		SOCPlaneFromPoints(&plane[4], planeVertex  , planeVertex+3, planeVertex+7);	// 좌 평면(left)
		SOCPlaneFromPoints(&plane[5], planeVertex+1, planeVertex+5, planeVertex+6);	// 우 평면(right)

		isMake = true;
	}

	bool Frustum::In(SOC_Vector3 &v, float radius)
	{
		if( isMake == false ) return false;

		float dist;

		for(int i=0; i<6; ++i)
		{
			dist = SOCPlaneDotCoord( &plane[i], &v );
			if(dist < (radius + gap) ) return false;
		}

		return true;
	}

	SOC_Vector3 Frustum::GetPosition()
	{
		return position;
	}

}