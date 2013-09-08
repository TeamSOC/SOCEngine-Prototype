#pragma once

#include "TextureForm.h"
#include "DeviceDirector.h"

namespace Rendering
{
	namespace Texture
	{
		class TextureDX : public TextureForm
		{
		private:
			LPDIRECT3DTEXTURE9 texture;

		public:
			TextureDX(void);
			~TextureDX(void);

		public:
			bool Create(const char *path);

		public:
			DeviceTexture GetTexture();
		};
	}
}