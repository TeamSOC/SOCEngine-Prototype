#include "Material.h"

namespace Rendering
{
	Material::Material(const char *name) : useShader(nullptr)
	{
		this->name = name;			
		ambientColor = Color(0.1f, 0.1f, 0.1f, 1.0f);
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

	bool Material::GetShaderRequiredParameters(unsigned int index, SOC_byte *outMatrixParameters, SOC_byte *outLightParameters)
	{
		if(index > shaders.size())
			return false;

		Shader::Shader *shader = (*(shaders.begin() + index));
		shader->GetRequiredParameters(outMatrixParameters, outLightParameters);

		return true;
	}

	bool Material::GetUseShaderRequiredParameters(SOC_byte *outMatrixParameters, SOC_byte *outLightParameters)
	{
		useShader->GetRequiredParameters(outMatrixParameters, outLightParameters);
		return true;
	}

	void Material::SetUseShaderRequiredParameters(Shader::TransformParameters *transform, Shader::LightParameters *light)
	{
		using namespace Shader;

		SOC_byte mp = useShader->GetRequiredMatrixParameters();
		SOC_byte lp = useShader->GetRequiredLightParameters();
		
		if ( REQUIRED_MATRIX_WORLD & mp )
			useShader->SetVariable(BasicParameters::worldMat, transform->worldMatrix);
		if ( REQUIRED_MATRIX_VIEW & mp )
			useShader->SetVariable(BasicParameters::viewMat, transform->viewMatrix);
		if ( REQUIRED_MATRIX_PROJECTION & mp )
			useShader->SetVariable(BasicParameters::projMat, transform->projMatrix);
		if ( REQUIRED_MATRIX_VP & mp )
			useShader->SetVariable(BasicParameters::viewProjMat, transform->viewProjMatrix);
		if ( REQUIRED_MATRIX_WVP & mp )
			useShader->SetVariable(BasicParameters::worldViewProjMat, transform->worldViewProjMatrix);

		if( REQUIRED_LIGHT_AMBIENT_COLOR & lp )
		{
			SOC_Vector4 vector = this->ambientColor.GetVector();
			useShader->SetVariable(BasicParameters::ambientColor, &vector);
		}

		int count = light->count;

		if(REQUIRED_LIGHT_HAS_LIGHT & lp)
		{
			useShader->SetVariable(BasicParameters::viewPos, light->viewPos);
			useShader->SetVariable(BasicParameters::lightPos, light->lightposAry, count);
			useShader->SetVariable(BasicParameters::lightRange, light->rangeAry, count);
			useShader->SetVariable(BasicParameters::lightType, light->typeAry, count);

			useShader->SetVariable(BasicParameters::lightSpotAngle, light->spotAngleAry, count);
			//아 모르겠다 지가 알아서 걸르것지 --;
		}

		if( REQUIRED_LIGHT_DIFFUSE & lp )
			useShader->SetVariable(BasicParameters::lightDiffuseColor, light->diffuseColorAry, count);

		if( REQUIRED_LIGHT_SPECULAR & lp )
		{
			useShader->SetVariable(BasicParameters::lightSpecularColor, light->specularColorAry, count);
			useShader->SetVariable(BasicParameters::lightSpecularPower, light->specularPowerAry, count);
		}
	}
}