#pragma once

#include "Transform.h"
#include "Frustum.h"
#include "Skybox.h"
#include "LightManager.h"
#include "Component.h"

namespace Rendering
{
	class Camera : public Component
	{
	public:
		static const Component::Type ComponentType = Component::Type::Camera;

	public:
		enum Type { Perspective, Orthographic };
		enum ClearFlag { FlagSkybox, FlagSolidColor, FlagTarget, FlagDontClear };
		//CLEAR_FLAG_DEPTHONLY는 제외함. 어떻게 구현하라는건지 잘 모르겠음 -ㅠ-;

	private:
		Frustum		*frustum;

	private:
		Common::Rect<float>	  normalizedViewPortRect;

	public:  //굳이 private로 할 필요는 없지.
		float				FOV;
		float				clippingNear;
		float				clippingFar;
		ClearFlag			clearFlag;
		Type				camType;
		float				aspect;
		Color				clearColor;
		Skybox				*skybox;
		//1. hdr을 여기서 처리하는데?
		/*2. 컬링 마스크처리에서 여러개의 태그를 선택할 수 있어.
		     그럼 태그 시스템을 바꿔야 한단 소리네 하.. */
		//3. 렌더 텍스쳐 선택. 이건 지금 할게 아니야

	public:
		Camera();
		~Camera(void);

	private:
		void CalcAspect();
		void Clear();

	public:
		void GetPerspectiveMatrix(SOC_Matrix *outMatrix, float farGap);
		void GetOrthoGraphicMatrix(SOC_Matrix *outMatrix);
		void GetProjectionMatrix(SOC_Matrix *outMatrix, float farGap = 0);
		void GetViewMatrix(SOC_Matrix *outMatrix);
		void GetViewProjectionMatrix(SOC_Matrix *outMatrix, float farGap = 0);

	public:
		static void SceneUpdate(float dt, std::vector<Object*> *sceneObjects);
		static void SceneRender(Camera *cam, 
			std::vector<Object*>::iterator &objectBegin,
			std::vector<Object*>::iterator &objectEnd,
			Light::LightManager* sceneLights);

	public:
		void SetViewPort(Common::Rect<float> rect);

	public:
		virtual void Initialize();
		virtual void Destroy();
//		virtual Component::Type GetComponentType();
	};
}