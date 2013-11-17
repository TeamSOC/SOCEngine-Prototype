#include "Shader.h"

using namespace std;
using namespace Device;

namespace Rendering
{
	namespace Shader
	{
		Shader::Shader(Device::Graphics *graphics, const char *name)
		{
			compiled = false;
			numPass = 0;

			if(name != nullptr)
				this->name = name;

			this->graphics = graphics;

			requiredLightParam = 0;
			requiredMatrixParam = 0;

			shader = NULL;
		}

		Shader::~Shader(void)
		{
			if(shader)
				shader->Release();

		}

		bool Shader::Compile(string &shaderCode)
		{
			LPD3DXBUFFER error = nullptr;
			SOC_dword flags = 0;
			LPDIRECT3DDEVICE9 device = dynamic_cast<Device::Graphics*>(graphics)->GetD3DDevice();
			bool success = true;

#if _DEBUG
			flags |= D3DXSHADER_DEBUG;
#endif

			success = SUCCEEDED( D3DXCreateEffect(device, shaderCode.data(), shaderCode.length(), NULL, NULL, flags, NULL, &shader, &error) );

#if _DEBUG
			if(error)
			{
				int size = error->GetBufferSize();
				void *ack = error->GetBufferPointer();

				if(ack)
				{
					char *str = new char[size];
					memcpy(str, (const char*)ack, size);
					//					sprintf(str, (const char*)ack, size);
					OutputDebugString(str);
					delete[] str;					
				}
			}
#endif
			compiled = success;
			if(success)
				GetRequiredParameters(&requiredMatrixParam, &requiredLightParam);

			return success; 
		}

		bool Shader::SetVariable(const char *parameter, SOC_Matrix *m)
		{
			return SUCCEEDED(shader->SetMatrix(parameter, m));
		}

		bool Shader::SetVariable(const char *parameter, SOC_Matrix *ary, SOC_uint count)
		{
			return SUCCEEDED(shader->SetMatrixArray(parameter, ary, count));
		}

		bool Shader::SetVariable(const char *parameter, SOC_Vector3 *v)
		{
			return SUCCEEDED(shader->SetValue(parameter, v, sizeof(SOC_Vector3)));
		}

		bool Shader::SetVariable(const char *parameter, SOC_Vector3 *ary, SOC_uint count)
		{
			return SUCCEEDED(shader->SetValue(parameter, ary, sizeof(SOC_Vector3) * count));
		}

		bool Shader::SetVariable(const char *parameter, SOC_Vector4 *v)
		{
			return SUCCEEDED(shader->SetVector(parameter, v));
		}

		bool Shader::SetVariable(const char *parameter, SOC_Vector4 *ary, SOC_uint count)
		{
			return SUCCEEDED(shader->SetVectorArray(parameter, ary, count));
		}

		bool Shader::SetVariable(const char *parameter, bool b)
		{
			return SUCCEEDED(shader->SetBool(parameter, b));
		}

		bool Shader::SetVariable(const char *parameter, float f)
		{
			return SUCCEEDED(shader->SetFloat(parameter, f));
		}

		bool Shader::SetVariable(const char *parameter, float *ary, SOC_uint count)
		{
			return SUCCEEDED(shader->SetFloatArray(parameter, ary, count));
		}

		bool Shader::SetVariable(const char *parameter, int i)
		{
			return SUCCEEDED(shader->SetInt(parameter, i));
		}

		bool Shader::SetVariable(const char *parameter, int *ary, SOC_uint count)
		{
			return SUCCEEDED(shader->SetIntArray(parameter, ary, count));
		}

		bool Shader::SetTechnique(const char *technique)
		{
			return SUCCEEDED(shader->SetTechnique(technique));
		}

		bool Shader::SetVariable(const char *parameter, Texture::Texture *texture)
		{
			LPDIRECT3DTEXTURE9 tex = texture->GetTexture();
			return SUCCEEDED( shader->SetTexture(parameter, tex) );
		}

		bool Shader::SetVariable(const char *parameter, void *data, SOC_uint size)
		{
			return SUCCEEDED(shader->SetValue(parameter, data, size));
		}

		bool Shader::SetStructArrayVariable(const char *structName, SOC_uint index, const char *component, void* data, SOC_uint size)
		{
			D3DXHANDLE structHandle = shader->GetParameterElement(structName, index);
			D3DXHANDLE componentHandle = shader->GetParameterByName(structHandle, component);

			return SUCCEEDED(shader->SetValue(componentHandle, data, size));;
		}

