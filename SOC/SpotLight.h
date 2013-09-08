#pragma once

#include "LightForm.h"
#include "Cone.h"

namespace Rendering
{
	namespace Light
	{
		class SpotLight : public LightForm
		{
		public:
			float angle;

		public:
			SpotLight(Object *parent = NULL);

		public:
			bool Intersect(SOC_Vector3 worldPos, float radius);
		};

	}
}
