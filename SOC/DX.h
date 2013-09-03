#pragma once

#include "GraphicsForm.h"
#include "Windows.h"

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
				d3dHandle = Direct3DCreate9( D3D_SDK_VERSION );

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

				bool success = false;

				if(rect == nullptr)	
					success = SUCCEEDED( device->Clear(0, NULL, flags, d3dColor, z, stencil) );
				else
				{
					D3DRECT d3dRect;
					d3dRect.x1 = rect->x;
					d3dRect.y1 = rect->y;
					d3dRect.x2 = rect->x + rect->size.w;
					d3dRect.y2 = rect->y + rect->size.h;

					success = SUCCEEDED( device->Clear(count, &d3dRect, flags, d3dColor, z, stencil) );
				}

				return success;
			}

			bool Clear(clearFlag flags, Rendering::Color &color)
			{
				return Clear(0, NULL, flags, color, 1.0f, 0L);
			}

			bool CreateVertexBuffer(int bufferLength, SOC_dword usage, SOC_POOL pool, void** outBuffer)
			{
				LPDIRECT3DVERTEXBUFFER9 *buffer = (LPDIRECT3DVERTEXBUFFER9*)outBuffer;
				return SUCCEEDED( device->CreateVertexBuffer(bufferLength, usage, 0, pool == SOC_POOL_DEFAULT ? D3DPOOL_DEFAULT : D3DPOOL_MANAGED, buffer, NULL) );
			}

			bool CreateIndexBuffer(int bufferLength, SOC_POOL pool, void** outBuffer)
			{
				D3DPOOL d3dPool = pool == SOC_POOL_DEFAULT ? D3DPOOL_DEFAULT : D3DPOOL_MANAGED;				
				return SUCCEEDED( device->CreateIndexBuffer( bufferLength, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, d3dPool, (LPDIRECT3DINDEXBUFFER9*)outBuffer, NULL) );;
			}

			bool SetIndices( void *indexBuffer )
			{
				LPDIRECT3DINDEXBUFFER9 idxBuffer = (LPDIRECT3DINDEXBUFFER9)indexBuffer;
				return SUCCEEDED( device->SetIndices(idxBuffer) );
			}

			bool DrawIndexedPrimitive(SOC_TRIANGLE type, SOC_int baseVertexIdx, SOC_uint minVertexIdx, SOC_uint numVertices, SOC_uint startIdx, SOC_uint primitiveCount)
			{
				D3DPRIMITIVETYPE d3dPrimitiType = (D3DPRIMITIVETYPE)type;
				return SUCCEEDED( device->DrawIndexedPrimitive(d3dPrimitiType, baseVertexIdx, minVertexIdx, numVertices, startIdx, primitiveCount) );
			}

			bool SetVertexStream(SOC_uint stream, void *deviceVertexBuffer, SOC_uint stride)
			{
				LPDIRECT3DVERTEXBUFFER9 vb = (LPDIRECT3DVERTEXBUFFER9)deviceVertexBuffer;
				return SUCCEEDED(device->SetStreamSource( stream, vb, 0, stride));
			}

			bool SetVertexStremFrequency(SOC_uint stream, SOC_uint frequency)
			{
				if(frequency == 0)
					frequency = 1;

				frequency = stream == 0 ? D3DSTREAMSOURCE_INDEXEDDATA | frequency : D3DSTREAMSOURCE_INSTANCEDATA | frequency;
				return SUCCEEDED( device->SetStreamSourceFreq(stream, frequency) );
			}

			bool BeginScene()
			{
				return SUCCEEDED(	device->BeginScene() );
			}

			 bool EndScene()
			{
				return SUCCEEDED( device->EndScene() );
			}

			void Presnet()
			{
				device->Present(NULL, NULL, NULL, NULL);
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