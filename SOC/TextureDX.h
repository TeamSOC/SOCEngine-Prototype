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
			TextureDX(void)
			{
				texture = NULL;
			}

			~TextureDX(void)
			{
				texture->Release();
			}

		public:
			bool Create(const char *path)
			{
				Device::Graphics::DX *device = dynamic_cast<Device::Graphics::DX*>( Device::DeviceDirector::GetInstance()->GetGraphics() );

				LPDIRECT3DTEXTURE9 tex;
				if( FAILED(D3DXCreateTextureFromFile(device->GetD3DDevice(), path, &tex)) )
					return false;

				D3DSURFACE_DESC desc;
				tex->GetLevelDesc(0, &desc);

				this->size.w = desc.Width;
				this->size.h = desc.Height;

				return true;
			}

		public:
			LPDIRECT3DTEXTURE9 GetTexture()
			{
				return texture;
			}
		};
	}
}