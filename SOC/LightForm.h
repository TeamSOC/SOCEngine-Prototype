#pragma once

#include "RenderingMath.h"
#include "Sphere.h"
#include "Component.h"



namespace Rendering
{
	namespace Light
	{
		class LightForm : public Component
		{
		public:
			static const Component::Type ComponentType = Component::Type::Light;

		public:
			enum LightType{ DIRECTIONAL = 0, POINT, SPOT };

		protected:
			LightType type;
		
		public:
			Color ambient;
			Color diffuse;
			Color specular;
		
			float range;
			float specularPower;

		protected:
			LightForm();

		public:
			virtual bool Intersect(Intersection::Sphere &sphere) = 0;
			SOC_Vector3& GetWorldPosition();
			SOC_Vector3& GetDirection();

		public:
			virtual void Initialize();
			virtual void Destroy();
			LightType GetType();
		};
	}
}