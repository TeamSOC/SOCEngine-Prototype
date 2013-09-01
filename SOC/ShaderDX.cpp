#include "ShaderDX.h"

using namespace std;
using namespace Device;

namespace Rendering
{
	namespace Shader
	{

		ShaderDX::ShaderDX(const char *name) : ShaderForm(name)
		{
			shader = NULL;
		}

		ShaderDX::~ShaderDX(void)
		{
			if(shader)
				shader->Release();
		}

		bool ShaderDX::Compile(string shaderCode)
		{
			LPD3DXBUFFER error = nullptr;
			SOC_dword flags = 0;
			LPDIRECT3DDEVICE9 device = dynamic_cast<Graphics::DX* >(DeviceDirector::GetInstance()->GetGraphics() )->GetD3DDevice();
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
					sprintf(str, (const char*)ack, size);
					OutputDebugString(str);
					delete[] str;					
				}
			}
#endif
			compiled = success;
			return success; 
		}

		bool ShaderDX::SetVariable(char *parameter, SOC_Matrix *m)
		{
			return SUCCEEDED(shader->SetMatrix(parameter, m));
		}

		bool ShaderDX::SetVariable(char *parameter, SOC_Matrix *ary, SOC_uint count)
		{
			return SUCCEEDED(shader->SetMatrixArray(parameter, ary, count));
		}

		bool ShaderDX::SetVariable(char *parameter, SOC_Vector4 *v)
		{
			return SUCCEEDED(shader->SetVector(parameter, v));
		}

		bool ShaderDX::SetVariable(char *parameter, SOC_Vector4 *ary, SOC_uint count)
		{
			return SUCCEEDED(shader->SetVectorArray(parameter, ary, count));
		}

		bool ShaderDX::SetVariable(char *parameter, bool b)
		{
			return SUCCEEDED(shader->SetBool(parameter, b));
		}

		bool ShaderDX::SetVariable(char *parameter, float f)
		{
			return SUCCEEDED(shader->SetFloat(parameter, f));
		}

		bool ShaderDX::SetVariable(char *parameter, float *ary, SOC_uint count)
		{
			return SUCCEEDED(shader->SetFloatArray(parameter, ary, count));
		}

		bool ShaderDX::SetVariable(char *parameter, int i)
		{
			return SUCCEEDED(shader->SetInt(parameter, i));
		}

		bool ShaderDX::SetVariable(char *parameter, int *ary, SOC_uint count)
		{
			return SUCCEEDED(shader->SetIntArray(parameter, ary, count));
		}

		bool ShaderDX::SetTechnique(char *technique)
		{
			return SUCCEEDED(shader->SetTechnique(technique));
		}

		bool ShaderDX::SetVariable(char *parameter, Texture::Texture *texture)
		{
			LPDIRECT3DTEXTURE9 tex = texture->GetTexture();
			return SUCCEEDED( shader->SetTexture(parameter, tex) );
		}

		bool ShaderDX::Begin()
		{
			return SUCCEEDED( shader->Begin(&this->numPass, NULL) );
		}

		bool ShaderDX::BeginPass(SOC_uint pass)
		{
			return SUCCEEDED( shader->BeginPass(pass) );
		}

		bool ShaderDX::EndPass()
		{
			return SUCCEEDED( shader->EndPass() );
		}

		bool ShaderDX::End()
		{
			return SUCCEEDED( shader->End() );
		}
	}
}