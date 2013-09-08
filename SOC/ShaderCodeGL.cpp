#include "ShaderCodeGL.h"


namespace Rendering
{
	namespace Shader
	{
		ShaderCodeGL::ShaderCodeGL(void)
		{

		}

		ShaderCodeGL::~ShaderCodeGL(void)
		{

		}

		void ShaderCodeGL::insert(unsigned int pos, const char *str)
		{
			vertexCode.insert(pos, str);
			fragmentCode.insert(pos, str);
		}

		void ShaderCodeGL::erase(unsigned int start, unsigned int end)
		{
			vertexCode.erase(start, end);
			fragmentCode.erase(start, end);
		}

		ShaderCodeGL ShaderCodeGL::operator +(std::string str)
		{
			vertexCode += str;
			fragmentCode += str;

			return *this;
		}

		ShaderCodeGL ShaderCodeGL::operator +=(std::string str)
		{
			vertexCode += str;
			fragmentCode += str;

			return *this;
		}
	}
}