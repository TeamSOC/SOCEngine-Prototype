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

	void Transform::LookAt(Transform *target)
	{
		target->UpdateWorldTransform();
		LookAt(target->position, SOC_Vector3(0, 1, 0));
	}

	void Transform::LookAt(SOC_Vector3 worldPosition)
	{
		LookAt(worldPosition, SOC_Vector3(0, 1, 0));
	}

	void Transform::LookAt(Transform *target, SOC_Vector3 worldUp)
	{
		target->UpdateWorldTransform();
		LookAt(target->position, worldUp);
	}

	void Transform::LookAt(SOC_Vector3 worldPosition, SOC_Vector3 worldUp)
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

		SOCQuaternionRotationMatrix(&rotation, &rotationMatrix);
		localEulerAngles = SOCQuaternionToEuler(rotation);
		UpdateMatrix();

	}

	void Transform::Rotate(SOC_Vector3 eulerAngles)
	{
		SOC_Vector3 euler = this->localEulerAngles + eulerAngles;
		SetEulerAngles(euler);
	}

	void Transform::Rotate(SOC_Vector3 axis, float angle)
	{
		SOC_Quaternion q;
		SOCQuaternionRotationAxis(&q, &axis, angle);

		SOC_Vector3 euler = SOCQuaternionToEuler(q);
		euler += this->localEulerAngles;

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

		for(Transform *o = this; o != NULL; o = o->parent)
			mat *= o->matrix;

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

		localEulerAngles = SOCQuaternionToEuler(quaternion);

		UpdateMatrix();
	}

	void Transform::SetScale(SOC_Vector3 scale)
	{
		this->localScale = scale;
		UpdateMatrix();
	}

	void Transform::SetEulerAngles(SOC_Vector3 euler)
	{
		euler = SOCEulerNormalize(euler);
		localEulerAngles = euler; 

		Yaw(euler.y);
		Pitch(euler.x);
		Roll(euler.z);

		SOCVec3Normalize(&forward, &forward);

		SOCVec3Cross(&up, &forward, &right);
		SOCVec3Normalize(&up, &up);

		SOCVec3Cross(&right, &up, &forward);
		SOCVec3Normalize(&right, &right);

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

		SOCQuaternionRotationMatrix(&rotation, &rotationMatrix);
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

		eulerAngles = SOCEulerNormalize(e);
		position = p;
		scale = s;
	}

	void Transform::UpdateMatrix()
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

	void Transform::Roll(float angle)
	{
		SOC_Matrix T;

		SOCMatrixRotationAxis(&T, &forward, angle);
		SOCVec3TransformCoord(&up, &up, &T);
		SOCVec3TransformCoord(&right, &right, &T);
	}

	void Transform::Yaw(float angle)
	{
		SOC_Matrix T;

		SOCMatrixRotationAxis(&T, &up, angle);
		SOCVec3TransformCoord(&right, &right, &T);
		SOCVec3TransformCoord(&forward, &forward, &T);
	}

	void Transform::Pitch(float angle)
	{
		SOC_Matrix T;

		SOCMatrixRotationAxis(&T, &right, angle);
		SOCVec3TransformCoord(&right, &right, &T);
		SOCVec3TransformCoord(&forward, &forward, &T);
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

	float Transform::GetRadius()
	{
		return radius; 
	}

	SOC_Vector3 Transform::GetForward()
	{
		return forward;
	}
}