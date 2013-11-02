#pragma once

#include "Platform.h"
#include "DeviceDirector.h"
#include "Texture.h"

#include "TransformParameters.h"
#include "LightParameters.h"
#include "BasicParameterNames.h"

#include <string>

#define DEFAULT_TECHNIQUE "SOC"

namespace Rendering
{
	namespace Shader
	{
#define DEFAULT_TECHNIQUE "SOC"

		class ShaderForm
		{
		protected:
			std::string name;

		protected:
			Device::Graphics::GraphicsForm	*graphics;

			bool	 compiled;
			SOC_uint numPass;

			SOC_byte requiredMatrixParam;
			SOC_byte requiredLightParam;

		public:
			ShaderForm(Device::Graphics::GraphicsForm *graphics, const char *name = nullptr);
			virtual ~ShaderForm(void);

		public:
			virtual bool Compile(std::string &shaderCode) = 0;
			virtual void GetRequiredParameters(SOC_byte *outMatrixParamters, SOC_byte *outLightParameters, char *technique) = 0;

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
			virtual bool IsParameterUsed(const char *parameter, const char *technique) = 0;

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