#include "IndexBuffer.h"


namespace Rendering
{
	namespace Buffer
	{
		IndexBuffer::IndexBuffer(int count, Device::Graphics *graphics)
		{
			this->count = count;
			this->graphics = graphics;
			indexBuffer = NULL;
		}

		IndexBuffer::~IndexBuffer(void)
		{
			if(indexBuffer)
				indexBuffer->Release();
		}

		bool IndexBuffer::Create(SOC_POOL pool)
		{
			return graphics->CreateIndexBuffer(sizeof(SOC_word) * count, pool, &indexBuffer);
		}

		bool IndexBuffer::Lock(void** inputData)
		{
			return SUCCEEDED( indexBuffer->Lock( 0, sizeof(SOC_word) * count, inputData, NULL) );
		}

		bool IndexBuffer::UnLock()
		{
			return SUCCEEDED( indexBuffer->Unlock() );
		}

		DeviceIndexBuffer IndexBuffer::GetDeviceBuffer()
		{
			return indexBuffer;
		}

		int IndexBuffer::GetCount()
		{
			return count;
		}
	}
}