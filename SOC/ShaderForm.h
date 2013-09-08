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
		private:
			std::string name;

		protected:
			Device::Graphics::GraphicsForm	*graphics;

			bool	 compiled;
			SOC_uint numPass;

		public:
			ShaderForm(Device::Graphics::GraphicsForm *graphics, const char *name = nullptr);
			~ShaderForm(void);

		public:
			virtual bool Compile(std::string &shaderCode) = 0;

			virtual bool SetVariable(char *parameter, SOC_Matrix *m) = 0;
			virtual bool SetVariable(char *parameter, SOC_Matrix *ary, SOC_uint count) = 0;
			virtual bool SetVariable(char *parameter, SOC_Vector4 *v) = 0;
			virtual bool SetVariable(char *parameter, SOC_Vector4 *ary, SOC_uint count) = 0;
			virtual bool SetVariable(char *parameter, bool b) = 0;
			virtual bool SetVariable(char *parameter, float f) = 0;
			virtual bool SetVariable(char *parameter, float *ary, SOC_uint count) = 0;
			virtual bool SetVariable(char *parameter, int i) = 0;
			virtual bool SetVariable(char *parameter, int *ary, SOC_uint count) = 0;
			virtual bool SetVariable(char *parameter, Texture::Texture *texture) = 0;

			virtual bool SetTechnique(char *technique) = 0;

			virtual bool Begin() = 0;
			virtual bool BeginPass(SOC_uint pass) = 0;
			virtual bool EndPass() = 0;
			virtual bool End() = 0;

		public:
			bool IsCompiled();
			SOC_uint GetNumPasses();
			const char* GetName();
		};
	}
}