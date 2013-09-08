#pragma once

#include "ShaderManagerForm.h"

namespace Rendering
{
	namespace Shader
	{
		class ShaderManagerDX : public ShaderManagerForm
		{
		public:
			typedef std::string shaderCode;

		private:
			SOCHashMap<std::string, shaderCode> hash;
			int dirLen;

		public:
			ShaderManagerDX(void);
			~ShaderManagerDX(void);

		public:
			bool LoadShaderFromFile( std::string path, shaderCode *outShaderCode, bool inShaderFolder);
			bool FindShader(std::string path, std::string *outShaderCode, bool inResourceFolder);
			void DeleteAll();
		};

	}
}