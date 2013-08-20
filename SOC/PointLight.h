#pragma once

#include "LightForm.h"
#include "Sphere.h"

namespace Rendering
{
	namespace Light
	{

		class PointLight : public LightForm
		{
		public:
			PointLight(Object *parent = NULL) : LightForm(parent)
			{
				type = LIGHTTYPE_POINT;
			}

			~PointLight(void)
			{
			}

		public:
			bool Intersect(SOC_Vector3 worldPos, float radius)
			{
				return Intersection::Sphere::Intersection(worldPos, radius, this->GetWorldPosition(), this->radius);
			}
		};

	}
}