#pragma once

#include "Rendering.h"
#include <utility>

namespace Rendering
{
	namespace Buffer
	{
		class IndexBufferForm
		{
		protected:
			int count;
			Device::Graphics::GraphicsForm *graphics;

		public:
			IndexBufferForm(int count, Device::Graphics::GraphicsForm *graphics)
			{
				//NULL
				this->count = count;
				this->graphics = graphics;
			}

			virtual ~IndexBufferForm(void)
			{
			}

		public:
			virtual bool	Create(SOC_POOL pool) = 0;
			virtual bool	Lock(void** inputData) = 0;
			virtual bool	UnLock() = 0;

		public:
			int GetCount()
			{
				return count;
			}
			virtual void* GetBuffer() = 0;
		};

	}
}