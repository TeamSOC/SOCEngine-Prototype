#pragma once

#include "Platform.h"
#include "DeviceDirector.h"
#include "Texture.h"
#include <string>

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

		namespace BasicParameters
		{
			static const char *worldMat				= "worldMat";
			static const char *viewMat				= "viewMat";
			static const char *projMat				= "projMat";
			static const char *viewProjMat			= "viewProjMat";
			static const char *worldViewProjMat		= "worldViewProjMat";

			static const char *ambientColor			= "ambientColor";

			static const char *lightDiffuseColor	= "lightDiffuesColor";
			static const char *lightSpecularColor	= "lightSpecularColor";
			static const char *lightSpecularPower   = "lightSpecularPower";
	
			static const char *viewPos				= "viewPos";
			static const char *lightPos				= "lightPos";
			static const char *lightRange			= "lightRange";
			static const char *lightType			= "lightType";
			static const char *lightSpotAngle		= "lightSpotAngle";
		}

		struct TransformParameters
		{
			SOC_Matrix *worldMatrix;
			SOC_Matrix *viewMatrix;
			SOC_Matrix *projMatrix;

			SOC_Matrix *viewProjMatrix;
			SOC_Matrix *worldViewProjMatrix;

			TransformParameters() : worldMatrix(nullptr), viewMatrix(nullptr), projMatrix(nullptr), viewProjMatrix(nullptr), worldViewProjMatrix(nullptr)
			{}
			TransformParameters(SOC_Matrix *worldMat, SOC_Matrix *viewMat, SOC_Matrix *projMat, SOC_Matrix *viewProjMat, SOC_Matrix *worldViewProjMat)
			{
				worldMatrix = worldMat;
				viewMatrix = viewMat;
				projMatrix = projMat;
				viewProjMatrix = viewProjMat;
				worldViewProjMatrix = worldViewProjMat;
			}
		};

		struct LightParameters
		{
			SOC_Vector4 *diffuseColorAry;
			SOC_Vector4 *specularColorAry;

			float *rangeAry;
			float *specularPowerAry;

			SOC_Vector4 *lightposAry;
			SOC_Vector4  viewPos;

			float *spotAngleAry;
			int *typeAry;

			int count;

			LightParameters() : diffuseColorAry(nullptr), specularColorAry(nullptr), rangeAry(nullptr),
				specularPowerAry(nullptr), lightposAry(nullptr), spotAngleAry(nullptr), typeAry(nullptr)
			{
				count = 0;
				viewPos = SOC_Vector4(0, 0, 0, 0);
			}

			LightParameters(int *typeAry,
				SOC_Vector4 *diffuseColorAry, float *rangeAry, SOC_Vector4 *lightposAry,
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
			}
		};

		class ShaderForm
		{
		private:
			std::string name;

		protected:
			Device::Graphics::GraphicsForm	*graphics;

			bool	 compiled;
			SOC_uint numPass;

			SOC_byte requiredMatrixParam;
			SOC_byte requiredLightParam;

		public:
			ShaderForm(Device::Graphics::GraphicsForm *graphics, const char *name = nullptr);
			~ShaderForm(void);

		public:
			virtual bool Compile(std::string &shaderCode) = 0;

			virtual bool SetVariable(const char *parameter, SOC_Matrix *m) = 0;
			virtual bool SetVariable(const char *parameter, SOC_Matrix *ary, SOC_uint count) = 0;
			virtual bool SetVariable(const char *parameter, SOC_Vector4 *v) = 0;
			virtual bool SetVariable(const char *parameter, SOC_Vector4 *ary, SOC_uint count) = 0;
			virtual bool SetVariable(const char *parameter, bool b) = 0;
			virtual bool SetVariable(const char *parameter, float f) = 0;
			virtual bool SetVariable(const char *parameter, float *ary, SOC_uint count) = 0;
			virtual bool SetVariable(const char *parameter, int i) = 0;
			virtual bool SetVariable(const char *parameter, int *ary, SOC_uint count) = 0;
			virtual bool SetVariable(const char *parameter, Texture::Texture *texture) = 0;

			virtual bool SetTechnique(const char *technique) = 0;
			virtual bool IsParameterUsed(const char *paramter, const char *technique) = 0;

			virtual bool Begin() = 0;
			virtual bool BeginPass(SOC_uint pass) = 0;
			virtual bool EndPass() = 0;
			virtual bool End() = 0;

		public:
			bool IsCompiled();
			SOC_uint GetNumPasses();
			const char* GetName();
			SOC_byte GetRequiredMatrixParameters();
			SOC_byte GetRequiredLightParameters();
		};
	}
}