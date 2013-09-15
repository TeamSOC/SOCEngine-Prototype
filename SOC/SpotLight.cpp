#include "SpotLight.h"

using namespace Intersection;

namespace Rendering
{
	namespace Light
	{
		SpotLight::SpotLight(Object *parent)  : LightForm(parent)
		{
			type = LIGHTTYPE_SPOT;
			spotAngle = 1.0f;
		}

		bool SpotLight::Intersect(Intersection::Sphere &sphere)
		{
			float angle = spotAngle;

			if(angle < 1)				angle = 1;
			else if(angle > 179)		angle = 179;

			Cone cone(angle, range, forward, GetWorldPosition());

			return cone.Intersection(sphere);
		}
	}
}