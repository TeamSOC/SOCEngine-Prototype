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
			IndexBufferForm(int count, Device::Graphics::GraphicsForm *graphics);

		public:
			virtual bool	Create(SOC_POOL pool) = 0;
			virtual bool	Lock(void** inputData) = 0;
			virtual bool	UnLock() = 0;

		public:
			int GetCount();
			virtual void* GetBuffer() = 0;
		};

	}
}