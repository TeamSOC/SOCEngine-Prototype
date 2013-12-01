#include "Texture.h"

namespace Rendering
{
	namespace Texture
	{
		Texture::Texture(void)
		{
			texture = NULL;
		}

		Texture::~Texture(void)
		{
			texture->Release();
		}

		bool Texture::Create(const char *path)
		{
			Device::Graphics *device = dynamic_cast<Device::Graphics*>( Device::DeviceDirector::GetInstance()->GetGraphics() );

			if( FAILED(D3DXCreateTextureFromFile(device->GetD3DDevice(), path, &texture)) )
				return false;

			D3DSURFACE_DESC desc;
			texture->GetLevelDesc(0, &desc);

			this->size.w = desc.Width;
			this->size.h = desc.Height;

			return true;
		}

		LPDIRECT3DTEXTURE9 Texture::GetTexture()
		{
			return texture;
		}

		Common::Size<int> Texture::GetSize()
		{
			return size;
		}

		float Texture::GetAlpha()
		{
			return alpha;
		}
	}
}