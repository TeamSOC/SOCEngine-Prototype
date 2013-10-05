#pragma once

#include "Device.h"
#include "Size.h"

namespace Rendering
{
	namespace Texture
	{
		class TextureForm
		{
		protected:
			Common::Size<int> size;
			float alpha;

		public:
			TextureForm(void);
			virtual ~TextureForm(void);

		public:
			virtual bool Create(const char *path) = 0;

		public:
			Common::Size<int> GetSize();
			virtual DeviceTexture GetTexture() = 0;
			float GetAlpha();
		};
	}
}