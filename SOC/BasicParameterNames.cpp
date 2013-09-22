#include "BasicParameterNames.h"

namespace Rendering
{
	namespace Shader
	{
		const char* BasicParameterNames::GetWorldMatrix()
		{
			static const char *worldMat	= "worldMat";
			return worldMat;
		}

		const char* BasicParameterNames::GetViewMatrix()
		{
			static const char *viewMat	= "viewMat";
			return viewMat;
		}

		const char* BasicParameterNames::GetProjMatrix()
		{
			static const char *projMat = "projMat";
			return projMat;
		}

		const char* BasicParameterNames::GetViewProjMatrix()
		{
			static const char *viewProjMat = "viewProjMat";
			return viewProjMat;
		}

		const char* BasicParameterNames::GetWorldViewProjMatrix()
		{
			static const char *worldViewProjMat	= "worldViewProjMat";
			return worldViewProjMat;
		}

		const char* BasicParameterNames::GetAmbientColor()
		{
			static const char *ambientColor	= "ambientColor";
			return ambientColor;
		}

		const char* BasicParameterNames::GetLightDiffuseColor()
		{
			static const char *lightDiffuseColor = "lightDiffuesColor";
			return lightDiffuseColor;
		}

		const char* BasicParameterNames::GetLightSpecularColor()
		{
			static const char *lightSpecularColor = "lightSpecularColor";
			return lightSpecularColor;
		}

		const char* BasicParameterNames::GetLightSpecularPower()
		{
			static const char *lightSpecularPower = "lightSpecularPower";
			return lightSpecularPower;
		}

		const char* BasicParameterNames::GetViewPos()
		{
			static const char *viewPos = "viewPos";
			return viewPos;
		}

		const char* BasicParameterNames::GetLightPos()
		{
			static const char *lightPos = "lightPos";
			return lightPos;
		}

		const char* BasicParameterNames::GetLightDir()
		{
			static const char *lightDir = "lightDir";
			return lightDir;
		}

		const char* BasicParameterNames::GetLightRange()
		{
			static const char *lightRange = "lightRange";
			return lightRange;
		}

		const char* BasicParameterNames::GetLightType()
		{
			static const char *lightType = "lightType";
			return lightType;
		}

		const char* BasicParameterNames::GetLightSpotAngle()
		{
			static const char *lightSpotAngle = "lightSpotAngle";
			return lightSpotAngle;
		}
	}
}