#include "Camera.h"
#include "Scene.h"

using namespace Common;
using namespace std;
using namespace Rendering::Light;
using namespace Device;

namespace Rendering
{
	Camera::Camera()
	{
		FOV = 60;
		clippingNear = 0.1f;
		clippingFar = 1000.0f;
		normalizedViewPortRect = Rect<float>(0, 0, 1, 1);

		Size<int> windowSize = DeviceDirector::GetInstance()->GetApplication()->GetSize();
		aspect = (float)windowSize.w / (float)windowSize.h;

		camType    = Type::Perspective;
		clearColor = Color(1.0f, 0.5f,0.5f,1.0f);

		frustum = new Frustum(0.0f);
		
		this->skybox = nullptr;

		clearFlag = ClearFlag::FlagSolidColor;
//		Device::DeviceDirector::GetInstance()->GetScene()
	}

	Camera::~Camera(void)
	{
		Utility::SAFE_DELETE(frustum);
	}

	void Camera::Clear()
	{
		//defulat is 'target clear option'.
//		Graphics flag = Graphics::FlagTarget;
		Graphics::GraphicsForm::ClearFlag flag = Graphics::GraphicsForm::FlagTarget;

		if( clearFlag == ClearFlag::FlagDontClear )
			return;

		if( clearFlag == ClearFlag::FlagSkybox )
		{
			//skybox Rendering
			skybox->Render();
			return;
		}

		else if( clearFlag == ClearFlag::FlagSolidColor )
			flag |= Graphics::GraphicsForm::FlagZBuffer;

		DeviceDirector::GetInstance()->GetGraphics()->Clear( 0, NULL, flag, clearColor, 1.0f, 0);
	}

	void Camera::CalcAspect()
	{
		float w = normalizedViewPortRect.size.w - normalizedViewPortRect.x;
		float h = normalizedViewPortRect.size.h - normalizedViewPortRect.y;

		Size<int> windowSize =  Device::DeviceDirector::GetInstance()->GetSize();
		
		aspect = ((float)windowSize.w * w) / ((float)windowSize.h * h);
	}

	void Camera::GetPerspectiveMatrix(SOC_Matrix *outMatrix, float farGap)
	{
		SOCMatrixPerspectiveFovLH(outMatrix, FOV, aspect, clippingNear, clippingFar + farGap);
	}
	void Camera::GetOrthoGraphicMatrix(SOC_Matrix *outMatrix)
	{
		Size<int> windowSize = Device::DeviceDirector::GetInstance()->GetSize();;
		SOCMatrixOrthoLH(outMatrix, 
			(float)(windowSize.w * normalizedViewPortRect.size.w),
			(float)(windowSize.h * normalizedViewPortRect.size.h),
			clippingNear, clippingFar);
	}
	void Camera::GetProjectionMatrix(SOC_Matrix *outMatrix, float farGap /* =0 */)
	{
		if(camType == Type::Perspective)
		{
			GetPerspectiveMatrix(outMatrix, farGap);
			return;
		}

		GetOrthoGraphicMatrix(outMatrix);
	}

	void Camera::SetViewPort(Common::Rect<float> rect)
	{
		normalizedViewPortRect = rect;
		CalcAspect();
	}

	void Camera::SceneUpdate(float dt, std::vector<Object*> *sceneObjects)
	{
		for(vector<Object*>::iterator iter = sceneObjects->begin(); iter != sceneObjects->end(); ++iter)
			(*iter)->Update(dt);
	}

	void Camera::SceneRender(Camera *cam, std::vector<Object*> *sceneObjects, Light::LightManager* sceneLights)
	{
		SOC_Matrix projMat, viewMat, viewProjMat;
		cam->GetProjectionMatrix(&projMat);
		cam->ownerTransform->GetWorldMatrix(&viewMat);
		viewProjMat = viewMat * projMat;

		cam->Clear();		
		cam->frustum->Make(&(viewMat * projMat));

		//추후 작업.	

		vector<LightForm*> lights;
		sceneLights->Intersect(cam->frustum, &lights);
		//월드 상의 빛에서 절두체에 겹치는거 모두 찾음.

		for(vector<Object*>::iterator iter = sceneObjects->begin(); iter != sceneObjects->end(); ++iter)
		{
//			(*iter)->Update(delta);
			(*iter)->Culling(cam->frustum);
			(*iter)->Render(&lights, &viewMat, &projMat, &viewProjMat);
		}
	}

	void Camera::GetViewMatrix(SOC_Matrix *outMatrix)
	{
		ownerTransform->GetMatrix(outMatrix);
	}

	void Camera::GetViewProjectionMatrix(SOC_Matrix *outMatrix, float farGap)
	{
		SOC_Matrix proj;

		ownerTransform->GetMatrix(outMatrix); // view Matrix
		GetProjectionMatrix(&proj, farGap);

		SOCMatrixMultiply(outMatrix, outMatrix, &proj);
	}
}