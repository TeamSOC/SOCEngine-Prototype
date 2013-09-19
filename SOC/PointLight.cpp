#include "PointLight.h"

namespace Rendering
{
	namespace Light
	{
		PointLight::PointLight(Object *parent) : LightForm(parent)
		{
			type = LIGHTTYPE_POINT;
		}

		PointLight::~PointLight(void)
		{
		}

//		bool PointLight::Intersect(Intersection::Sphere &sphere)
//		{
//			return true;
//		}
	}
}