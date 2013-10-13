#include "ShaderManagerDX.h"

namespace Rendering
{
	namespace Shader
	{
		ShaderManagerDX::ShaderManagerDX(void)
		{
			shaderDir = "../Shader/DX/";
			dirLen = strlen(shaderDir);
		}

		ShaderManagerDX::~ShaderManagerDX(void)
		{
			DeleteAll();
		}

		bool ShaderManagerDX::LoadShaderFromFile( std::string path, shaderCode *outShaderCode, bool inShaderFolder)
		{
			SOCHashMap<std::string, shaderCode>::iterator iter = hash.find(path);

			if(iter != hash.end())
				return false;

			if(inShaderFolder)
			{
				path.insert(0, shaderDir);
			}

			path += ".fx"; //hlsl shader
			std::ifstream file( path.c_str() );

			if( file.good() == false )
			{
				file.close();
				return false;
			}

			std::string buff;
			std::string data;

			while(std::getline(file, buff))
			{
				data += buff;
				data += "\n";
			}

			if(inShaderFolder)
			{
				path.erase( path.length() - 3, 3);
				path.erase(0, dirLen);
			}

			hash.insert( SOCHashMap<std::string, shaderCode>::value_type(path, data));

			if(outShaderCode)
				*outShaderCode = data;

			return true;
		}

		bool ShaderManagerDX::FindShader(std::string path, std::string *outShaderCode, bool inResourceFolder)
		{
			if(inResourceFolder)
				path.erase(0, dirLen);

			SOCHashMap<std::string, shaderCode>::iterator iter = hash.find(path);

			if(iter == hash.end())
				return false;

			*outShaderCode = iter->second;
			outShaderCode->erase(0, 1);

			return true;
		}

		void ShaderManagerDX::DeleteAll()
		{
			hash.clear();
		}
	}
}