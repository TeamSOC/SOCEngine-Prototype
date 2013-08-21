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
			LPDIRECT3DDEVICE9 device;

		public:
			IndexBufferDX(int count, Device::Graphics::GraphicsForm *graphics) : IndexBufferForm(count, graphics)
			{
				device = dynamic_cast<Device::Graphics::DX*>( graphics )->GetD3DDevice();
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
				D3DPOOL d3dPool = pool == SOC_POOL_DEFAULT ? D3DPOOL_DEFAULT : D3DPOOL_MANAGED;
				return SUCCEEDED( device->CreateIndexBuffer( 0, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, d3dPool, &indexBuffer, NULL) );
			}

			bool Lock(void** inputData)
			{
				return SUCCEEDED( indexBuffer->Lock( sizeof(SOC_word) * count, 0, inputData, NULL) );
			}

			bool UnLock()
			{
				return SUCCEEDED( indexBuffer->Unlock() );
			}
		};

	}
}