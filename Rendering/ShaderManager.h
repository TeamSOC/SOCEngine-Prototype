#pragma once

#include <hash_map>
#include <string>
#include <fstream>


namespace Rendering
{
	class ShaderManager
	{
#define SHADER_DIR "../Shader/"

	private:
		std::hash_map<std::string, std::wstring> hash;
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
		bool InitializeFromFile( std::string &path, bool inShaderFolder)
		{
			if(inShaderFolder)
				path.erase(0, dirLen);

			std::hash_map<std::string, std::wstring>::iterator iter = hash.find(path);

			if(iter != hash.end())
				return false;

			std::wifstream file( path.c_str() );

			if( file.good() == false )
			{
				file.close();
				return false;
			}

			std::wstring buff;
			std::wstring data;

			while(std::getline(file, buff))
				data += buff;

			hash.insert( std::hash_map<std::string, std::wstring>::value_type(path, data));

			return true;
		}

		bool FindShader(std::string path, std::wstring *outFile, bool inResourceFolder)
		{
			if(inResourceFolder)
				path.erase(0, dirLen);
			
			std::hash_map<std::string, std::wstring>::iterator iter = hash.find(path);

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