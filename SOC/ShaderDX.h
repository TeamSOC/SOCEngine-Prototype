#pragma once

#include "ShaderForm.h"

namespace Rendering
{
	namespace Shader
	{
		class ShaderDX : public ShaderForm
		{
		private:
			LPD3DXEFFECT shader;
			bool compiled;

		public:
			ShaderDX(void);
			~ShaderDX(void);

		public:
			bool Compile(std::string shaderCode);

			bool SetMatrix(char *parameter, SOC_Matrix *m);
			bool SetMatrixAry(char *parameter, SOC_Matrix *ary, SOC_uint count);
			bool SetVector(char *parameter, SOC_Vector4 *v);
			bool SetVectorAry(char *parameter, SOC_Vector4 *ary, SOC_uint count);
			bool SetBool(char *parameter, bool b);
			bool SetFloat(char *parameter, float f);
			bool SetFloatAry(char *parameter, float *ary, SOC_uint count);
			bool SetInt(char *parameter, int i);
			bool SetIntAry(char *parameter, int *ary, SOC_uint count);
			bool SetTechnique(char *technique);
			bool SetTexture(char *parameter, Texture::Texture *texture);

			bool Begin(SOC_uint *numPasses);
			bool BeginPass(SOC_uint pass);
			bool EndPass();
			bool End();
		};
	}
}