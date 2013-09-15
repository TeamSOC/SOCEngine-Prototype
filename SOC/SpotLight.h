#pragma once

#include "LightForm.h"
#include "Cone.h"

namespace Rendering
{
	namespace Light
	{
		class SpotLight : public LightForm
		{
		private:
			float spotAngle;

		public:
			SpotLight(Object *parent = NULL);

		public:
			bool Intersect(Intersection::Sphere &sphere);
		};

	}
}
