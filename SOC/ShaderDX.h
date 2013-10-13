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
			virtual bool Compile(std::string &shaderCode);
			virtual void GetRequiredParameters(SOC_byte *outMatrixParamters, SOC_byte *outLightParameters, char *technique = DEFAULT_TECHNIQUE);

			virtual bool SetVariable(const char *parameter, SOC_Matrix *m);
			virtual bool SetVariable(const char *parameter, SOC_Matrix *ary, SOC_uint count);
			virtual bool SetVariable(const char *parameter, SOC_Vector4 *v);
			virtual bool SetVariable(const char *parameter, SOC_Vector4 *ary, SOC_uint count);
			virtual bool SetVariable(const char *parameter, bool b);
			virtual bool SetVariable(const char *parameter, float f);
			virtual bool SetVariable(const char *parameter, float *ary, SOC_uint count);
			virtual bool SetVariable(const char *parameter, int i);
			virtual bool SetVariable(const char *parameter, int *ary, SOC_uint count);
			virtual bool SetVariable(const char *parameter, Texture::Texture *texture);

			virtual bool IsParameterUsed(const char *parameter, const char *technique = DEFAULT_TECHNIQUE);

			virtual bool SetTechnique(const char *technique = DEFAULT_TECHNIQUE);

			virtual bool Begin();
			virtual bool BeginPass(SOC_uint pass);
			virtual bool EndPass();
			virtual bool End();

		};
	}
}