#include "LightForm.h"

namespace Rendering
{
	namespace Light
	{
		LightForm::LightForm(Object *parent) : Object(parent)
		{
			diffuse		= Color::white();
			specular	= Color::white();

			onSpecular = true;

			range = 0.0f;
			intensity = 1.0f;
			specularPower = 20.0f;

			isLight = true;
		}
	}
}