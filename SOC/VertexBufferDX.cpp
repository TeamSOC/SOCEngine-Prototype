#include "VertexBufferDX.h"

namespace Rendering
{
	namespace Buffer
	{
		VertexBufferDX::VertexBufferDX(int vertexBufferSize, int numOfVertex, Device::Graphics::GraphicsForm *graphics) 
			: VertexBufferForm(vertexBufferSize, numOfVertex, graphics)
		{
			vertexBuffer = NULL;
			device = dynamic_cast<Device::Graphics::DX*>( graphics )->GetD3DDevice();
		}

		VertexBufferDX::~VertexBufferDX(void)
		{
			if (vertexBuffer)
			{
				vertexBuffer->Release();
				vertexBuffer = NULL;
			}
		}

		bool VertexBufferDX::Create(SOC_dword usage, SOC_POOL pool)
		{
			return graphics->CreateVertexBuffer(GetLength(), usage, pool, &vertexBuffer);
		}

		bool VertexBufferDX::Lock(void **inputData)
		{
			return SUCCEEDED(vertexBuffer->Lock(0, GetLength(), inputData, NULL));
		}

		bool VertexBufferDX::UnLock()
		{
			return SUCCEEDED( vertexBuffer->Unlock() );
		}

		DeviceVertexBuffer VertexBufferDX::GetDeviceBuffer()
		{
			return vertexBuffer;
		}
	}
}