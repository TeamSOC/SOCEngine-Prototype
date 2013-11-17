#pragma once

#include "DeviceDirector.h"
#include "Platform.h"

namespace Rendering
{
	namespace Buffer
	{
		class VertexBuffer
		{
		private:
			int vertexBufferSize;
			int numOfVertex;
			Device::Graphics *graphics;

			LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
			LPDIRECT3DDEVICE9 device;

		public:
			VertexBuffer(int vertexBufferSize, int numOfVertex, Device::Graphics *graphics);
			~VertexBuffer(void);

		public:
			bool Create(SOC_dword usage, SOC_POOL pool);
			bool Lock(void **inputData);
			bool UnLock();

		public:
			int GetNumOfVertex();
			int GetLength();
			int GetSize();

			DeviceVertexBuffer GetDeviceBuffer();
		};
	}
}