#pragma once

#include "LightForm.h"

namespace Rendering
{
	namespace Light
	{
		class DirectionalLight : public LightForm
		{
		public:
			DirectionalLight();
			~DirectionalLight();

		public:
			virtual bool Intersect(Intersection::Sphere &sphere);
		};

	}
}