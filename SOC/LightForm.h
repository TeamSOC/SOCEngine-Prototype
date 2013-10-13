#pragma once

#include "RenderingMath.h"
#include "Sphere.h"
#include "Component.h"

namespace Rendering
{
	namespace Light
	{
#define MAX_LIGHT 8

		class LightForm : public Component
		{
		public:
			static const Component::Type ComponentType = Component::Type::Light;

		public:
			enum LightType{ LIGHTTYPE_DIRECTIONAL = 0, LIGHTTYPE_POINT, LIGHTTYPE_SPOT };
			LightType type;
		
		public:
			Color diffuseColor;
			Color specularColor;
		
			float range;
			float specularPower;

		protected:
			LightForm();

		public:
			virtual bool Intersect(Intersection::Sphere &sphere) = 0;
			SOC_Vector3& GetWorldPosition();
			SOC_Vector3& GetDirection();
//			virtual Component::Type GetComponentType();
		};
	}
}