#pragma once

#include "SOCHashMap.h"
#include <string>
#include <fstream>


namespace Rendering
{
	namespace Shader
	{
		class ShaderManagerDX
		{
#define SHADER_DIR "../Shader/DX/"

		public:
			typedef std::string shaderCode;

		private:
			SOCHashMap<std::string, shaderCode> hash;
			int dirLen;

		public:
			ShaderManagerDX(void)
			{
				dirLen = strlen(SHADER_DIR);
			}

			~ShaderManagerDX(void)
			{

			}

		public:
			bool LoadShaderFromFile( std::string path, shaderCode *outShaderCode, bool inShaderFolder)
			{
//				if(inShaderFolder)
//				{
//					path.insert(0, shaderDir);
//					path.erase(0, dirLen);
//				}

				SOCHashMap<std::string, shaderCode>::iterator iter = hash.find(path);

				if(iter != hash.end())
					return false;

				if(inShaderFolder)
				{
					path.insert(0, SHADER_DIR);
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

			bool FindShader(std::string path, std::string *outFile, bool inResourceFolder)
			{
				if(inResourceFolder)
					path.erase(0, dirLen);

				SOCHashMap<std::string, shaderCode>::iterator iter = hash.find(path);

				if(iter == hash.end())
					return false;

				*outFile = iter->second;

				return true;
			}

			void DeleteAll()
			{
				hash.clear();
			}
		};

	}
}