		bool Shader::SetStructVariable(const char *variableName, const char *component, void* data, SOC_uint size)
		{
			std::string parameter = variableName;
			parameter += ".";
			parameter += component;
		
			return SetVariable(parameter.c_str(), data, size);
		}

		bool Shader::Begin()
		{
			return SUCCEEDED( shader->Begin(&this->numPass, NULL) );
		}

		bool Shader::BeginPass(SOC_uint pass)
		{
			return SUCCEEDED( shader->BeginPass(pass) );
		}

		bool Shader::EndPass()
		{
			return SUCCEEDED( shader->EndPass() );
		}

		bool Shader::End()
		{
			return SUCCEEDED( shader->End() );
		}

		bool Shader::IsParameterUsed(const char *parameter, const char *technique)
		{			 
			return (bool)shader->IsParameterUsed(parameter, technique);
		}

		void Shader::GetRequiredParameters(SOC_byte *outMatrixParamters, SOC_byte *outLightParameters, char *technique)
		{
			if(IsParameterUsed(BasicParameterNames::GetWorldMatrix(), technique))
				requiredMatrixParam |= REQUIRED_TRANSFORM::WORLD;

			if(IsParameterUsed(BasicParameterNames::GetViewMatrix(), technique))
				requiredMatrixParam |= REQUIRED_TRANSFORM::VIEW;

			if(IsParameterUsed(BasicParameterNames::GetProjMatrix(), technique))
				requiredMatrixParam |= REQUIRED_TRANSFORM::PROJECTION;

			if(IsParameterUsed(BasicParameterNames::GetViewProjMatrix(), technique))
				requiredMatrixParam |= REQUIRED_TRANSFORM::VIEW_PROJECTION;

			if(IsParameterUsed(BasicParameterNames::GetWorldViewProjMatrix(), technique))
				requiredMatrixParam |= REQUIRED_TRANSFORM::WORLD_VIEW_PROJECTION;

			if(IsParameterUsed(BasicParameterNames::GetWorldViewInvTnsMatrix(), technique))
				requiredMatrixParam |= REQUIRED_TRANSFORM::WORLD_VIEW_INV_TRANS;

			const char *structName = nullptr;
			bool test;// = shader->SetValue("material.ambient", nullptr, sizeof(float));
			std::string &checkParam = BasicParameterNames::GetMaterialElement(BasicParameterNames::GetAmbient());

			SOC_Vector4 temp(0, 0, 0, 0);
			if(SetVariable(checkParam.c_str(), &temp))
			{
				requiredLightParam |= REQUIRED_LIGHTING::MATERIAL;

				float tempfloat = 0.0f;
				if(SetVariable(BasicParameterNames::GetMaterialElement(BasicParameterNames::GetMaterialShininess()).c_str(), tempfloat))
					requiredLightParam |= REQUIRED_LIGHTING::MATERIAL_SHININESS;
			}
			
			structName = shader->GetParameterElement(BasicParameterNames::GetLight(), 0);
			if(structName != nullptr)
			{
				requiredLightParam |= REQUIRED_LIGHTING::LIGHT;
				
				if(shader->GetParameterByName(structName, BasicParameterNames::GetLightRange()) != nullptr)
					requiredLightParam |= REQUIRED_LIGHTING::LIGHT_RANGE;

				if(shader->GetParameterByName(structName, BasicParameterNames::GetLightSpotAngle()) != nullptr)
					requiredLightParam |= REQUIRED_LIGHTING::LIGHT_SPOTANGLE;
			}

			if(outMatrixParamters)
				*outMatrixParamters = requiredMatrixParam;

			if(outLightParameters)
				*outLightParameters = requiredLightParam;
		}

		bool Shader::IsCompiled()
		{
			return compiled;
		}

		SOC_uint Shader::GetNumPasses()
		{
			return numPass;
		}

		const char* Shader::GetName()
		{
			return name.c_str();
		}

		SOC_byte Shader::GetRequiredMatrixParameters()
		{
			return requiredMatrixParam;
		}

		SOC_byte Shader::GetRequiredLightParameters()
		{
			return requiredLightParam;
		}
	}
}