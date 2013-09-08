#pragma once

#include <string>

namespace Rendering
{
	namespace Shader
	{
		//only Use GL
		struct ShaderCodeGL
		{
		public:
			std::string vertexCode;
			std::string fragmentCode;

		public:
			ShaderCodeGL(void);
			~ShaderCodeGL(void);

		public:
			void insert(unsigned int pos, const char *str);
			void erase(unsigned int start, unsigned int end);

		public:
			ShaderCodeGL operator +(std::string str);
			ShaderCodeGL operator +=(std::string str);
		};

	}
}