#include "Material.h"

namespace Rendering
{
	namespace Material
	{

		Material::Material(const char *name) : useShader(nullptr)
		{
			if(name != nullptr)
				this->name = name;			
			elements.ambientColor = Color(0.1f, 0.1f, 0.1f, 1.0f);
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

		bool Material::SelectUseShader(Shader::Shader *shader)
		{
			if(shader == nullptr)
				return false;

			if(HasShader(shader) == false)
				AddShader(shader);

			useShader = shader;
			return true;
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

		Shader::Shader* Material::FindShader( const char *name )
		{
			std::vector<Shader::Shader *>::iterator iter;
			for(iter = shaders.begin(); iter != shaders.end(); ++iter)
			{
				if( strcmp(name, (*iter)->GetName()) == 0 )
					return *iter;
			}

			return nullptr;
		}

		bool Material::HasShader(Shader::Shader *shader)
		{
			std::vector<Shader::Shader *>::iterator iter;
			for(iter = shaders.begin(); iter != shaders.end(); ++iter)
			{
				if( (*iter) == shader )
					return true;
			}

			return false;
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

		void Material::SetUseShaderRequiredParameters(TransformParameters *transform, Light::LightParameters *light)
		{
			using namespace Shader;

			SOC_byte mp = useShader->GetRequiredMatrixParameters();
			SOC_byte lp = useShader->GetRequiredLightParameters();

			bool test = false;

			if ( REQUIRED_MATRIX_WORLD & mp )
				test = useShader->SetVariable(BasicParameterNames::GetWorldMatrix(), transform->worldMatrix);
			if ( REQUIRED_MATRIX_VIEW & mp )
				test = useShader->SetVariable(BasicParameterNames::GetViewMatrix(), transform->viewMatrix);
			if ( REQUIRED_MATRIX_PROJECTION & mp )
				test = useShader->SetVariable(BasicParameterNames::GetProjMatrix(), transform->projMatrix);
			if ( REQUIRED_MATRIX_VP & mp )
				test = useShader->SetVariable(BasicParameterNames::GetViewProjMatrix(), transform->viewProjMatrix);
			if ( REQUIRED_MATRIX_WVP & mp )
				test = useShader->SetVariable(BasicParameterNames::GetWorldViewProjMatrix(), transform->worldViewProjMatrix);

			if( REQUIRED_LIGHT_AMBIENT_COLOR & lp )
			{
				SOC_Vector4 vector = elements.ambientColor.GetVector();
				useShader->SetVariable(BasicParameterNames::GetAmbientColor(), &vector);
			}

			int count = light->count;

			if(REQUIRED_LIGHT_HAS_LIGHT & lp)
			{
				useShader->SetVariable(BasicParameterNames::GetViewPos(), &light->viewPos);
				useShader->SetVariable(BasicParameterNames::GetLightPos(), light->lightposAry, count);
				useShader->SetVariable(BasicParameterNames::GetLightRange(), light->rangeAry, count);
				useShader->SetVariable(BasicParameterNames::GetLightType(), light->typeAry, count);
				useShader->SetVariable(BasicParameterNames::GetLightDir(), light->lightDirAry, count);

				useShader->SetVariable(BasicParameterNames::GetLightSpotAngle(), light->spotAngleAry, count);
				//아 모르겠다 지가 알아서 걸르것지 --;
			}

			if( REQUIRED_LIGHT_DIFFUSE & lp )
				useShader->SetVariable(BasicParameterNames::GetLightDiffuseColor(), light->diffuseColorAry, count);

			if( REQUIRED_LIGHT_SPECULAR & lp )
			{
				useShader->SetVariable(BasicParameterNames::GetLightSpecularColor(), light->specularColorAry, count);
				useShader->SetVariable(BasicParameterNames::GetLightSpecularPower(), light->specularPowerAry, count);
			}
		}
	}

}