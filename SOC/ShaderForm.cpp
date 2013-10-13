#include "ShaderForm.h"

namespace Rendering
{
	namespace Shader
	{
		ShaderForm::ShaderForm(Device::Graphics::GraphicsForm *graphics, const char *name)
		{
			compiled = false;
			numPass = 0;

			if(name != nullptr)
				this->name = name;

			this->graphics = graphics;

			requiredLightParam = 0;
			requiredMatrixParam = 0;
		}

		ShaderForm::~ShaderForm(void)
		{

		}

		bool ShaderForm::IsCompiled()
		{
			return compiled;
		}

		SOC_uint ShaderForm::GetNumPasses()
		{
			return numPass;
		}

		const char* ShaderForm::GetName()
		{
			return name.c_str();
		}

		SOC_byte ShaderForm::GetRequiredMatrixParameters()
		{
			return requiredMatrixParam;
		}

		SOC_byte ShaderForm::GetRequiredLightParameters()
		{
			return requiredLightParam;
		}
	}
}