#pragma once

//#include <stdarg.h>
#include <vector>
#include <string>

#include "Platform.h"
#include "Sphere.h"

#include "Container.h"
#include "Frustum.h"
#include "Transform.h"

#include "Mesh.h"
#include "Light.h"
#include "Camera.h"

namespace Rendering
{
	class Object : public Container<Object>
	{
	protected:
		bool use;
		bool culled;

	protected:
		Object *parent;
		Object *root;
		Transform *transform;

	protected:
		std::vector<Component*> componenets;

	public:
		Object(Object* parent = NULL);
		virtual ~Object(void);

	public:
		void Update(float delta);
		void Render(std::vector<Light::LightForm*> *lights, SOC_Matrix *viewMat, SOC_Matrix *projMat, SOC_Matrix *viewProjMat);

		virtual bool Intersect(Intersection::Sphere &sphere);

	public:
		Object* AddObject(Object *child, bool copy = false);
		Object* AddObject(Object *child, int renderQueueOrder, bool copy = false);

		template<class ComponentType>
		ComponentType* AddComponent();

		template<class ComponentType>
		ComponentType* GetComponent();

		template<class ComponentType>
		std::vector<ComponentType*> GetComponents();

		void DeleteComponent(Component *component);
		void DeleteAllComponent();

		bool Culling(Frustum *frustum);
		bool IsChildOf(Object *parent);

		void SetUse(bool is);
		bool GetUse();
		bool Culled();

	public:
		void UpdateChild(float delta);

	public:
		static Object* Copy(Object *obj);
		Transform *GetTransform();
	};

}