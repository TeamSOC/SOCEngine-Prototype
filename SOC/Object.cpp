#include "Object.h"
#include "Math.h"
#include "Utility.h"

using namespace std;
using namespace Intersection;

namespace Rendering
{
	Object::Object(Object* parent /* = NULL */)
	{
		this->parent = parent;

		if(parent)
			root = parent->root;
		else root = this;

		forward = SOC_Vector3(0.0f, 0.0f, 1.0f);
		right	= SOC_Vector3(1.0f, 0.0f, 0.0f);
		up		= SOC_Vector3(0.0f, 1.0f, 0.0f);

		localPosition	 = SOC_Vector3(0.0f, 0.0f, 0.0f);
		rotation		 = SOC_Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
		localScale		 = SOC_Vector3(1.0f, 1.0f, 1.0f);
		localEulerAngles = SOC_Vector3(0.0f, 0.0f, 0.0f);

		for(Object *o = this; o != NULL; o = o->parent)
		{
			position += o->localPosition;

			scale.x *= o->localScale.x;
			scale.y *= o->localScale.y;
			scale.z *= o->localScale.z;

			eulerAngles += localEulerAngles;
		}

		radius = 50.0f; // default
		isLight = false;
		culled = false;
	}

	Object::~Object(void)
	{
	}

	Object* Object::AddObject(Object *child, int renderQueue, bool copy/* = false */)
	{
		Object *c =  Container::AddObject(child, renderQueue, copy);
		radius = Object::CalcRadius(this, c);

		return c;
	}

