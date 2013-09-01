#pragma once

#include "SOCHashMap.h"
#include <string>
#include <fstream>


namespace Rendering
{
	namespace Shader
	{

		class ShaderManager
		{
#define SHADER_DIR "../Shader/"

		public:
			typedef std::string shaderCode;

		private:
			SOCHashMap<std::string, shaderCode> hash;
			int dirLen;

		public:
			ShaderManager(void)
			{
				dirLen = strlen(SHADER_DIR);
			}

			~ShaderManager(void)
			{

			}

		public:
			bool LoadShaderFromFile( std::string path, shaderCode *outShaderCode, bool inShaderFolder)
			{
				if(inShaderFolder)
					path.erase(0, dirLen);

				SOCHashMap<std::string, shaderCode>::iterator iter = hash.find(path);

				if(iter != hash.end())
					return false;

				std::ifstream file( path.c_str() );

				if( file.good() == false )
				{
					file.close();
					return false;
				}

				std::string buff;
				std::string data;

				while(std::getline(file, buff))
					data += buff;

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