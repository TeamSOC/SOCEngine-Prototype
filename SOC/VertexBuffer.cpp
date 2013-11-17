#include "VertexBuffer.h"

namespace Rendering
{
	namespace Buffer
	{
		VertexBuffer::VertexBuffer(int vertexBufferSize, int numOfVertex, Device::Graphics *graphics)
		{
			this->vertexBufferSize = vertexBufferSize;
			this->graphics = graphics;
			this->numOfVertex = numOfVertex;

			vertexBuffer = NULL;
			device = dynamic_cast<Device::Graphics*>( graphics )->GetD3DDevice();
		}

		VertexBuffer::~VertexBuffer(void)
		{
			if (vertexBuffer)
			{
				vertexBuffer->Release();
				vertexBuffer = NULL;
			}
		}

		bool VertexBuffer::Create(SOC_dword usage, SOC_POOL pool)
		{
			return graphics->CreateVertexBuffer(GetLength(), usage, pool, &vertexBuffer);
		}

		bool VertexBuffer::Lock(void **inputData)
		{
			return SUCCEEDED(vertexBuffer->Lock(0, GetLength(), inputData, NULL));
		}

		bool VertexBuffer::UnLock()
		{
			return SUCCEEDED( vertexBuffer->Unlock() );
		}

		DeviceVertexBuffer VertexBuffer::GetDeviceBuffer()
		{
			return vertexBuffer;
		}

		int VertexBuffer::GetNumOfVertex()
		{
			return numOfVertex;
		}
		int VertexBuffer::GetLength()
		{
			return vertexBufferSize * numOfVertex;
		}
		int VertexBuffer::GetSize()
		{
			return vertexBufferSize;
		}

	}
}