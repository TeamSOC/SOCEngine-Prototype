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
			VertexBufferDX(int vertexBufferSize, int numOfVertex, Device::Graphics::GraphicsForm *graphics) 
				: VertexBufferForm(vertexBufferSize, numOfVertex, graphics)
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
				return graphics->CreateVertexBuffer(GetLength(), usage, pool, (void**)&vertexBuffer);
			}

			bool Lock(void **inputData)
			{
				return SUCCEEDED(vertexBuffer->Lock(0, GetLength(), inputData, NULL));
			}

			bool UnLock()
			{
				return SUCCEEDED( vertexBuffer->Unlock() );
			}

		public:
			void* GetDeviceBuffer()
			{
				return vertexBuffer;
			}
		};
	}
}