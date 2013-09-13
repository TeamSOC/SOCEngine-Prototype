#pragma once

#include "Platform.h"

namespace Rendering
{
	class Frustum
	{
	private:
		SOC_Vector3			planeVertex[8];
		SOC_Vector3			position;
		SOC_Plane			plane[6];
		float				gap;
		bool				isMake;

	public:
		Frustum(float gap = 0.0);
		~Frustum(void);

	public:
		void Make(SOC_Matrix *viewProjection);
		bool In(SOC_Vector3 &v, float radius = 0.0f);

	public:
		SOC_Vector3 GetPosition();
	};

}