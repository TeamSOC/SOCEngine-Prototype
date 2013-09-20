//
//  ShaderGL.cpp
//  Rendering
//
//  Created by Jiman Jeong on 13. 9. 18..
//  Copyright (c) 2013년 SOC. All rights reserved.
//

#include "ShaderGL.h"

namespace Rendering
{
	namespace Shader
	{
		ShaderGL::ShaderGL(Device::Graphics::GraphicsForm *graphics, const char *name)
		: ShaderForm(graphics, name)
		{
			
		}
		
		ShaderGL::~ShaderGL()
		{
			
		}
		
		
		bool ShaderGL::Compile(std::string &shaderCode)
		{
			return false;
		}
		
		void ShaderGL::GetRequiredParameters(SOC_byte *outMatrixParamters, SOC_byte *outLightParameters, char *technique)
		{
		}
		
		bool ShaderGL::SetVariable(const char *parameter, SOC_Matrix *m)
		{
			return false;
		}
		
		bool ShaderGL::SetVariable(const char *parameter, SOC_Matrix *ary, SOC_uint count)
		{
			return false;
		}
		
		bool ShaderGL::SetVariable(const char *parameter, SOC_Vector4 *v)
		{
			return false;
		}
		
		bool ShaderGL::SetVariable(const char *parameter, SOC_Vector4 *ary, SOC_uint count)
		{
			return false;
		}
		
		bool ShaderGL::SetVariable(const char *parameter, bool b)
		{
			return false;
		}
		
		bool ShaderGL::SetVariable(const char *parameter, float f)
		{
			return false;
		}
		
		bool ShaderGL::SetVariable(const char *parameter, float *ary, SOC_uint count)
		{
			return false;
		}
		
		bool ShaderGL::SetVariable(const char *parameter, int i)
		{
			return false;
		}
		
		bool ShaderGL::SetVariable(const char *parameter, int *ary, SOC_uint count)
		{
			return false;
		}
		
		bool ShaderGL::SetVariable(const char *parameter, Texture::Texture *texture)
		{
			return false;
		}
		
		bool ShaderGL::SetTechnique(const char *technique)
		{
			return false;
		}
		
		bool ShaderGL::IsParameterUsed(const char *paramter, const char *technique)
		{
			return false;
		}
		
		bool ShaderGL::Begin()
		{
			return false;
		}
		
		bool ShaderGL::BeginPass(SOC_uint pass)
		{
			return false;
		}
		
		bool ShaderGL::EndPass()
		{
			return false;
		}
		
		bool ShaderGL::End()
		{
			return false;
		}
	}
}