	Object* Object::AddObject(Object *child, bool copy/* = false */)
	{
		Object *c =  Container::AddObject(child, copy);
		radius = Object::CalcRadius(this, c);

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

	void Object::LookAt(Object *target)
	{
		target->UpdateWorldTransform();
		LookAt(target->position, SOC_Vector3(0, 1, 0));
	}

	void Object::LookAt(SOC_Vector3 worldPosition)
	{
		LookAt(worldPosition, SOC_Vector3(0, 1, 0));
	}

	void Object::LookAt(Object *target, SOC_Vector3 worldUp)
	{
		target->UpdateWorldTransform();
		LookAt(target->position, worldUp);
	}

	void Object::LookAt(SOC_Vector3 worldPosition, SOC_Vector3 worldUp)
	{
		UpdateWorldTransform();

		SOC_Vector3 dir = worldPosition - position;
		SOCVec3Normalize(&dir, &dir);
		forward = dir;
		up = worldUp;

		SOCVec3Cross(&right, &up, &forward);
		SOCVec3Normalize(&right, &right);

		SOCVec3Cross(&up, &forward, &right);

		SOC_Matrix rotationMatrix;

		rotationMatrix._11 = right.x;
		rotationMatrix._12 = up.x;
		rotationMatrix._13 = forward.x;
		rotationMatrix._14 = 0;

		rotationMatrix._21 = right.y;
		rotationMatrix._22 = up.y;
		rotationMatrix._23 = forward.y;
		rotationMatrix._24 = 0;

		rotationMatrix._31 = right.z;
		rotationMatrix._32 = up.z;
		rotationMatrix._33 = forward.z;
		rotationMatrix._34 = 0;

		rotationMatrix._41 = 0;
		rotationMatrix._42 = 0;
		rotationMatrix._43 = 0;
		rotationMatrix._44 = 1.0f;

		SOCQuaternionRotationMatrix(&rotation, &rotationMatrix); //ƒı≈Õ¥œæ ±∏«‘
		localEulerAngles = SOCQuaternionToEuler(rotation); // ø¿¿œ∑Ø ±∏«‘
		UpdateMatrix();
		
	}

	void Object::Rotate(SOC_Vector3 eulerAngles)
	{
		SOC_Vector3 euler = this->localEulerAngles + eulerAngles;
		SetEulerAngles(euler);
	}

	void Object::Rotate(SOC_Vector3 axis, float angle)
	{
		SOC_Quaternion q;
		SOCQuaternionRotationAxis(&q, &axis, angle);

		SOC_Vector3 euler = SOCQuaternionToEuler(q);
		euler += this->localEulerAngles;

		SetEulerAngles(euler);
	}

	void Object::Rotate(float x, float y, float z)
	{
		SOC_Vector3 euler = localEulerAngles + SOC_Vector3(x, y, z);
		SetEulerAngles(euler);
	}

	void Object::Translate(SOC_Vector3 translation)
	{
		SOC_Vector3 p = localPosition + translation;
		SetPosition(p);
	}

	void Object::TranslateWithUpVec(float units)
	{
		localPosition += up * units;
	}

	void Object::TranslateWithForwardVec(float units)
	{
		localPosition += forward * units;
	}

	void Object::TranslateWithRightVec(float units)
	{
		localPosition += right * units;
	}

	void Object::GetMatrix(SOC_Matrix *outMatrix)
	{
		*outMatrix = matrix;
	}

	void Object::GetWorldMatrix(SOC_Matrix *outMatrix)
	{
		SOC_Matrix mat;

		SOCMatrixIdentity(&mat);

		for(Object *o = this; o != NULL; o = o->parent)
			mat *= o->matrix;

		*outMatrix = mat;
	}

	void Object::SetPosition(SOC_Vector3 position)
	{
		this->localPosition = position;
		UpdateMatrix();
	}

	void Object::SetRotation(SOC_Quaternion quaternion)
	{
		rotation = quaternion; //ƒı≈Õ¥œæ ±∏«‘

		SOC_Matrix rotationMatrix;
		SOCMatrixRotationQuaternion(&rotationMatrix, &quaternion);

		right	= SOC_Vector3(rotationMatrix._11, rotationMatrix._21, rotationMatrix._31);
		up		= SOC_Vector3(rotationMatrix._12, rotationMatrix._22, rotationMatrix._32);
		forward = SOC_Vector3(rotationMatrix._13, rotationMatrix._23, rotationMatrix._33);
		//3√‡ ±∏«‘

		localEulerAngles = SOCQuaternionToEuler(quaternion);

		//ø¿¿œ∑Ø ±∏«‘.
		UpdateMatrix();
	}

	void Object::SetScale(SOC_Vector3 scale)
	{
		this->localScale = scale;
		UpdateMatrix();
	}

	void Object::SetEulerAngles(SOC_Vector3 euler)
	{
		euler = SOCEulerNormalize(euler);
		localEulerAngles = euler; //ø¿¿œ∑Ø ±∏«‘.

		Yaw(euler.y);
		Pitch(euler.x);
		Roll(euler.z);

		SOCVec3Normalize(&forward, &forward);

		SOCVec3Cross(&up, &forward, &right);
		SOCVec3Normalize(&up, &up);

		SOCVec3Cross(&right, &up, &forward);
		SOCVec3Normalize(&right, &right);
		//3√‡ ±∏«‘.

		SOC_Matrix rotationMatrix;

		rotationMatrix._11 = right.x;
		rotationMatrix._12 = up.x;
		rotationMatrix._13 = forward.x;
		rotationMatrix._14 = 0;

		rotationMatrix._21 = right.y;
		rotationMatrix._22 = up.y;
		rotationMatrix._23 = forward.y;
		rotationMatrix._24 = 0;

		rotationMatrix._31 = right.z;
		rotationMatrix._32 = up.z;
		rotationMatrix._33 = forward.z;
		rotationMatrix._34 = 0;

		SOCQuaternionRotationMatrix(&rotation, &rotationMatrix); //ƒı≈Õ¥œæ ±∏«‘.
		UpdateMatrix();
	}

	void Object::SetDirection(SOC_Vector3 dir)
	{
		SOC_Vector3 p = GetWorldPosition() + dir;
		LookAt(p);
	}

	void Object::UpdateWorldTransform()
	{
		SOC_Vector3 p(0, 0, 0), s(1, 1, 1), e(0, 0, 0);

		for(Object *o = this; o != NULL; o = o->parent)
		{
			p += o->localPosition;

			s.x *= o->localScale.x;
			s.y *= o->localScale.y;
			s.z *= o->localScale.z;

			e += localEulerAngles;
		}

		eulerAngles = SOCEulerNormalize(e);
		position = p;
		scale = s;
	}

	void Object::UpdateMatrix()
	{
		SOCMatrixRotationQuaternion(&matrix, &rotation);

		matrix._11 *= localScale.x;
		matrix._22 *= localScale.y;
		matrix._33 *= localScale.z;

		SOC_Vector3 p = SOC_Vector3(-SOCVec3Dot(&right, &localPosition),
			-SOCVec3Dot(&up, &localPosition),
			-SOCVec3Dot(&forward, &localPosition));

		matrix._41 = p.x;
		matrix._42 = p.y;
		matrix._43 = p.z;
		matrix._44 = 1.0f;
	}

	void Object::Roll(float angle)
	{
		SOC_Matrix T;

		SOCMatrixRotationAxis(&T, &forward, angle);
		SOCVec3TransformCoord(&up, &up, &T);
		SOCVec3TransformCoord(&right, &right, &T);
	}

	void Object::Yaw(float angle)
	{
		SOC_Matrix T;

		SOCMatrixRotationAxis(&T, &up, angle);
		SOCVec3TransformCoord(&right, &right, &T);
		SOCVec3TransformCoord(&forward, &forward, &T);
	}

	void Object::Pitch(float angle)
	{
		SOC_Matrix T;

		SOCMatrixRotationAxis(&T, &right, angle);
		SOCVec3TransformCoord(&right, &right, &T);
		SOCVec3TransformCoord(&forward, &forward, &T);
	}

	SOC_Vector3 Object::GetWorldPosition()
	{
		SOC_Vector3 p(0,0,0);

		for(Object *o = this; o != NULL; o = o->parent)
			p += o->localPosition;

		return p;
	}

	SOC_Vector3 Object::GetLocalPosition()
	{
		return localPosition;
	}

	void Object::Billboard(SOC_Matrix *camWorldMat, SOC_Matrix *outMatrix)
	{
		SOC_Matrix mat = *camWorldMat;

		mat._11 = camWorldMat->_11;
		mat._13 = camWorldMat->_13;
		mat._31 = camWorldMat->_31;
		mat._33 = camWorldMat->_33;

		SOCMatrixInverse(&mat, NULL, &mat);
		*outMatrix = mat;
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
		culled = frustum->In(GetWorldPosition(), radius);

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

	bool Object::Update(float delta)
	{
		//null
		return false;
	}

	void Object::Render(std::vector<Object*> *lights, SOC_Matrix *viewMat, SOC_Matrix *projMat, SOC_Vector3 dir)
	{
		if(culled)	return;

		Sphere thisObject(GetWorldPosition(), radius);
		std::vector<Object*> intersectLights;

		for(std::vector<Object*>::iterator iter = lights->begin(); iter != lights->end(); ++iter)
		{
			if((*iter)->Intersect(thisObject))
				intersectLights.push_back((*iter));
		}

		_Render(&intersectLights, viewMat, projMat, dir);
	}

	bool Object::Intersect(Intersection::Sphere &sphere)
	{
		return sphere.Intersection(GetWorldPosition(), radius);
	}

	void Object::_Render(std::vector<Object*> *lights, SOC_Matrix *viewMat, SOC_Matrix *projMat, SOC_Vector3 &dir)
	{
		//null
	}

	float Object::GetRadius()
	{
		return radius; 
	}

	bool Object::IsLight()
	{
		return isLight;
	}

	float Object::CalcRadius(Object *parent, Object *child)
	{
		float distance = SOCVec3Length(&(parent->GetWorldPosition() - child->GetWorldPosition()));
		float totalR = distance + child->radius;

		return totalR > parent->radius ? totalR : parent->radius;
	}

	Object* Object::Copy(Object *obj)
	{
		return new Object(*obj);
	}
}

