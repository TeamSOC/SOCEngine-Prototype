#include "TransformParameters.h"

namespace Rendering
{
	TransformParameters::TransformParameters() : worldMatrix(nullptr), viewMatrix(nullptr), projMatrix(nullptr), viewProjMatrix(nullptr), worldViewProjMatrix(nullptr)
	{
	}

	TransformParameters::TransformParameters(SOC_Matrix *worldMat, SOC_Matrix *viewMat, SOC_Matrix *projMat, SOC_Matrix *viewProjMat, SOC_Matrix *worldViewProjMat)
	{
		worldMatrix = worldMat;
		viewMatrix = viewMat;
		projMatrix = projMat;
		viewProjMatrix = viewProjMat;
		worldViewProjMatrix = worldViewProjMat;
	}
}