#include "Transform.h"

namespace Rendering
{
	Transform::Transform(Transform *parent)
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

		for(Transform *o = this; o != NULL; o = o->parent)
		{
			position += o->localPosition;

			scale.x *= o->localScale.x;
			scale.y *= o->localScale.y;
			scale.z *= o->localScale.z;

			eulerAngles += localEulerAngles;
		}

		radius = 0.0f; // default
	}

	Transform::~Transform(void)
	{

	}

	void Transform::LookAt(SOC_Vector3 worldPosition)
	{
		UpdateWorldTransform();

		SOC_Vector3 dir = worldPosition - position;
		SOCVec3Normalize(&dir, &dir);
		forward = dir;

		float x, y, z;
		x = acos(D3DXVec2Dot(&SOC_Vector2(forward.x, forward.y), &SOC_Vector2(dir.x, dir.y)));	//xy 평면
		y = acos(D3DXVec2Dot(&SOC_Vector2(forward.x, forward.z), &SOC_Vector2(dir.x, dir.z)));	//xz 평면
		z = acos(D3DXVec2Dot(&SOC_Vector2(forward.y, forward.z), &SOC_Vector2(dir.y, dir.z)));	//yz 평면

		x = (int)Math::RadianToDegree(x);
		y = (int)Math::RadianToDegree(y);
		z = (int)Math::RadianToDegree(z);

		if( x == 0 && z == 0 )
		{
			SOCVec3Cross(&up, &forward, &right);
			SOCVec3Normalize(&up, &up);

			SOCVec3Cross(&right, &up, &forward);
			SOCVec3Normalize(&right, &right);
		}
		else
		{
			SOCVec3Cross(&right, &up, &forward);
			SOCVec3Normalize(&right, &right);

			SOCVec3Cross(&up, &forward, &right);
			SOCVec3Normalize(&up, &up);
		}

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

		SOCQuaternionRotationMatrix(&rotation, &rotationMatrix);

		//회전 순서?? 그거 문제인거 같은데,, 나중에 제대로 살펴보자
		if(x == 0 && z == 0)
		{
			localEulerAngles.x = Math::RadianToDegree(atan2(-rotationMatrix._31, rotationMatrix._11));
			localEulerAngles.y = Math::RadianToDegree(atan2(-rotationMatrix._23, rotationMatrix._22));
			localEulerAngles.z = Math::RadianToDegree(asin(rotationMatrix._21));
		}
		else
		{
			localEulerAngles.y = Math::RadianToDegree(atan2(-rotationMatrix._31, rotationMatrix._11));
			localEulerAngles.x = Math::RadianToDegree(atan2(-rotationMatrix._23, rotationMatrix._22));
			localEulerAngles.z = Math::RadianToDegree(asin(rotationMatrix._21));
		}

		localEulerAngles = Math::EulerNormalize(localEulerAngles);

		UpdateMatrix();
	}

	void Transform::LookAt(Transform *target)
	{
		target->UpdateWorldTransform();
		LookAt(target->position);
	}

	void Transform::Rotate(SOC_Vector3 eulerAngles)
	{
		SOC_Vector3 euler = this->localEulerAngles + eulerAngles;
		SetEulerAngles(euler);
	}

	void Transform::Rotate(float x, float y, float z)
	{
		SOC_Vector3 euler = localEulerAngles + SOC_Vector3(x, y, z);
		SetEulerAngles(euler);
	}

	void Transform::Translate(SOC_Vector3 translation)
	{
		SOC_Vector3 p = localPosition + translation;
		SetPosition(p);
	}

	void Transform::TranslateWithUpVec(float units)
	{
		localPosition += up * units;
	}

	void Transform::TranslateWithForwardVec(float units)
	{
		localPosition += forward * units;
	}

	void Transform::TranslateWithRightVec(float units)
	{
		localPosition += right * units;
	}

	void Transform::GetMatrix(SOC_Matrix *outMatrix)
	{
		*outMatrix = matrix;
	}

	void Transform::GetWorldMatrix(SOC_Matrix *outMatrix)
	{
		SOC_Matrix mat;
		SOCMatrixIdentity(&mat);

		UpdateMatrix();

		for(Transform *o = this; o != NULL; o = o->parent)
			SOCMatrixMultiply(&mat, &o->matrix, &mat);

		*outMatrix = mat;
	}

	void Transform::SetPosition(SOC_Vector3 position)
	{
		this->localPosition = position;
		UpdateMatrix();
	}

	void Transform::SetRotation(SOC_Quaternion quaternion)
	{
		rotation = quaternion; 

		SOC_Matrix rotationMatrix;
		SOCMatrixRotationQuaternion(&rotationMatrix, &quaternion);

		right	= SOC_Vector3(rotationMatrix._11, rotationMatrix._21, rotationMatrix._31);
		up		= SOC_Vector3(rotationMatrix._12, rotationMatrix._22, rotationMatrix._32);
		forward = SOC_Vector3(rotationMatrix._13, rotationMatrix._23, rotationMatrix._33);

		Math::RadianToDegree(&localEulerAngles, &Math::QuaternionToEuler(rotation));

		UpdateMatrix();
	}

	void Transform::SetScale(SOC_Vector3 scale)
	{
		this->localScale = scale;
		UpdateMatrix();
	}

	void Transform::SetEulerAngles(SOC_Vector3 euler)
	{
		euler = Math::EulerNormalize(euler);
		localEulerAngles = euler; 

		SOC_Vector3 re;
		re.x = Math::DegreeToRadian(euler.x);
		re.y = Math::DegreeToRadian(euler.y);
		re.z = Math::DegreeToRadian(euler.z);

		SOC_Matrix rotationMatrix;
		D3DXQuaternionRotationYawPitchRoll(&rotation, re.y, re.x, re.z);
		D3DXMatrixRotationQuaternion(&rotationMatrix, &rotation);

		right = SOC_Vector3(rotationMatrix._11, rotationMatrix._21, rotationMatrix._31);
		up = SOC_Vector3(rotationMatrix._12, rotationMatrix._22, rotationMatrix._32);
		forward = SOC_Vector3(rotationMatrix._13, rotationMatrix._23, rotationMatrix._33);

		UpdateMatrix();
	}

	void Transform::SetDirection(SOC_Vector3 dir)
	{
		SOC_Vector3 p = GetWorldPosition() + dir;
		LookAt(p);
	}

	void Transform::UpdateWorldTransform()
	{
		SOC_Vector3 p(0, 0, 0), s(1, 1, 1), e(0, 0, 0);

		for(Transform *o = this; o != NULL; o = o->parent)
		{
			p += o->localPosition;

			s.x *= o->localScale.x;
			s.y *= o->localScale.y;
			s.z *= o->localScale.z;

			e += localEulerAngles;
		}

		eulerAngles = Math::EulerNormalize(e);
		position = p;
		scale = s;
	}

	void Transform::UpdateMatrix()
	{
		SOCMatrixRotationQuaternion(&matrix, &rotation);

		matrix._11 *= localScale.x;
		matrix._22 *= localScale.y;
		matrix._33 *= localScale.z;

		matrix._41 = localPosition.x;
		matrix._42 = localPosition.y;
		matrix._43 = localPosition.z;
		matrix._44 = 1.0f;

		//SOC_Vector3 p = SOC_Vector3(
		//	-SOCVec3Dot(&right, &localPosition),
		//	-SOCVec3Dot(&up, &localPosition),
		//	-SOCVec3Dot(&forward, &localPosition));

		//matrix._41 = p.x;
		//matrix._42 = p.y;
		//matrix._43 = p.z;
		//matrix._44 = 1.0f;
	}

	SOC_Vector3 Transform::GetWorldPosition()
	{
		SOC_Vector3 p(0,0,0);

		for(Transform *o = this; o != NULL; o = o->parent)
			p += o->localPosition;

		return p;
	}

	SOC_Vector3 Transform::GetLocalPosition()
	{
		return localPosition;
	}

	void Transform::Billboard(SOC_Matrix *camWorldMat, SOC_Matrix *outMatrix)
	{
		SOC_Matrix mat = *camWorldMat;

		mat._11 = camWorldMat->_11;
		mat._13 = camWorldMat->_13;
		mat._31 = camWorldMat->_31;
		mat._33 = camWorldMat->_33;

		SOCMatrixInverse(&mat, NULL, &mat);
		*outMatrix = mat;
	}

	float Transform::CalcRadius(Transform *child)
	{
		float distance = SOCVec3Length(&(GetWorldPosition() - child->GetWorldPosition()));
		float totalR = distance + child->radius;

		this->radius = totalR > radius ? totalR : radius;

		return radius;
	}

	SOC_Vector3 Transform::GetForward()
	{
		return forward;
	}

	SOC_Vector3 Transform::GetLocalEulerAngle()
	{
		return this->localEulerAngles;
	}

	SOC_Vector3 Transform::GetWorldEulerAngle()
	{
		SOC_Vector3 p(0,0,0);

		for(Transform *o = this; o != NULL; o = o->parent)
			p += o->localEulerAngles;

		return p;
	}

	SOC_Vector3 Transform::GetLocalScale()
	{
		return this->localScale;
	}

	SOC_Vector3 Transform::GetWorldScale()
	{
		SOC_Vector3 p(1,1,1);

		for(Transform *o = this; o != NULL; o = o->parent)
		{
			p.x *= o->localScale.x;
			p.y *= o->localScale.y;
			p.z *= o->localScale.z;
		}

		return p;
	}

	SOC_Quaternion Transform::GetRotation()
	{
		return this->rotation;
	}

	SOC_Vector3 Transform::GetRight()
	{
		return right;
	}

	SOC_Vector3 Transform::GetUp()
	{
		return up;
	}

	float Transform::GetRadius()
	{
		return radius;
	}

	void Transform::SetRadius(float radius)
	{
		this->radius = radius;
	}

	void Transform::SetBound(Intersection::AABB &bound)
	{
		this->bound = bound;
	}

	Intersection::AABB Transform::GetBound()
	{
		return this->bound;
	}
}