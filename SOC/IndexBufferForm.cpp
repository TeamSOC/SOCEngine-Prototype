#include "IndexBufferForm.h"

namespace Rendering
{
	namespace Buffer
	{
		IndexBufferForm::IndexBufferForm(int count, Device::Graphics::GraphicsForm *graphics)
		{
			//NULL
			this->count = count;
			this->graphics = graphics;
		}

		int IndexBufferForm::GetCount()
		{
			return count;
		}
	}
}