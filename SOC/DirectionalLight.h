#pragma once

#include "LightForm.h"

namespace Rendering
{
	namespace Light
	{
		class DirectionalLight : public LightForm
		{
		public:
			DirectionalLight(Object *parent = NULL);
			~DirectionalLight(void);

		public:
			bool Intersect(SOC_Vector3 worldPos, float radius);
		};

	}
}