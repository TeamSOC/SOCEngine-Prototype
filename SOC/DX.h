#pragma once

#include "GraphicsForm.h"
#include "Windows.h"

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace Device
{
	namespace Graphics
	{
		class DX : public GraphicsForm
		{
		private:
			float elapse;
			float  fps;	

		private:
			LPDIRECT3D9			d3dHandle;
			LPDIRECT3DDEVICE9	device;

			D3DPRESENT_PARAMETERS d3dpp;

		public:
			DX(PRESENT_INTERVAL interval, Application::Application *app) 
				: GraphicsForm(interval, app)
			{
				ZeroMemory(&d3dpp, sizeof(d3dpp));

				Application::Windows *win = dynamic_cast<Application::Windows*>(app);

				d3dpp.Windowed = win->IsWindowMode();

				if(interval == PRESENT_INTERVAL_DEFAULT)
					d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
				else if( interval == PRESENT_INTERVAL_IMMEDIATE )
					d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
				else d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

				d3dpp.BackBufferWidth				= win->GetSize().w;
				d3dpp.BackBufferHeight				= win->GetSize().h;
				d3dpp.BackBufferFormat				= D3DFMT_X8R8G8B8;
				d3dpp.BackBufferCount				= 1;
				d3dpp.MultiSampleType				= D3DMULTISAMPLE_NONE;
				d3dpp.MultiSampleQuality			= 0;
				d3dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;
				d3dpp.hDeviceWindow					= win->GetHandle();
				d3dpp.EnableAutoDepthStencil		= TRUE;
				d3dpp.AutoDepthStencilFormat		= D3DFMT_D24X8;
				d3dpp.Flags							= D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
				d3dpp.FullScreen_RefreshRateInHz	= 0;
			}

			~DX(void)
			{
				if(d3dHandle)
				{
					d3dHandle->Release();
					d3dHandle = nullptr;
				}

				if(device)
				{
					device->Release();
					device = nullptr;
				}
			}

		public:
			bool DX::Initialize()
			{
				if(FAILED(d3dHandle->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &device)))
					return false;

				return true;
			}

		public:
			bool Clear(unsigned int count, const Common::Rect<int> *rect, clearFlag flags, Rendering::Color &color, float z, unsigned int stencil)
			{				
				D3DCOLOR d3dColor = D3DCOLOR_COLORVALUE(color.r, color.g, color.b, color.a);

				//SOC_dword flag;
				//if(flags & CLEAR_FLAG_TARGET)
				//	flag |= D3DCLEAR_TARGET;
				//if(flags & CLEAR_FLAG_STENCIL)
				//	flag |= D3DCLEAR_STENCIL

				if(rect == nullptr)	
					device->Clear(0, NULL, flags, d3dColor, z, stencil);
				else
				{
					D3DRECT d3dRect;
					d3dRect.x1 = rect->x;
					d3dRect.y1 = rect->y;
					d3dRect.x2 = rect->x + rect->size.w;
					d3dRect.y2 = rect->y + rect->size.h;

					device->Clear(count, &d3dRect, flags, d3dColor, z, stencil);
				}
			}

		public:
			LPDIRECT3DDEVICE9 GetD3DDevice()
			{
				return device;
			}

		public:
			void CalcElapse()
			{
				static float		lastTime;
				float				now;
				static unsigned int	staticTime = GetTickCount();


				now = (float)(GetTickCount() - staticTime) / 1000;

				elapse = now - lastTime;
				elapse = Utility::Max((float)0, elapse);

				lastTime = now;
			}
			void CalculateFPS()
			{
				static int frameCnt = 0;
				static float elapsed = 0;

				frameCnt++;
				elapsed += elapse;

				if( elapsed >= 1.f )
				{
					fps = (float)frameCnt / elapsed;
					elapsed = 0;
					frameCnt = 0;
				}
			}
		};

	}
}