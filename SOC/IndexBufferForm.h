#pragma once

#include "Rendering.h"
#include <utility>

namespace Rendering
{
	namespace Buffer
	{
		class IndexBufferForm
		{
		public:
			int count;

		public:
			IndexBufferForm(int count, Device::Graphics::GraphicsForm *graphics = NULL)
			{
				//NULL
				this->count = count;
			}

			~IndexBufferForm(void)
			{
			}

		public:
			virtual bool Create(SOC_POOL pool) = 0;
			virtual bool Lock(void** inputData) = 0;
			virtual bool UnLock() = 0;

		public:
			int GetCount()
			{
				return count;
			}
		};

	}
}