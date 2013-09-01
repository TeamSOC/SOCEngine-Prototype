#pragma once

#include "Rendering.h"

namespace Rendering
{
	namespace Buffer
	{
		class VertexBufferForm
		{
		protected:
			int vertexBufferSize;
			Device::Graphics::GraphicsForm *graphics;

		public:
			VertexBufferForm(int verTexBufferSize, Device::Graphics::GraphicsForm *graphics)
			{
				//NULL
				this->vertexBufferSize = verTexBufferSize;
				this->graphics = graphics;
			}

			~VertexBufferForm(void);

		public:
			virtual bool Create(SOC_dword usage, SOC_POOL pool) = 0;
			virtual bool Lock(void **inputData) = 0;
			virtual bool UnLock() = 0;

		public:
			int GetVertexBufferSize()
			{
				return vertexBufferSize;
			}
			virtual void* GetBuffer() = 0;
		};
	}
}
