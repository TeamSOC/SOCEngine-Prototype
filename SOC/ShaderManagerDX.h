#pragma once

#include "ShaderManagerForm.h"

namespace Rendering
{
	namespace Shader
	{
		class ShaderManagerDX : public ShaderManagerForm
		{
		private:
			SOCHashMap<std::string, std::pair<ShaderCode, Shader*>> hash;
			int dirLen;

		public:
			ShaderManagerDX(Device::Graphics::GraphicsForm *graphics);
			~ShaderManagerDX(void);

		private:
			virtual bool LoadShaderFromFile( std::string &path, std::pair<ShaderCode, Shader*> *outPair, bool shaderClone, bool inShaderFolder = true);
			virtual bool FindShader(std::string &path, std::pair<ShaderCode, Shader*> *outPair, bool shaderClone);

		public:
			virtual bool LoadShaderFromFile( std::string path, ShaderCode *outShaderCode, bool inShaderFolder = true);
			virtual bool FindShader(std::string path, ShaderCode *outShaderCode);

			virtual bool LoadShaderFromFile( std::string path, Shader **outShader, bool shaderClone, bool inShaderFolder = true);
			virtual bool FindShader(std::string path, Shader **outShader, bool shaderClone);

			virtual void DeleteAll();
		};

	}
}