#include "TextureForm.h"

namespace Rendering
{
	namespace Texture
	{
		TextureForm::TextureForm(void)
		{
		}

		TextureForm::~TextureForm(void)
		{
		}

		Common::Size<int> TextureForm::GetSize()
		{
			return size;
		}
	}
}