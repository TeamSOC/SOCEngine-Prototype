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

		class Shader
		{
		private:
			LPD3DXEFFECT shader;
			std::string name;

			Device::Graphics	*graphics;

			bool	 compiled;
			SOC_uint numPass;

			SOC_byte requiredMatrixParam;
			SOC_byte requiredLightParam;

		public:
			Shader(Device::Graphics *graphics, const char *name = nullptr);
			~Shader(void);

		public:
			bool Compile(std::string &shaderCode);
			void GetRequiredParameters(SOC_byte *outMatrixParamters, SOC_byte *outLightParameters, char *technique = DEFAULT_TECHNIQUE);

			bool SetVariable(const char *parameter, SOC_Matrix *m);
			bool SetVariable(const char *parameter, SOC_Matrix *ary, SOC_uint count);
			bool SetVariable(const char *parameter, SOC_Vector3 *v);
			bool SetVariable(const char *parameter, SOC_Vector3 *ary, SOC_uint count);
			bool SetVariable(const char *parameter, SOC_Vector4 *v);
			bool SetVariable(const char *parameter, SOC_Vector4 *ary, SOC_uint count);
			bool SetVariable(const char *parameter, bool b);
			bool SetVariable(const char *parameter, float f);
			bool SetVariable(const char *parameter, float *ary, SOC_uint count);
			bool SetVariable(const char *parameter, int i);
			bool SetVariable(const char *parameter, int *ary, SOC_uint count);
			bool SetVariable(const char *parameter, Texture::Texture *texture);
			bool SetVariable(const char *parameter, void *data, SOC_uint size);

			bool SetStructArrayVariable(const char *variableName, SOC_uint index, const char *component, void* data, SOC_uint size);
			bool SetStructVariable(const char *variableName, const char *component, void* data, SOC_uint size);

			bool IsParameterUsed(const char *parameter, const char *technique = DEFAULT_TECHNIQUE);

			bool SetTechnique(const char *technique = DEFAULT_TECHNIQUE);

			bool Begin();
			bool BeginPass(SOC_uint pass);
			bool EndPass();
			bool End();			

		public:
			bool IsCompiled();
			SOC_uint GetNumPasses();
			const char* GetName();
			SOC_byte GetRequiredMatrixParameters();
			SOC_byte GetRequiredLightParameters();
		};
	}
}