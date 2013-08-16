#pragma once

//#include <stdarg.h>
#include <vector>

#include <d3dx9.h>
#include <d3d9.h>

#include <string>

namespace Rendering
{
	class Object
	{
	protected:
		int renderQueue;
		std::vector<Object*> childs;
		bool use;

	protected:
		D3DXVECTOR3 forward;
		D3DXVECTOR3 right;
		D3DXVECTOR3 up;

		D3DXVECTOR3 position;
		D3DXVECTOR3 localPosition;

		D3DXQUATERNION rotation;

		D3DXVECTOR3 scale;
		D3DXVECTOR3 localScale;

		D3DXVECTOR3 eulerAngles;
		D3DXVECTOR3 localEulerAngles;

		D3DXMATRIXA16 matrix;

		float radius;

	protected:
		Object *parent;
		Object *root;

	public:
		std::string name;
		std::string tag;
		std::string layer;

	public:
		Object(Object* parent = NULL);
		virtual ~Object(void);

	public:
		virtual bool Update();
		virtual bool Render();

	private:
		enum FIND_ENUM{FIND_ENUM_NAME, FIND_ENUM_TAG};
		std::vector<Object*> _FindChild(std::string str, FIND_ENUM e, bool one);

	public:
		std::vector<Object*> FindChilds(std::string name);
		std::vector<Object*> FindChildsWithTag(std::string tag);

		Object* FindChild(std::string name);
		Object* FindChildWithTag(std::string tag);

		void AddChild(Object *child, bool copy = false);
		void AddChild(Object *child, int renderQueueOrder, bool copy = false);

		void DeleteChild(Object *child);
		void DeleteAllChilds();

	public:
		void LookAt(Object *target);
		void LookAt(D3DXVECTOR3 worldPosition);
		void LookAt(Object *target, D3DXVECTOR3 worldUp);
		void LookAt(D3DXVECTOR3 worldPosition, D3DXVECTOR3 worldUp);

		void Rotate(D3DXVECTOR3 eulerAngles);
		void Rotate(D3DXVECTOR3 axis, float angle);
		void Rotate(float x, float y, float z);

		void Translate(D3DXVECTOR3 translation);
		void TranslateWithUpVec(float units);
		void TranslateWithForwardVec(float units);
		void TranslateWithRightVec(float units);

		void Billboard(Object *camera, D3DXMATRIX *outMatrix);

		bool IsChildOf(Object *parent);

	protected:
		void UpdateMatrix();
	public:
		void UpdateWorldTransform();
		/* 쓸모 없을 듯
		void UpdateWorldPosition();
		void UpdateWorldScale();
		void UpdateWorldEuler();
		*/

	public:
		void SetPosition(D3DXVECTOR3 position);		
		void SetRotation(D3DXQUATERNION quaternion);				
		void SetScale(D3DXVECTOR3 scale);
		void SetEulerAngles(D3DXVECTOR3 euler);

	private:
		void Roll(float angle);
		void Yaw(float angle);
		void Pitch(float angle);

	public:
		void GetMatrix(D3DXMATRIX *outMatrix);
		void GetWorldMatrix(D3DXMATRIX *outMatrix);

		int GetChildCount()
		{ return childs.size(); }
		Object* Getchild(int index)
		{ return *(childs.begin()+index); }
		float GetRadius()
		{ return radius; }
		D3DXVECTOR3 GetWorldPosition();
		D3DXVECTOR3 GetLocalPosition();

		void SetUse(bool is);
		bool GetUse();

	public:
		void UpdateChild();

	public:
		static Object* Copy(Object *obj);
	};

}