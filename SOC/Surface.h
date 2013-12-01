#pragma once

#include "Platform.h"

namespace Rendering
{
	namespace Buffer
	{

		class Surface
		{
		private:
			Device::Graphics *graphics;
			DeviceSurface surface;

		public:
			Surface(Device::Graphics *graphics)
			{
				this->graphics = graphics;
				surface = nullptr;
			}

			~Surface(void)
			{
				Utility::SAFE_RELEASE(surface);
			}

		public:
			void GetRenderTarget(SOC_uint renderTargetIdx)
			{
				ReleaseSurface();
				graphics->GetRenderTarget(renderTargetIdx, &surface);
			}

			void SetRenderTarget(SOC_uint renderTargetIdx)
			{
				graphics->SetRenderTarget(renderTargetIdx, surface);
			}

			void ReleaseSurface()
			{
				if(surface)
				{
					surface->Release();
					surface = nullptr;
				}
			}

			bool hasSurface()
			{
				return surface == nullptr ? false : true;
			}

			void GetSurfaceLevel(DeviceTexture texture, SOC_uint level)
			{
				ReleaseSurface();
				texture->GetSurfaceLevel(level, &surface);
			}
		};

	}
}