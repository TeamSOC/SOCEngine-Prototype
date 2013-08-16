#include "Object.h"
#include "Math.h"

using namespace std;

namespace Rendering
{
	Object::Object(Object* parent /* = NULL */)
	{
		this->parent = parent;

		if(parent)
     		 root = parent->root;
		else root = this;

		forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		right	= D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		up		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		localPosition	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rotation		 = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
		localScale		 = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		localEulerAngles = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		vector<Object*>::iterator iter = childs.begin();

		for(iter; iter != childs.end(); ++iter)
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
		vector<Object*>::iterator iter = childs.begin();

		for(iter; iter != childs.end(); ++iter)
		{
			if((*iter) == child)
			{
				childs.erase(iter);
				return;
			}
		}
	}

	void Object::DeleteAllChilds()
	{
		childs.clear();
	}

	void Object::UpdateChild()
	{
		if(use == false)
			return;

		vector<Object*>::iterator iter = childs.begin();

		for(iter; iter != childs.end(); ++iter)
		{
			(*iter)->Update();
			(*iter)->Render();
		}
	}

	Object* Object::Copy(Object *obj)
	{
		Object *o = new Object();
		(*o) = (*obj);

		return o;
	}

	vector<Object*> Object::_FindChild(std::string str, FIND_ENUM e, bool one)
	{
		vector<Object*> v;
		vector<Object*>::iterator iter = childs.begin();

		for(iter; iter != childs.end(); ++iter)
		{
			string *findItem = e == FIND_ENUM_NAME ? &(*iter)->name : &(*iter)->tag;
			if( (*findItem) == str )
			{
				v.push_back((*iter));
				if(one) return v;
			}
		}
		//해쉬로 한다면 할수있겠지만, 굳이 그럴필요가 있나 싶어
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
		LookAt(target->position, D3DXVECTOR3(0, 1, 0));
	}

	void Object::LookAt(D3DXVECTOR3 worldPosition)
	{
		LookAt(worldPosition, D3DXVECTOR3(0, 1, 0));
	}

	void Object::LookAt(Object *target, D3DXVECTOR3 worldUp)
	{
		target->UpdateWorldTransform();
		LookAt(target->position, worldUp);
	}
	
	void Object::LookAt(D3DXVECTOR3 worldPosition, D3DXVECTOR3 worldUp)
	{
		UpdateWorldTransform();

		D3DXVECTOR3 dir = position - worldPosition;
		D3DXVec3Normalize(&dir, &dir);
		//그럼 이제, 이 dir과 월드 forward의 각이 얼마나 꺽였는지 알아내서 회전시키면 되.

		forward = dir;
		up = worldUp;

		D3DXVec3Cross(&right, &up, &forward);
		D3DXVec3Normalize(&right, &right);

		D3DXVec3Cross(&up, &forward, &right);
		//3축구함

		D3DXMATRIX rotationMatrix;

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

		D3DXQuaternionRotationMatrix(&rotation, &rotationMatrix); //쿼터니언 구함
		localEulerAngles = Math::Tool::QuaternionToEuler(rotation); // 오일러 구함
		UpdateMatrix();
	}

	void Object::Rotate(D3DXVECTOR3 eulerAngles)
	{
		D3DXVECTOR3 euler = this->localEulerAngles + eulerAngles;
		SetEulerAngles(euler);
	}

	void Object::Rotate(D3DXVECTOR3 axis, float angle)
	{
		D3DXQUATERNION q;
		D3DXQuaternionRotationAxis(&q, &axis, angle);

		D3DXVECTOR3 euler = Math::Tool::QuaternionToEuler(q);
		euler += this->localEulerAngles;

		SetEulerAngles(euler);
	}

	void Object::Rotate(float x, float y, float z)
	{
		D3DXVECTOR3 euler = localEulerAngles + D3DXVECTOR3(x, y, z);
		SetEulerAngles(euler);
	}

