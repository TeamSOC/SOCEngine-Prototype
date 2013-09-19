//
//  ShaderManagerGL.h
//  Rendering
//
//  Created by Jiman Jeong on 13. 9. 19..
//  Copyright (c) 2013년 SOC. All rights reserved.
//

#pragma once

#include "ShaderManagerForm.h"

namespace Rendering
{
	namespace Shader
	{
		class ShaderManagerGL : public ShaderManagerForm
		{
		public:
			ShaderManagerGL();
			virtual ~ShaderManagerGL();
			
		public:
			virtual bool LoadShaderFromFile( std::string path, ShaderCode *outShaderCode, bool inShaderFolder);
			virtual bool FindShader(std::string path, std::string *outShaderCode, bool inResourceFolder);
			
			virtual void DeleteAll();
		};
	}
}
