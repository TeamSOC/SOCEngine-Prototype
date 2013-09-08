#include "Material.h"

namespace Rendering
{
	Material::Material(const char *name) : useShader(nullptr)
	{
		this->name = name;			
	}

	Material::~Material(void)
	{
		DeleteAllShader();
	}

	void Material::Begin()
	{
		useShader->Begin();
	}

	void Material::BeginPass(int pass)
	{
		useShader->BeginPass(pass);
	}

	void Material::End()
	{
		useShader->End();
	}

	void Material::EndPass()
	{
		useShader->EndPass();
	}

	bool Material::SelectUseShader(SOC_uint idx)
	{
		if(idx > shaders.size())
			return false;

		useShader = shaders[idx];
		return true;
	}

	bool Material::SelectUseShader( std::string name )
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

	void Material::AddShader( Shader::Shader *shader )
	{
		if(useShader == nullptr)
			useShader = shader;

		shaders.push_back( shader );
	}

	void Material::DeleteShader( Shader::Shader *shader )
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

	void Material::DeleteAllShader( )
	{
		shaders.clear();
	}

	int Material::GetShaderCount()
	{
		return shaders.size();
	}

	SOC_uint Material::GetUseShaderPass()
	{
		return useShader->GetNumPasses();
	}

	const char* Material::GetName()
	{
		return name.c_str();
	}
}