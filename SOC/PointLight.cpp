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

		//bool PointLight::Intersect(Intersection::Sphere &sphere)
		//{
		//애초에 그냥 구 충돌인데 다른게 있나?
		//}
	}
}