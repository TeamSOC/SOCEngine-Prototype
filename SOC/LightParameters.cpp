#include "LightParameters.h"

namespace Rendering
{
	namespace Light
	{
		LightParameters::LightParameters() : diffuseColorAry(nullptr), specularColorAry(nullptr), rangeAry(nullptr),
			specularPowerAry(nullptr), lightposAry(nullptr), spotAngleAry(nullptr), typeAry(nullptr),
			lightDirAry(nullptr)
		{
			count = 0;
			viewPos = SOC_Vector4(0, 0, 0, 0);
		}

		LightParameters::LightParameters(int *typeAry,
			SOC_Vector4 *diffuseColorAry, float *rangeAry, SOC_Vector4 *lightposAry, SOC_Vector4 *lightDirAry,
			SOC_Vector4 &viewPos, SOC_Vector4 *specularColorAry, float *specularPowerAry,
			float *spotAngleAry)
		{
			this->diffuseColorAry = diffuseColorAry;
			this->rangeAry = rangeAry;

			this->lightposAry = lightposAry;
			this->viewPos = viewPos;

			this->specularColorAry = specularColorAry;
			this->specularPowerAry = specularPowerAry;

			this->spotAngleAry = spotAngleAry;
			this->typeAry = typeAry;
			this->lightDirAry = lightDirAry;
		}

	}
}