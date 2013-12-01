#pragma once

#include "RenderingMath.h"
#include "AABB.h"
#include "Math.h"

namespace Rendering
{
	class Transform
	{
	private:
		Transform *root;
		Transform *parent;

	protected:
		SOC_Vector3 forward;
		SOC_Vector3 right;
		SOC_Vector3 up;

		SOC_Vector3 position;
		SOC_Vector3 localPosition;

		SOC_Quaternion rotation;

		SOC_Vector3 scale;
		SOC_Vector3 localScale;

		SOC_Vector3 eulerAngles;
		SOC_Vector3 localEulerAngles;

		SOC_Matrix matrix;

	private:
		float radius;
		Intersection::AABB bound;

	public:
		Transform(Transform* parent);
		~Transform(void);

	public:
		float CalcRadius(Transform *child);

	public:
		void LookAt(Transform *target);
		void LookAt(SOC_Vector3 worldPosition);
		//void LookAt(Transform *target, SOC_Vector3 worldUp);
		void LookAt(SOC_Vector3 worldPosition, SOC_Vector3 worldUp);

		void Rotate(SOC_Vector3 eulerAngles);
		void Rotate(float x, float y, float z);

		void Translate(SOC_Vector3 translation);
		void TranslateWithUpVec(float units);
		void TranslateWithForwardVec(float units);
		void TranslateWithRightVec(float units);

		void Billboard(SOC_Matrix *camWorldMat, SOC_Matrix *outMatrix);

	protected:
		void UpdateMatrix();

	private:
		void Roll(float angle);
		void Yaw(float angle);
		void Pitch(float angle);

	public:
		void UpdateWorldTransform();

	public:
		void SetPosition(SOC_Vector3 position);		
		//void SetRotation(SOC_Quaternion quaternion);				
		void SetScale(SOC_Vector3 scale);
		void SetEulerAngles(SOC_Vector3 euler);
		void SetDirection(SOC_Vector3 dir);

	public:
		void GetMatrix(SOC_Matrix *outMatrix);
		void GetWorldMatrix(SOC_Matrix *outMatrix);

		SOC_Vector3 GetWorldPosition();
		SOC_Vector3 GetLocalPosition();

		SOC_Vector3 GetLocalEulerAngle();
		SOC_Vector3 GetWorldEulerAngle();

		SOC_Vector3 GetLocalScale();
		SOC_Vector3 GetWorldScale();

		SOC_Quaternion GetRotation();

		SOC_Vector3 GetForward();
		SOC_Vector3 GetRight();
		SOC_Vector3 GetUp();

		float GetRadius();
		void SetRadius(float radius);

		void SetBound(Intersection::AABB &bound);
		Intersection::AABB GetBound();
	};
}