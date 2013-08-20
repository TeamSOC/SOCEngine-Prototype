#include "Camera.h"
#include "DeviceDirector.h"
#include "Light.h"

using namespace Common;
using namespace std;
using namespace Rendering::Light;
using namespace Device;


namespace Rendering
{
	static Camera *mainCamera = NULL;

	Camera::Camera(Device::DeviceDirector device, Skybox *skybox, 
		std::vector<Object*>* objectRoots, LightManager* sceneLightMgr, 
		Object *parent/* = NULL*/)
	{
		FOV = 60;
		clippingNear = 0.1f;
		clippingFar = 1000.0f;
		normalizedViewPortRect = Rect<float>(0, 0, 1, 1);

		Size<int> windowSize = DeviceDirector::GetInstance()->GetApplication()->GetSize();
		aspect = (float)windowSize.w / (float)windowSize.h;

		camType    = TYPE_PERSPECTIVE;
		clearColor = Color(1.0f, 0.5f,0.5f,1.0f);

		frustum = new Frustum(0.0f);
		this->skybox = skybox;
		this->device = device;
		this->sceneObjects = sceneObjects;
		this->sceneLights = sceneLights;

		clearFlag = CLEAR_FLAG_SOLIDCOLOR;

		if(mainCamera == NULL)
			mainCamera = this;

		isLight = false;
	}

	Camera::~Camera(void)
	{
		Utility::SAFE_DELETE(frustum);

		if( mainCamera == this )
			mainCamera = NULL;
	}

	void Camera::Clear()
	{
		//defulat is 'target clear option'.
//		Graphics flag = Graphics::CLEAR_FLAG_TARGET;
		Graphics::GraphicsForm::clearFlag flag = Graphics::GraphicsForm::CLEAR_FLAG_TARGET;

		if( clearFlag == CLEAR_FLAG_DONT_CLAR )
			return;

		if( clearFlag == CLEAR_FLAG_SKYBOX )
		{
			//skybox Rendering
			skybox->Render();
			return;
		}

		else if( clearFlag == CLEAR_FLAG_SOLIDCOLOR )
			flag |= Graphics::GraphicsForm::CLEAR_FLAG_ZBUFFER;

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
		if(camType == TYPE_PERSPECTIVE)
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

	bool Camera::Render()
	{
		SOC_Matrix projMat, worldMat;
		GetProjectionMatrix(&projMat);
		GetWorldMatrix(&worldMat);

		Clear();		
		frustum->Make(&(worldMat * projMat));

		//추후 작업.		

		vector<Object*> objects;
		
		for(vector<Object*>::iterator iter = sceneObjects->begin(); iter != sceneObjects->end(); ++iter)
		{
			//일단은 프로스텀만 건짐. 나머진 그 이후에 생각하지 뭐..
			if( frustum->In( (*iter) ) )
				objects.push_back((*iter));		
		}

		vector<Object*> lights;
		sceneLights->Intersect(frustum, &lights);
		//월드 상의 빛에서 절두체에 겹치는거 모두 찾음.

		for(vector<Object*>::iterator objIter = objects.begin(); objIter != objects.end(); ++objIter)
			(*objIter)->Render(&lights);

		return true;
	}

	void Camera::SetMainCamera(Camera *camera)
	{
		mainCamera = camera;
	}

	Camera* Camera::GetMainCamera()
	{
		return mainCamera;
	}
}