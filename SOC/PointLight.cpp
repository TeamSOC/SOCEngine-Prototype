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

		bool PointLight::Intersect(SOC_Vector3 worldPos, float radius)
		{
			return Intersection::Sphere::Intersection(worldPos, radius, this->GetWorldPosition(), this->radius);
		}
	}
}