#include "Object.h"
#include "Math.h"
#include "Utility.h"

using namespace std;
using namespace Intersection;

namespace Rendering
{
	using namespace Light;

	Object::Object(Object* parent /* = NULL */) : Container()
	{
		culled = false;
		transform = new Transform( parent ? parent->transform : nullptr);
	}

	Object::~Object(void)
	{
		if(transform)
			delete transform;

		DeleteAllObjects(true);
		DeleteAllComponent();
	}

	Object* Object::AddObject(Object *child, int renderQueue, bool copy/* = false */)
	{
		Object *c =  Container::AddObject(child, renderQueue, copy);
		transform->CalcRadius(c->transform);

		return c;
	}

	Object* Object::AddObject(Object *child, bool copy/* = false */)
	{
		Object *c =  Container::AddObject(child, copy);
		transform->CalcRadius(c->transform);

		return c;
	}

	void Object::UpdateChild(float delta)
	{
		if(use == false)
			return;

		vector<Object*>::iterator iter;

		for(iter = objects.begin(); iter != objects.end(); ++iter)
			(*iter)->Update(delta);
	}

	void Object::SetUse(bool is)
	{
		use = is;
	}

	bool Object::IsChildOf(Object *parent)
	{
		return (parent == this->parent); 
	}

	bool Object::Culling(Frustum *frustum)
	{
		culled = frustum->In(transform->GetWorldPosition(), transform->GetRadius());

		if(culled == false)
		{
			for(vector<Object*>::iterator iter = objects.begin(); iter != objects.end(); ++iter)
				(*iter)->Culling(frustum);
		}

		return culled;
	}

	bool Object::GetUse()
	{
		return use;
	}

	bool Object::Culled()
	{
		return culled;
	}

	void Object::Update(float delta)
	{
		for(std::vector<Component*>::iterator iter = componenets.begin(); iter != componenets.end(); ++iter)
			(*iter)->Update(delta);
	}

	void Object::Render(std::vector<LightForm*> *lights, SOC_Matrix *viewMat, SOC_Matrix *projMat, SOC_Matrix *viewProjMat)
	{
		if(culled)	return;

		Sphere thisObject(transform->GetWorldPosition(), transform->GetRadius());
		std::vector<LightForm*> intersectLights;

		for(std::vector<LightForm*>::iterator iter = lights->begin(); iter != lights->end(); ++iter)
		{
			if((*iter)->Intersect(thisObject))
				intersectLights.push_back((*iter));
		}

		SOC_Matrix worldMat, worldViewProjMat;

		transform->GetWorldMatrix(&worldMat);
		worldViewProjMat = worldMat;
		worldViewProjMat *= (*viewProjMat);

		TransformParameters tp(&worldMat, viewMat, projMat, viewProjMat, &worldViewProjMat);
		LightParameters lp;

		SOC_Vector4 diffuseColorAry[MAX_LIGHT], specularColorAry[MAX_LIGHT];
		float rangeAry[MAX_LIGHT], specularPowerAry[MAX_LIGHT];
		SOC_Vector4 lightPosAry[MAX_LIGHT], lightDirAry[MAX_LIGHT];
		float spotAngleAry[MAX_LIGHT];
		int typeAry[MAX_LIGHT];

		int intersectLightCount = intersectLights.size();
		lp.count = intersectLightCount > MAX_LIGHT ? MAX_LIGHT : intersectLightCount;

		for(int i=0; i < lp.count; ++i)
		{
			LightForm *light = intersectLights[i];
			diffuseColorAry[i]  = light->diffuseColor.GetVector();
			specularColorAry[i] = light->specularColor.GetVector();
			rangeAry[i] = light->range;
			specularPowerAry[i] = light->specularPower;
			lightPosAry[i] = SOC_Vector4(light->GetWorldPosition(), 1.0f);
			lightDirAry[i] = SOC_Vector4(light->GetDirection(), 1.0f);
			typeAry[i] = (int)light->type;
			spotAngleAry[i] = light->type == LightForm::LIGHTTYPE_SPOT ? static_cast<SpotLight*>(light)->spotAngle : 1.0f;		
		}

		lp.viewPos = SOC_Vector4(viewMat->_41, viewMat->_42, viewMat->_43, 1.0f);

		for(std::vector<Component*>::iterator iter = componenets.begin(); iter != componenets.end(); ++iter)
			(*iter)->Render(&tp, &lp);
	}

	bool Object::Intersect(Intersection::Sphere &sphere)
	{
		return sphere.Intersection(transform->GetWorldPosition(), transform->GetRadius());
	}

	//void Object::_Render(std::vector<LightForm*> *lights, SOC_Matrix *viewMat, SOC_Matrix *projMat, SOC_Matrix *viewProjMat)
	//{
	//	//null
	//}

	void Object::DeleteComponent(Component *component)
	{
		for(std::vector<Component*>::iterator iter = componenets.begin(); iter != componenets.end(); ++iter)
		{
			if((*iter) == component)
			{
				(*iter)->Destroy();
				componenets.erase(iter);
				delete (*iter);
				return;
			}
		}

	}

	Object* Object::Copy(Object *obj)
	{
		return new Object(*obj);
	}

	Transform* Object::GetTransform()
	{
		return transform;
	}

	void Object::DeleteAllComponent()
	{
		for(std::vector<Component*>::iterator iter = componenets.begin(); iter != componenets.end(); ++iter)
			delete (*iter);

		componenets.clear();
	}
}

#include "Object.hpp"