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

		bool Texture::Create(int width, int height)
		{
			Device::Graphics *dx = dynamic_cast<Device::Graphics*>( Device::DeviceDirector::GetInstance()->GetGraphics() );

			if(FAILED(D3DXCreateTexture(dx->GetD3DDevice(), width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &texture)))
				return false;

			size.w = width;
			size.h = height;

			return true;
		}

		bool Texture::GetRenderTarget(SOC_uint level, DeviceSurface *surface)
		{
			return SUCCEEDED( texture->GetSurfaceLevel(level, surface) );
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