#include "ShaderForm.h"

namespace Rendering
{
	namespace Shader
	{
		ShaderForm::ShaderForm(const char *name)
		{
			compiled = false;
			numPass = 0;

			this->name = name;
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
	}
}