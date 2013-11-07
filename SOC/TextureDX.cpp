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

			if( FAILED(D3DXCreateTextureFromFile(device->GetD3DDevice(), path, &texture)) )
				return false;

			D3DSURFACE_DESC desc;
			texture->GetLevelDesc(0, &desc);

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