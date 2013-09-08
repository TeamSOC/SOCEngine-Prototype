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
			VertexBufferDX(int vertexBufferSize, int numOfVertex, Device::Graphics::GraphicsForm *graphics);
			~VertexBufferDX(void);

		public:
			bool Create(SOC_dword usage, SOC_POOL pool);
			bool Lock(void **inputData);
			bool UnLock();

		public:
			void* GetDeviceBuffer();
		};
	}
}