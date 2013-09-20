#include "DirectionalLight.h"

namespace Rendering
{
	namespace Light
	{
		DirectionalLight::DirectionalLight() : LightForm()
		{
			type = LIGHTTYPE_DIRECTIONAL;
		}

		DirectionalLight::~DirectionalLight()
		{
		}

		bool DirectionalLight::Intersect(Intersection::Sphere &sphere)
		{
			return true;
		}
	}
}