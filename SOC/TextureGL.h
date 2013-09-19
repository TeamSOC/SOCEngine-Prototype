//
//  TextureGL.h
//  Rendering
//
//  Created by Jiman Jeong on 13. 9. 17..
//  Copyright (c) 2013년 SOC. All rights reserved.
//

#pragma once

#include "TextureForm.h"
#include "DeviceDirector.h"

namespace Rendering
{
	namespace Texture
	{
		class TextureGL : public TextureForm
		{
			DeviceTexture texture;
			
		public:
			TextureGL(void);
			~TextureGL(void);
			
		public:
			virtual bool Create(const char *path);
			
		public:
			virtual DeviceTexture GetTexture();
		};
	}
}