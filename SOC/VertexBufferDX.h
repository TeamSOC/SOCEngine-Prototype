#pragma once

#include "VertexBufferForm.h"

namespace Rendering
{
	namespace Buffer
	{
		class VertexBufferDX : public VertexBufferForm
		{
		private:
			LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
			LPDIRECT3DDEVICE9 device;

		public:
			VertexBufferDX(int vertexBufferSize, Device::Graphics::GraphicsForm *graphics) 
				: VertexBufferForm(vertexBufferSize)
			{
				vertexBuffer = NULL;
				device = dynamic_cast<Device::Graphics::DX*>( graphics )->GetD3DDevice();
			}

			~VertexBufferDX(void)
			{
				if (vertexBuffer)
				{
					vertexBuffer->Release();
					vertexBuffer = NULL;
				}
			}

		public:
			bool Create(SOC_dword usage, SOC_POOL pool)
			{
				return SUCCEEDED( device->CreateVertexBuffer(vertexBufferSize, usage, 0, pool == SOC_POOL_DEFAULT ? D3DPOOL_DEFAULT : D3DPOOL_MANAGED, &vertexBuffer, NULL) );
			}

			bool Lock(void **inputData)
			{
				return SUCCEEDED(vertexBuffer->Lock(0, vertexBufferSize, inputData, NULL));
			}

			bool UnLock()
			{
				return SUCCEEDED( vertexBuffer->Unlock() );
			}
		};
	}
}