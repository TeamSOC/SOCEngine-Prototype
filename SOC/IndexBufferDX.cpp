#include "IndexBufferDX.h"


namespace Rendering
{
	namespace Buffer
	{
		IndexBufferDX::IndexBufferDX(int count, Device::Graphics::GraphicsForm *graphics) : IndexBufferForm(count, graphics)
		{
			indexBuffer = NULL;
		}

		IndexBufferDX::~IndexBufferDX(void)
		{
			if(indexBuffer)
				indexBuffer->Release();
		}

		bool IndexBufferDX::Create(SOC_POOL pool)
		{
			return graphics->CreateIndexBuffer(sizeof(SOC_word) * count, pool, (void**)&indexBuffer);
		}

		bool IndexBufferDX::Lock(void** inputData)
		{
			return SUCCEEDED( indexBuffer->Lock( 0, sizeof(SOC_word) * count, inputData, NULL) );
		}

		bool IndexBufferDX::UnLock()
		{
			return SUCCEEDED( indexBuffer->Unlock() );
		}

		void* IndexBufferDX::GetBuffer()
		{
			return indexBuffer;
		}
	}
}