	void Object::Translate(D3DXVECTOR3 translation)
	{
		D3DXVECTOR3 p = localPosition + translation;
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

	void Object::GetMatrix(D3DXMATRIX *outMatrix)
	{
		*outMatrix = matrix;
	}

	void Object::GetWorldMatrix(D3DXMATRIX *outMatrix)
	{
		D3DXMATRIX mat;
		for(Object *o = this; o != NULL; o = o->parent)
			mat *= o->matrix;

		*outMatrix = mat;
	}

	void Object::SetPosition(D3DXVECTOR3 position)
	{
		this->localPosition = position;
		UpdateMatrix();
	}

	void Object::SetRotation(D3DXQUATERNION quaternion)
	{
		rotation = quaternion; //쿼터니언 구함

		D3DXMATRIX rotationMatrix;		
		D3DXMatrixRotationQuaternion(&rotationMatrix, &quaternion);

		right	= D3DXVECTOR3(rotationMatrix._11, rotationMatrix._21, rotationMatrix._31);
		up		= D3DXVECTOR3(rotationMatrix._12, rotationMatrix._22, rotationMatrix._32);
		forward = D3DXVECTOR3(rotationMatrix._13, rotationMatrix._23, rotationMatrix._33);
		//3축 구함

		localEulerAngles = Math::Tool::QuaternionToEuler(quaternion);

		//오일러 구함.
		UpdateMatrix();
	}

	void Object::SetScale(D3DXVECTOR3 scale)
	{
		this->localScale = scale;
		UpdateMatrix();
	}

	void Object::SetEulerAngles(D3DXVECTOR3 euler)
	{
		euler = Math::Tool::EulerNormalize(euler);
		localEulerAngles = euler; //오일러 구함.

		Yaw(euler.y);
		Pitch(euler.x);
		Roll(euler.z);

		D3DXVec3Normalize(&forward, &forward);

		D3DXVec3Cross(&up, &forward, &right);
		D3DXVec3Normalize(&up, &up);

		D3DXVec3Cross(&right, &up, &forward);
		D3DXVec3Normalize(&right, &right);
		//3축 구함.

		D3DXMATRIX rotationMatrix;

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

		D3DXQuaternionRotationMatrix(&rotation, &rotationMatrix); //쿼터니언 구함.
		UpdateMatrix();
	}

	void Object::UpdateWorldTransform()
	{
		D3DXVECTOR3 p(0, 0, 0), s(1, 1, 1), e(0, 0, 0);

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
		D3DXMatrixRotationQuaternion(&matrix, &rotation);

		matrix._11 *= localScale.x;
		matrix._22 *= localScale.y;
		matrix._33 *= localScale.z;

		D3DXVECTOR3 p = D3DXVECTOR3(-D3DXVec3Dot(&right, &localPosition),
									-D3DXVec3Dot(&up, &localPosition),
									-D3DXVec3Dot(&forward, &localPosition));

		matrix._41 = p.x;
		matrix._42 = p.y;
		matrix._43 = p.z;
		matrix._44 = 1.0f;
	}

	void Object::Roll(float angle)
	{
		D3DXMATRIX T;

		D3DXMatrixRotationAxis(&T, &forward, angle);
		D3DXVec3TransformCoord(&up, &up, &T);
		D3DXVec3TransformCoord(&right, &right, &T);
	}

	void Object::Yaw(float angle)
	{
		D3DXMATRIX T;

		D3DXMatrixRotationAxis(&T, &up, angle);
		D3DXVec3TransformCoord(&right, &right, &T);
		D3DXVec3TransformCoord(&forward, &forward, &T);
	}

	void Object::Pitch(float angle)
	{
		D3DXMATRIX T;

		D3DXMatrixRotationAxis(&T, &right, angle);
		D3DXVec3TransformCoord(&right, &right, &T);
		D3DXVec3TransformCoord(&forward, &forward, &T);
	}

	D3DXVECTOR3 Object::GetWorldPosition()
	{
		D3DXVECTOR3 p(0,0,0);

		for(Object *o = this; o != NULL; o = o->parent)
			p += o->localPosition;

		return p;
	}

	D3DXVECTOR3 Object::GetLocalPosition()
	{
		return localPosition;
	}

	void Object::Billboard(Object *camera, D3DXMATRIX *outMatrix)
	{
		//카메라 구현 이후에 작업.
		D3DXMATRIX mat;
		D3DXMatrixIdentity(&mat);

		D3DXMATRIX camWorldMat;
		camera->GetWorldMatrix(&camWorldMat);

		mat._11 = camWorldMat._11;
		mat._13 = camWorldMat._13;
		mat._31 = camWorldMat._31;
		mat._33 = camWorldMat._33;

		D3DXMatrixInverse(&mat, NULL, &mat);
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

	bool Object::Render()
	{
		//null
		return false;
	}
}

