//
//  TextureGL.cpp
//  Rendering
//
//  Created by Jiman Jeong on 13. 9. 17..
//  Copyright (c) 2013년 SOC. All rights reserved.
//

#include "TextureGL.h"

namespace Rendering
{
	namespace Texture
	{
		TextureGL::TextureGL(void)
		{
		}
		
		TextureGL::~TextureGL(void)
		{
		}
		
		bool TextureGL::Create(const char *path)
		{
			Device::Graphics::GraphicsForm *device = Device::DeviceDirector::GetInstance()->GetGraphics();
			
//			
//			this->size.w = desc.Width;
//			this->size.h = desc.Height;
			
			return true;
		}
		
		DeviceTexture TextureGL::GetTexture()
		{
			return texture;
		}
	}
}