#pragma once

#include "Platform.h"

namespace Rendering
{
	namespace Buffer
	{
		class IndexBuffer
		{
		private:
			LPDIRECT3DINDEXBUFFER9 indexBuffer;
			Device::Graphics *graphics;
			int count;

		public:
			IndexBuffer();
			IndexBuffer(int count, Device::Graphics *graphics);
			~IndexBuffer(void);

		public:
			bool Create(SOC_POOL pool);
			bool Create(LPD3DXMESH mesh)
			{
				mesh->GetIndexBuffer(&indexBuffer);
				return true;
			}

			bool Lock(void** inputData);
			bool UnLock();

		public:
			DeviceIndexBuffer GetDeviceBuffer();
			int GetCount();
		};

	}
}