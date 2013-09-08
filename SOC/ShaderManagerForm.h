#pragma once

#include "SOCHashMap.h"
#include <string>
#include <fstream>
#include "ShaderCode.h"

namespace Rendering
{
	namespace Shader
	{
		class ShaderManagerForm
		{
		protected:
			const char *shaderDir;
			int dirLen;

		public:
			virtual bool LoadShaderFromFile( std::string path, ShaderCode *outShaderCode, bool inShaderFolder) = 0;
			virtual bool FindShader(std::string path, std::string *outShaderCode, bool inResourceFolder) = 0;

			virtual void DeleteAll() = 0;
		};
	}
}