#include "Camera.h"
#include "Windows.h"

using namespace Common;
using namespace std;

namespace Rendering
{
	static Camera *mainCamera = NULL;

	Camera::Camera(LPDIRECT3DDEVICE9 device, Skybox *skybox, std::vector<Object*>* sceneObjects, Object *parent/* = NULL*/)
	{
		FOV = 60;
		clippingNear = 0.1f;
		clippingFar = 1000.0f;
		normalizedViewPortRect = Rect<float>(0, 0, 1, 1);

		Size<int> windowSize = Device::Windows::GetSize();
		aspect = (float)windowSize.w / (float)windowSize.h;

		camType    = TYPE_PERSPECTIVE;
		clearColor = D3DCOLOR_ARGB(255,128,128,255);

		frustum = new Frustum(0.0f);
		this->skybox = skybox;
		this->device = device;
		this->sceneObjects = sceneObjects;
		clearFlag = CLEAR_FLAG_SOLIDCOLOR;

		if(mainCamera == NULL)
			mainCamera = this;
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
		DWORD flag = D3DCLEAR_TARGET;

		if( clearFlag == CLEAR_FLAG_DONT_CLAR )
			return;

		if( clearFlag == CLEAR_FLAG_SKYBOX )
		{
			//skybox Rendering
			skybox->Render();
			return;
		}

		else if( clearFlag == CLEAR_FLAG_SOLIDCOLOR )
			flag |= D3DCLEAR_ZBUFFER;

		//	if(clearFlag == CLEAR_FLAG_DEPTHONLY)
		// 뭘 어떻게 구현하라는건지 잘 모르겠음

		device->Clear( 0, NULL, flag, clearColor, 1.0f, 0);
	}

	void Camera::CalcAspect()
	{
		float w = normalizedViewPortRect.size.w - normalizedViewPortRect.x;
		float h = normalizedViewPortRect.size.h - normalizedViewPortRect.y;

		Size<int> windowSize =  Device::Windows::GetSize();
		
		aspect = ((float)windowSize.w * w) / ((float)windowSize.h * h);
	}

	void Camera::GetPerspectiveMatrix(D3DXMATRIX *outMatrix, float farGap)
	{
		D3DXMatrixPerspectiveFovLH(outMatrix, FOV, aspect, clippingNear, clippingFar + farGap);
	}
	void Camera::GetOrthoGraphicMatrix(D3DXMATRIX *outMatrix)
	{
		Size<int> windowSize = Device::Windows::GetSize();
		D3DXMatrixOrthoLH(outMatrix, windowSize.w * normalizedViewPortRect.size.w,
								windowSize.h * normalizedViewPortRect.size.h,
								clippingNear, clippingFar);
	}
	void Camera::GetProjectionMatrix(D3DXMATRIX *outMatrix, float farGap /* =0 */)
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
		D3DXMATRIX projMat, worldMat;
		GetProjectionMatrix(&projMat);
		GetWorldMatrix(&worldMat);

		Clear();		
		frustum->Make(&(worldMat * projMat));

		//추후 작업.		

		vector<Object*> todoList;
		for(vector<Object*>::iterator iter = sceneObjects->begin(); iter != sceneObjects->end(); ++iter)
		{
			//일단은 프로스텀만 건짐. 나머진 그 이후에 생각하지 뭐..
			if(frustum->In((*iter)))
				todoList.push_back((*iter));
		}

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