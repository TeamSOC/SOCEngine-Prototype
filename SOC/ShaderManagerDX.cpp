#include "ShaderManagerDX.h"

using namespace std;

namespace Rendering
{
	namespace Shader
	{
		ShaderManagerDX::ShaderManagerDX(Device::Graphics::GraphicsForm *graphics) : ShaderManagerForm(graphics)
		{
			shaderDir = "../Shader/DX/";
			dirLen = strlen(shaderDir);
		}

		ShaderManagerDX::~ShaderManagerDX(void)
		{
			DeleteAll();
		}

		bool ShaderManagerDX::LoadShaderFromFile( std::string &path, std::pair<ShaderCode, Shader*> *outPair, bool shaderClone, bool inShaderFolder)
		{
			SOCHashMap<std::string, pair<ShaderCode, Shader*>>::iterator iter = hash.find(path);
			string name = path;

			if(iter != hash.end())
				return FindShader(name, outPair, shaderClone);

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
			std::string code;

			while(std::getline(file, buff))
			{
				code += buff;
				code += "\n";
			}

			if(inShaderFolder)
			{
				path.erase( path.length() - 3, 3);
				path.erase(0, dirLen);
			}

			pair<ShaderCode, Shader*> pairData;
			pairData.first = code;

			Shader *shader = new Shader(graphics, name.data());
			shader->Compile(code);

			pairData.second = shader;

			hash.insert( SOCHashMap<std::string, pair<ShaderCode, Shader*>>::value_type(path, pairData));

			if(outPair)
				*outPair = pairData;

			return true;
		}

		bool ShaderManagerDX::FindShader(std::string &name, std::pair<ShaderCode, Shader*> *outPair, bool shaderClone)
		{
			SOCHashMap<std::string, pair<ShaderCode, Shader*>>::iterator iter = hash.find(name);

			if(iter == hash.end())
				return false;

			outPair->first = iter->second.first;

			Shader *shader;

			if(shaderClone)
			{
				shader = new Shader(graphics, iter->second.first.data());
				shader->Compile(iter->second.first);
			}
			else shader = iter->second.second;

			outPair->second = shader;
			outPair->first.erase(0, 1);

			return true;
		}

		bool ShaderManagerDX::LoadShaderFromFile( std::string path, ShaderCode *outShaderCode, bool inShaderFolder)
		{
			pair<ShaderCode, Shader*> pairData;
			bool res = LoadShaderFromFile(path, &pairData, false, inShaderFolder);

			if(res)
				*outShaderCode = pairData.first;

			return res;
		}

		bool ShaderManagerDX::FindShader(std::string path, ShaderCode *outShaderCode)
		{
			pair<ShaderCode, Shader*> pairData;
			bool res = FindShader(path, &pairData, false);

			if(res)
				*outShaderCode = pairData.first;

			return res;
		}

		bool ShaderManagerDX::LoadShaderFromFile( std::string path, Shader **outShader, bool shaderClone, bool inShaderFolder)
		{
			pair<ShaderCode, Shader*> pairData;
			bool res = LoadShaderFromFile(path, &pairData, shaderClone, inShaderFolder);

			if(res)
				*outShader = pairData.second;

			return res;
		}

		bool ShaderManagerDX::FindShader(std::string path, Shader **outShader, bool shaderClone)
		{
			pair<ShaderCode, Shader*> pairData;
			bool res = FindShader(path, &pairData, shaderClone);

			if(res)
				*outShader = pairData.second;

			return res;
		}


		void ShaderManagerDX::DeleteAll()
		{
			hash.clear();
		}
	}
}