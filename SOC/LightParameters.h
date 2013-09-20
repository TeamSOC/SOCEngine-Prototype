#pragma once

#include "RenderingMath.h"

namespace Rendering
{
	namespace Light
	{
		struct LightParameters
		{
			SOC_Vector4 *diffuseColorAry;
			SOC_Vector4 *specularColorAry;

			float *rangeAry;
			float *specularPowerAry;

			SOC_Vector4 *lightposAry;
			SOC_Vector4 *lightDirAry;
			SOC_Vector4  viewPos;

			float *spotAngleAry;
			int *typeAry;

			int count;

		public:
			LightParameters();
			LightParameters(int *typeAry,
				SOC_Vector4 *diffuseColorAry, float *rangeAry, SOC_Vector4 *lightposAry, SOC_Vector4 *lightDirAry,
				SOC_Vector4 &viewPos, SOC_Vector4 *specularColorAry, float *specularPowerAry,
				float *spotAngleAry);
		};

	}
}