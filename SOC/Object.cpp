#include "Object.h"
#include "Math.h"
#include "Utility.h"

using namespace std;

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
	}

	Object::~Object(void)
	{
	}

	void Object::AddChild(Object *child, int renderQueue, bool copy/* = false */)
	{
		if(renderQueue < 0)
			return;

		Object *c = copy == false ? child : Object::Copy(this);

		vector<Object*>::iterator iter;

		for(iter = childs.begin(); iter != childs.end(); ++iter)
		{
			if( (*iter)->renderQueue <= renderQueue )
			{
				c->renderQueue = (*iter)->renderQueue == renderQueue ? renderQueue + 1 : renderQueue;
				childs.insert(iter + 1, c);
				return;
			}
		}
	}

	void Object::AddChild(Object *child, bool copy/* = false */)
	{
		Object *c = copy == false ? child : Object::Copy(this);

		c->renderQueue = (*(childs.end() - 1))->renderQueue + 1;
		c->parent = this;
		childs.push_back(c);

	}

	void Object::DeleteChild(Object *child)
	{
		vector<Object*>::iterator iter;

		for(iter = childs.begin(); iter != childs.end(); ++iter)
		{
			if((*iter) == child)
			{
				Utility::SAFE_DELETE(*iter);
				childs.erase(iter);
				return;
			}
		}
	}

	void Object::DeleteAllChilds()
	{
		for(vector<Object*>::iterator iter = childs.begin(); iter != childs.end(); ++iter)
			Utility::SAFE_DELETE(*iter);
	
		childs.clear();
	}

	void Object::UpdateChild()
	{
		if(use == false)
			return;

		vector<Object*>::iterator iter;

		for(iter = childs.begin(); iter != childs.end(); ++iter)
			(*iter)->Update();
	}

	Object* Object::Copy(Object *obj)
	{
		Object *o = new Object(NULL);
		(*o) = (*obj);

		return o;
	}

	vector<Object*> Object::_FindChild(std::string str, FIND_ENUM e, bool one)
	{
		vector<Object*> v;
		vector<Object*>::iterator iter;

		for(iter = childs.begin(); iter != childs.end(); ++iter)
		{
			string *findItem = e == FIND_ENUM_NAME ? &(*iter)->name : &(*iter)->tag;
			if( (*findItem) == str )
			{
				v.push_back((*iter));
				if(one) return v;
			}
		}
		return v;
	}

	vector<Object*> Object::FindChilds(string name)
	{
		return _FindChild(name, FIND_ENUM_NAME, false);
	}

	vector<Object*> Object::FindChildsWithTag(string tag)
	{
		return _FindChild(name, FIND_ENUM_TAG, false);
	}

	Object* Object::FindChild(string name)
	{
		vector<Object*> v = _FindChild(name, FIND_ENUM_NAME, true);
		return v.size() == 0 ? NULL : v[0];
	}
	
	Object* Object::FindChildWithTag(string tag)
	{
		vector<Object*> v = _FindChild(tag, FIND_ENUM_TAG, true);
		return v.size() == 0 ? NULL : v[0];
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

		SOC_Vector3 dir = position - worldPosition;
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
		localEulerAngles = Math::Tool::QuaternionToEuler(rotation); // ø¿¿œ∑Ø ±∏«‘
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

		SOC_Vector3 euler = Math::Tool::QuaternionToEuler(q);
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

		localEulerAngles = Math::Tool::QuaternionToEuler(quaternion);

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
		euler = Math::Tool::EulerNormalize(euler);
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

		eulerAngles = Math::Tool::EulerNormalize(e);
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

	void Object::Billboard(Object *camera, SOC_Matrix *outMatrix)
	{
		//ƒ´∏ﬁ∂Û ±∏«ˆ ¿Ã»ƒø° ¿€æ˜.
		SOC_Matrix mat;
		SOCMatrixIdentity(&mat);

		SOC_Matrix camWorldMat;
		camera->GetWorldMatrix(&camWorldMat);

		mat._11 = camWorldMat._11;
		mat._13 = camWorldMat._13;
		mat._31 = camWorldMat._31;
		mat._33 = camWorldMat._33;

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


	bool Object::GetUse()
	{
		return use;
	}

	bool Object::Update()
	{
		//null
		return false;
	}

	bool Object::Render(std::vector<Object*> *lights)
	{
		//null
		return false;
	}
}

