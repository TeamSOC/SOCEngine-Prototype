#include "TextureDX.h"

namespace Rendering
{
	namespace Texture
	{
		TextureDX::TextureDX(void)
		{
			texture = NULL;
		}

		TextureDX::~TextureDX(void)
		{
			texture->Release();
		}

		bool TextureDX::Create(const char *path)
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

		LPDIRECT3DTEXTURE9 TextureDX::GetTexture()
		{
			return texture;
		}
	}
}