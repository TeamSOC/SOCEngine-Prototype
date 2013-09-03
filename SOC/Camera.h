#pragma once

#include "Object.h"
#include "Rect.h"
#include "Frustum.h"
#include "Skybox.h"
#include "LightManager.h"
#include "DeviceDirector.h"

namespace Rendering
{
	class Camera : public Object
	{
	public:
		enum TYPE { TYPE_PERSPECTIVE, TYPE_ORTHOGRAPHIC };
		enum CLEAR_FLAG { CLEAR_FLAG_SKYBOX, CLEAR_FLAG_SOLIDCOLOR, CLEAR_FLAG_TARGET, CLEAR_FLAG_DONT_CLAR };
		//CLEAR_FLAG_DEPTHONLY는 제외함. 어떻게 구현하라는건지 잘 모르겠음 -ㅠ-;

	private:
		Frustum *frustum;
		Device::DeviceDirector *device;

	private:
		Common::Rect<float>	  normalizedViewPortRect;
		std::vector<Object*>* sceneObjects;
		Light::LightManager* sceneLights;

	public:  //굳이 private로 할 필요는 없지.
		float				FOV;
		float				clippingNear;
		float				clippingFar;
		CLEAR_FLAG			clearFlag;
		TYPE				camType;
		float				aspect;
		Color				clearColor;
		Skybox				*skybox;
		//1. hdr을 여기서 처리하는데? 제가 어찌 압니까..
		/*2. 컬링 마스크처리에서 여러개의 태그를 선택할 수 있어.
		     그럼 태그 시스템을 바꿔야 한단 소리네 하.. */
		//3. 렌더 텍스쳐 선택. 이건 지금 할게 아니야

	public:
		Camera(Device::DeviceDirector *device, Skybox *skybox, 
			std::vector<Object*>* objectRoots, Light::LightManager* sceneLightMgr, 
			Object *parent = NULL);
		~Camera(void);

	private:
		Camera(const Camera &cam)
		{
		}

	private:
		void CalcAspect();

	public:
		void Clear();

	public:
		void GetPerspectiveMatrix(SOC_Matrix *outMatrix, float farGap);
		void GetOrthoGraphicMatrix(SOC_Matrix *outMatrix);
		void GetProjectionMatrix(SOC_Matrix *outMatrix, float farGap = 0);
		void GetViewMatrix(SOC_Matrix *outMatrix){GetMatrix(outMatrix);}

	public:
		bool Render();

	public:
		void SetViewPort(Common::Rect<float> rect);
		
		static void SetMainCamera(Camera *camera);
		static Camera* GetMainCamera();
	};

}