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

	public:
		Material(const char *name = nullptr)
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
			std::vector<Shader::Shader*>::iterator iter;
			for( iter = shaders.begin(); iter != shaders.end(); ++iter )
				(*iter)->Begin();
		}
		void BeginPass()
		{
			int count = 0;
			std::vector<Shader::Shader*>::iterator iter;

			for( iter = shaders.begin(); iter != shaders.end(); ++iter )
			{
				count = (*iter)->GetNumPasses();

				for(int i=0; i < count; ++i)
					(*iter)->BeginPass(i);
			}
		}
		void End()
		{
			std::vector<Shader::Shader*>::iterator iter;
			for( iter = shaders.begin(); iter != shaders.end(); ++iter )
				(*iter)->End();

		}
		void EndPass()
		{
			std::vector<Shader::Shader*>::iterator iter;
			for( iter = shaders.begin(); iter != shaders.end(); ++iter )
				(*iter)->EndPass();
		}

	public:
		void AddShader( Shader::Shader *shader )
		{
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

	public:
		int GetShaderCount()
		{
			return shaders.size();
		}
		//static Material* Copy(Material *material)
		//{
		//	Material *m = new Material();
		//	(*m) = (*material);

		//	return m;
		//}
		const char* GetName()
		{
			return name.c_str();
		}
	};

}