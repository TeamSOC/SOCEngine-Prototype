#include "PointLight.h"
#include "Transform.h"

namespace Rendering
{
	namespace Light
	{
		PointLight::PointLight() : LightForm()
		{
			type = LIGHTTYPE_POINT;
		}

		PointLight::~PointLight(void)
		{
		}

		bool PointLight::Intersect(Intersection::Sphere &sphere)
		{
			return sphere.Intersection(ownerTransform->GetWorldPosition(), range);
		}

	}
}