#include "DirectionalLight.h"


namespace Rendering
{
	namespace Light
	{
		DirectionalLight::DirectionalLight(Object *parent) : LightForm(parent)
		{
			type = LIGHTTYPE_DIRECTIONAL;
		}

		DirectionalLight::~DirectionalLight(void)
		{
		}

		bool DirectionalLight::Intersect(Intersection::Sphere &sphere)
		{
			return true;
		}
	}
}