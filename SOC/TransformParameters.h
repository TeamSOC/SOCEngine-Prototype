#pragma once

#include "RenderingMath.h"

namespace Rendering
{
	struct TransformParameters
	{
		SOC_Matrix *worldMatrix;
		SOC_Matrix *viewMatrix;
		SOC_Matrix *projMatrix;

		SOC_Matrix *viewProjMatrix;
		SOC_Matrix *worldViewProjMatrix;

	public:
		TransformParameters();
		TransformParameters(SOC_Matrix *worldMat, SOC_Matrix *viewMat, SOC_Matrix *projMat, SOC_Matrix *viewProjMat, SOC_Matrix *worldViewProjMat);

		~TransformParameters()
		{

		}

		void SetMatrix(SOC_Matrix *worldMat, SOC_Matrix *viewMat, SOC_Matrix *projMat, SOC_Matrix *viewProjMat, SOC_Matrix *worldViewProjMat)
		{
			this->worldMatrix = worldMat;
			this->viewMatrix = viewMat;
			this->projMatrix = projMat;
			this->viewProjMatrix = viewProjMat;
			this->worldViewProjMatrix = worldViewProjMat;
		}
	};
}