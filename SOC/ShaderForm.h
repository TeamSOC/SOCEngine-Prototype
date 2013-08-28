#pragma once

#include "Rendering.h"
#include "DeviceDirector.h"
#include "Texture.h"
#include <string>

namespace Rendering
{
	namespace Shader
	{

		class ShaderForm
		{
		protected:
			bool compiled;

		public:
			ShaderForm(void)
			{
				compiled = false;
			}

			~ShaderForm(void)
			{

			}

		public:
			virtual bool Load(std::string shaderCode) = 0;

			virtual bool SetMatrix(char *parameter, SOC_Matrix *m) = 0;
			virtual bool SetMatrixAry(char *parameter, SOC_Matrix *ary, SOC_uint count) = 0;
			virtual bool SetVector(char *parameter, SOC_Vector4 *v) = 0;
			virtual bool SetVectorAry(char *parameter, SOC_Vector4 *ary, SOC_uint count) = 0;
			virtual bool SetBool(char *parameter, bool b) = 0;
			virtual bool SetFloat(char *parameter, float f) = 0;
			virtual bool SetFloatAry(char *parameter, float *ary, SOC_uint count) = 0;
			virtual bool SetInt(char *parameter, int i) = 0;
			virtual bool SetIntAry(char *parameter, int *ary, SOC_uint count) = 0;
			virtual bool SetTechnique(char *technique) = 0;
			virtual bool SetTexture(char *parameter, Texture::Texture *texture) = 0;

			virtual bool Begin(SOC_uint *numPasses) = 0;
			virtual bool BeginPass(SOC_uint pass) = 0;
			virtual bool EndPass() = 0;
			virtual bool End() = 0;

		public:
			bool IsCompiled();
		};
	}
}