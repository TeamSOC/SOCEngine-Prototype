#pragma once

//#include <stdarg.h>
#include <vector>
#include <string>

#include "Platform.h"
#include "Frustum.h"
#include "Sphere.h"

#include "Container.h"

namespace Rendering
{
	class Object : public Container<Object>
	{
	protected:
		bool use;
		bool isLight;
		bool culled;

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

		float radius;

	protected:
		Object *parent;
		Object *root;

	public:
		Object(Object* parent = NULL);
		virtual ~Object(void);

	public:
		virtual bool Update(float delta);
//		virtual void UpdateCameraTransform(SOC_Matrix *viewMat, SOC_Matrix *projMat, SOC_Vector3 dir);

		void Render(std::vector<Object*> *lights, SOC_Matrix *viewMat, SOC_Matrix *projMat, SOC_Vector3 dir);

		virtual bool Intersect(Intersection::Sphere &sphere);

	protected:
		virtual void _Render(std::vector<Object*> *lights, SOC_Matrix *viewMat, SOC_Matrix *projMat, SOC_Vector3 &dir);

	private:
		static float CalcRadius(Object *parent, Object *child);

	public:
		Object* AddObject(Object *child, bool copy = false);
		Object* AddObject(Object *child, int renderQueueOrder, bool copy = false);

	public:
		void LookAt(Object *target);
		void LookAt(SOC_Vector3 worldPosition);
		void LookAt(Object *target, SOC_Vector3 worldUp);
		void LookAt(SOC_Vector3 worldPosition, SOC_Vector3 worldUp);

		void Rotate(SOC_Vector3 eulerAngles);
		void Rotate(SOC_Vector3 axis, float angle);
		void Rotate(float x, float y, float z);

		void Translate(SOC_Vector3 translation);
		void TranslateWithUpVec(float units);
		void TranslateWithForwardVec(float units);
		void TranslateWithRightVec(float units);

		void Billboard(SOC_Matrix *camWorldMat, SOC_Matrix *outMatrix);

		bool IsChildOf(Object *parent);
		bool Culling(Frustum *frustum);

	protected:
		void UpdateMatrix();
	public:
		void UpdateWorldTransform();

	public:
		void SetPosition(SOC_Vector3 position);		
		void SetRotation(SOC_Quaternion quaternion);				
		void SetScale(SOC_Vector3 scale);
		void SetEulerAngles(SOC_Vector3 euler);
		void SetDirection(SOC_Vector3 dir);

	private:
		void Roll(float angle);
		void Yaw(float angle);
		void Pitch(float angle);

	public:
		void GetMatrix(SOC_Matrix *outMatrix);
		void GetWorldMatrix(SOC_Matrix *outMatrix);

		float GetRadius();
		SOC_Vector3 GetWorldPosition();
		SOC_Vector3 GetLocalPosition();

		void SetUse(bool is);
		bool GetUse();
		bool IsLight();
		bool Culled();

	public:
		void UpdateChild(float delta);

	public:
		static Object* Copy(Object *obj);
	};

}