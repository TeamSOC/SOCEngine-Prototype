#pragma once

#include "DeviceDirector.h"

namespace Rendering
{
	namespace Texture
	{
		class Texture
		{
		protected:
			LPDIRECT3DTEXTURE9 texture;
			Common::Size<int> size;
			float alpha;

		public:
			Texture(void);
			~Texture(void);

		public:
			bool Create(const char *path);

		public:
			DeviceTexture GetTexture();
			float GetAlpha();
			Common::Size<int> GetSize();
		};
	}
}