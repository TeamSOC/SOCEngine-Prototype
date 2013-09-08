#pragma once

#include "IndexBufferForm.h"

namespace Rendering
{
	namespace Buffer
	{
		class IndexBufferDX : public IndexBufferForm
		{
		private:
			LPDIRECT3DINDEXBUFFER9 indexBuffer;

		public:
			IndexBufferDX(int count, Device::Graphics::GraphicsForm *graphics);
			~IndexBufferDX(void);

		public:
			bool Create(SOC_POOL pool);
			bool Lock(void** inputData);
			bool UnLock();

		public:
			void* GetBuffer();
		};

	}
}