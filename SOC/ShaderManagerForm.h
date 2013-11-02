#pragma once

#include "SOCHashMap.h"
#include <string>
#include <fstream>
#include "ShaderCode.h"
#include "GraphicsForm.h"
#include "Shader.h"

namespace Rendering
{
	namespace Shader
	{
		class ShaderManagerForm
		{
		protected:
			Device::Graphics::GraphicsForm *graphics;

		public:
			ShaderManagerForm(Device::Graphics::GraphicsForm *graphics)
			{
				this->graphics = graphics;
			}

			virtual ~ShaderManagerForm()
			{

			}
			
		protected:
			const char *shaderDir;
			int dirLen;

		private:
			virtual bool LoadShaderFromFile( std::string &path, std::pair<ShaderCode, Shader*> *outPair, bool shaderClone, bool inShaderFolder = true) = 0;
			virtual bool FindShader(std::string &path, std::pair<ShaderCode, Shader*> *outPair, bool shaderClone) = 0;

		public:
			virtual bool LoadShaderFromFile( std::string path, ShaderCode *outShaderCode, bool inShaderFolder = true) = 0;
			virtual bool FindShader(std::string path, ShaderCode *outShaderCode) = 0;

			virtual bool LoadShaderFromFile( std::string path, Shader **outShader, bool shaderClone, bool inShaderFolder = true) = 0;
			virtual bool FindShader(std::string path, Shader **outShader, bool shaderClone) = 0;

			virtual void DeleteAll() = 0;
		};
	}
}