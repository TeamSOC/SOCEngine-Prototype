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
			int numOfVertex;
			Device::Graphics::GraphicsForm *graphics;

		public:
			VertexBufferForm(int vertexBufferSize, int numOfVertex, Device::Graphics::GraphicsForm *graphics)
			{
				//NULL
				this->vertexBufferSize = vertexBufferSize;
				this->graphics = graphics;
				this->numOfVertex = numOfVertex;
			}

			virtual ~VertexBufferForm(void)
			{

			}

		public:
			virtual bool Create(SOC_dword usage, SOC_POOL pool) = 0;
			virtual bool Lock(void **inputData) = 0;
			virtual bool UnLock() = 0;

		public:
			int GetNumOfVertex()
			{
				return numOfVertex;
			}
			int GetLength()
			{
				return vertexBufferSize * numOfVertex;
			}
			int GetSize()
			{
				return vertexBufferSize;
			}

			virtual void* GetDeviceBuffer() = 0;
		};
	}
}
