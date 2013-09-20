//
//  ShaderGL.h
//  Rendering
//
//  Created by Jiman Jeong on 13. 9. 18..
//  Copyright (c) 2013년 SOC. All rights reserved.
//

#ifndef __Rendering__ShaderGL__
#define __Rendering__ShaderGL__

#include "ShaderForm.h"

namespace Rendering
{
	namespace Shader
	{
		class ShaderGL : public ShaderForm
		{
		public:
			ShaderGL(Device::Graphics::GraphicsForm *graphics, const char *name = nullptr);
			virtual ~ShaderGL(void);
			
		public:
			virtual bool Compile(std::string &shaderCode);
			virtual void GetRequiredParameters(SOC_byte *outMatrixParamters, SOC_byte *outLightParameters, char *technique = DEFAULT_TECHNIQUE);
			
			virtual bool SetVariable(const char *parameter, SOC_Matrix *m);
			virtual bool SetVariable(const char *parameter, SOC_Matrix *ary, SOC_uint count);
			virtual bool SetVariable(const char *parameter, SOC_Vector4 *v);
			virtual bool SetVariable(const char *parameter, SOC_Vector4 *ary, SOC_uint count);
			virtual bool SetVariable(const char *parameter, bool b);
			virtual bool SetVariable(const char *parameter, float f);
			virtual bool SetVariable(const char *parameter, float *ary, SOC_uint count);
			virtual bool SetVariable(const char *parameter, int i);
			virtual bool SetVariable(const char *parameter, int *ary, SOC_uint count);
			virtual bool SetVariable(const char *parameter, Texture::Texture *texture);
			
			virtual bool SetTechnique(const char *technique);
			virtual bool IsParameterUsed(const char *paramter, const char *technique);
			
			virtual bool Begin();
			virtual bool BeginPass(SOC_uint pass);
			virtual bool EndPass();
			virtual bool End();
		};

	}
}

#endif /* defined(__Rendering__ShaderGL__) */
