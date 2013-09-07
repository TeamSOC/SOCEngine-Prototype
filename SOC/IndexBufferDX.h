#pragma once

#include "IndexBufferForm.h"

namespace Rendering
{
	namespace Buffer
	{
		class IndexBufferDX : public IndexBufferForm
		{
		private:
			LPDIRECT3DINDEXBUFFER9 indexBuffer;
//			LPDIRECT3DDEVICE9 device;

		public:
			IndexBufferDX(int count, Device::Graphics::GraphicsForm *graphics) : IndexBufferForm(count, graphics)
			{
//				device = dynamic_cast<Device::Graphics::DX*>( graphics )->GetD3DDevice();
				indexBuffer = NULL;
			}

			~IndexBufferDX(void)
			{
				if(indexBuffer)
					indexBuffer->Release();
			}

		public:
			bool Create(SOC_POOL pool)
			{
				return graphics->CreateIndexBuffer(sizeof(SOC_word) * count, pool, (void**)&indexBuffer);
			}

			bool Lock(void** inputData)
			{
				return SUCCEEDED( indexBuffer->Lock( 0, sizeof(SOC_word) * count, inputData, NULL) );
			}

			bool UnLock()
			{
				return SUCCEEDED( indexBuffer->Unlock() );
			}

		public:
			void* GetBuffer()
			{
				return indexBuffer;
			}
		};

	}
}