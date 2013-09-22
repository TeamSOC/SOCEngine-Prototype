#pragma once

namespace Rendering
{
	namespace Shader
	{
		enum REQUIRED_MATRIX
		{
			REQUIRED_MATRIX_WORLD			= 1,
			REQUIRED_MATRIX_VIEW			= 2,
			REQUIRED_MATRIX_PROJECTION		= 4,
			REQUIRED_MATRIX_VP				= 8,	//View * Projection
			REQUIRED_MATRIX_WVP				= 16	//World * View * Projection
		};

		//Specular light or other light should autonomously set. 
		enum REQUIRED_LIGHT
		{
			REQUIRED_LIGHT_DIFFUSE = 1,
			REQUIRED_LIGHT_AMBIENT_COLOR = 2,
			REQUIRED_LIGHT_SPECULAR = 4,
			REQUIRED_LIGHT_HAS_LIGHT = REQUIRED_LIGHT_DIFFUSE | REQUIRED_LIGHT_SPECULAR
		};

		class BasicParameterNames
		{
		public:
			static const char *GetWorldMatrix();
			static const char *GetViewMatrix();
			static const char *GetProjMatrix();
			static const char *GetViewProjMatrix();
			static const char *GetWorldViewProjMatrix();

			static const char *GetAmbientColor();
			static const char *GetLightDiffuseColor();

			static const char *GetLightSpecularColor();
			static const char *GetLightSpecularPower();

			static const char *GetViewPos();
			static const char *GetLightPos();
			static const char *GetLightDir();
			static const char *GetLightRange();
			static const char *GetLightType();
			static const char *GetLightSpotAngle();
		};
	}
}