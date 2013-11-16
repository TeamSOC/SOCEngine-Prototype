#pragma once

#include "RenderingMath.h"

namespace Rendering
{
	namespace Light
	{
		struct LightParameters
		{
			SOC_Vector3 ambient;
			SOC_Vector3 diffuse;
			SOC_Vector3 specular;

			float range;

			SOC_Vector4 lightPos;
			SOC_Vector3 lightDir;

			float spotAngle;
			int type;

		public:
			LightParameters();
			~LightParameters()
			{
			}

			void SetData(SOC_Vector3 &ambient, SOC_Vector3 &diffuse, SOC_Vector3 &specular, float range,
				SOC_Vector3 &lightPos, SOC_Vector3& lightdir, float spotAngle, int type)
			{
				this->ambient = ambient;
				this->diffuse = diffuse;
				this->specular = specular;
				this->range = range;
				this->lightPos = SOC_Vector4(lightPos, 1.0f);
				this->lightDir = lightdir;
				this->spotAngle = spotAngle;
				this->type = type;
			}
		};

	}
}