#pragma once

#include "Object.h"

namespace Rendering
{
	namespace Light
	{
#define MAX_LIGHT 8

		class LightForm : public Object
		{
		public:
			enum TYPE{ LIGHTTYPE_DIRECTIONAL = 0, LIGHTTYPE_POINT, LIGHTTYPE_SPOT };
			TYPE type;
		protected:
			Color diffuse;
			Color specular;

			bool onSpecular;

			float range;
			float specularPower;

		protected:
			LightForm(Object *parent = NULL);

		//public:
		//	virtual bool Intersect(Intersection::Sphere &sphere) = 0;
		//Move Object
		};
	}
}