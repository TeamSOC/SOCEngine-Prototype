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
			ShaderDX(const char *name = nullptr);
			~ShaderDX(void);

		public:
			bool Compile(std::string shaderCode);

			bool SetVariable(char *parameter, SOC_Matrix *m);
			bool SetVariable(char *parameter, SOC_Matrix *ary, SOC_uint count);
			bool SetVariable(char *parameter, SOC_Vector4 *v);
			bool SetVariable(char *parameter, SOC_Vector4 *ary, SOC_uint count);
			bool SetVariable(char *parameter, bool b);
			bool SetVariable(char *parameter, float f);
			bool SetVariable(char *parameter, float *ary, SOC_uint count);
			bool SetVariable(char *parameter, int i);
			bool SetVariable(char *parameter, int *ary, SOC_uint count);
			bool SetVariable(char *parameter, Texture::Texture *texture);

			bool SetTechnique(char *technique);

			bool Begin();
			bool BeginPass(SOC_uint pass);
			bool EndPass();
			bool End();
		};
	}
}