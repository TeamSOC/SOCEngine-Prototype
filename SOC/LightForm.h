#pragma once

#include "Object.h"
#include "Color.h"

namespace Rendering
{
	namespace Light
	{
		class LightForm : public Object
		{
		public:
			enum TYPE{ LIGHTTYPE_DIRECTIONAL, LIGHTTYPE_POINT, LIGHTTYPE_SPOT };
			TYPE type;

		protected:
			Color diffuse;
			Color specular;

			bool onSpecular;

			float range;
			float intensity;
			float specularPower;

		protected:
			LightForm(Object *parent = NULL) : Object(parent)
			{
				diffuse		= Color::white();
				specular	= Color::white();

				onSpecular = true;

				range = 0.0f;
				intensity = 1.0f;
				specularPower = 20.0f;

				isLight = true;
			}

		public:
			virtual bool Intersect(SOC_Vector3 worldPos, float radius) = 0;
		};
	}
}