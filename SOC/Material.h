#pragma once

#include "Shader.h"
#include <vector>

namespace Rendering
{
	class Material
	{
	private:
		std::string name;
		std::vector<Shader::Shader*> shaders;

		Shader::Shader* useShader;

	public:
		Material(const char *name = nullptr) : useShader(nullptr)
		{
			this->name = name;			
		}

		~Material(void)
		{
			DeleteAllShader();
		}

	public:
		void Begin()
		{
			useShader->Begin();
		}
		void BeginPass(int pass = 0)
		{
			useShader->BeginPass(pass);
		}
		void End()
		{
			useShader->End();
		}
		void EndPass()
		{
			useShader->EndPass();
		}

	public:
		bool SelectUseShader(SOC_uint idx)
		{
			if(idx > shaders.size())
				return false;

			useShader = shaders[idx];
			return true;
		}

		bool SelectUseShader( std::string name )
		{
			std::vector< Shader::Shader* >::iterator iter;
			for(iter = shaders.begin(); iter != shaders.end(); ++iter)
			{
				if((*iter)->GetName() == name)
				{
					useShader = (*iter);
					return true;
				}
			}

			return false;
		}

		void AddShader( Shader::Shader *shader )
		{
			if(useShader == nullptr)
				useShader = shader;

			shaders.push_back( shader );
		}
		void DeleteShader( Shader::Shader *shader )
		{
			std::vector<Shader::Shader *>::iterator iter;
			for(iter = shaders.begin(); iter != shaders.end(); ++iter)
			{
				if( (*iter) == shader )
				{
					shaders.erase(iter);
					return;
				}
			}
		}
		void DeleteAllShader( )
		{
			shaders.clear();
		}

	public:
		template<typename Type>
		void SetVariable(int idx, char *parameter, Type value)
		{
			(*(shaders.begin() + idx))->SetVariable(parameter, value);
		}
		template<typename Type>
		void SetVariable(int idx, char *parameter, Type value, SOC_uint count)
		{
			(*(shaders.begin() + idx))->SetVariable(parameter, value, count);
		}

		template<typename Type>
		void SetVariable(char *parameter, Type value)
		{
			useShader->SetVariable(parameter, value);
		}
		template<typename Type>
		void SetVariable(char *parameter, Type value, SOC_uint count)
		{
			useShader->SetVariable(parameter, value, count);
		}

	public:
		int GetShaderCount()
		{
			return shaders.size();
		}

		SOC_uint GetUseShaderPass()
		{
			return useShader->GetNumPasses();
		}

		const char* GetName()
		{
			return name.c_str();
		}
	};

}