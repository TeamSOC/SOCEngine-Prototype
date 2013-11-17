#pragma once

#include "DeviceDirector.h"

namespace Rendering
{
	namespace Texture
	{
		class Texture
		{
		private:
			LPDIRECT3DTEXTURE9 texture;
			Common::Size<int> size;
			float alpha;

		public:
			Texture(void);
			~Texture(void);

		public:
			bool Create(const char *path);
			bool Create(int width, int height);

		public:
			bool GetRenderTarget(SOC_uint level, DeviceSurface *surface);
			DeviceTexture GetTexture();
			float GetAlpha();
			Common::Size<int> GetSize();
		};
	}
}