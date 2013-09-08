#pragma once

#include "LightForm.h"

namespace Rendering
{
	namespace Light
	{
		class SpotLight : public LightForm
		{
		public:
			SpotLight(Object *parent = NULL);

		public:
			bool Intersect(SOC_Vector3 worldPos, float radius);
		};

	}
}
