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

		public:
			ShaderDX(Device::Graphics::GraphicsForm *graphics, const char *name = nullptr);
			~ShaderDX(void);

		public:
			bool Compile(std::string &shaderCode);
			void GetRequiredParameters(SOC_byte *outMatrixParamters, SOC_byte *outLightParameters, char *technique = DEFAULT_TECHNIQUE);

			bool SetVariable(const char *parameter, SOC_Matrix *m);
			bool SetVariable(const char *parameter, SOC_Matrix *ary, SOC_uint count);
			bool SetVariable(const char *parameter, SOC_Vector4 *v);
			bool SetVariable(const char *parameter, SOC_Vector4 *ary, SOC_uint count);
			bool SetVariable(const char *parameter, bool b);
			bool SetVariable(const char *parameter, float f);
			bool SetVariable(const char *parameter, float *ary, SOC_uint count);
			bool SetVariable(const char *parameter, int i);
			bool SetVariable(const char *parameter, int *ary, SOC_uint count);
			bool SetVariable(const char *parameter, Texture::Texture *texture);

			bool IsParameterUsed(const char *paramter, const char *technique = DEFAULT_TECHNIQUE);

			bool SetTechnique(const char *technique = DEFAULT_TECHNIQUE);

			bool Begin();
			bool BeginPass(SOC_uint pass);
			bool EndPass();
			bool End();

		};
	}
}