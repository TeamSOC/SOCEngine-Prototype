#include "Scene.h"

using namespace Rendering;
using namespace Texture;
using namespace Shader;
using namespace Light;
using namespace std;

//static Scene* nowScene = nullptr;

Scene::Scene(void) : BaseScene(), Container()
{
	destroyMgr = true;
}

Scene::~Scene(void)
{
	Destroy();
}

void Scene::Initialize()
{
	lightMgr		= new LightManager();
	textureMgr		= new TextureManager();
	shaderMgr		= new ShaderManager();
	graphics		= Device::DeviceDirector::GetInstance()->GetGraphics();
	cameraMgr		= new CameraManager();

	NextState();
	OnInitialize();
}

void Scene::Update(float dt)
{
	for(vector<Object*>::iterator iter = objects.begin(); iter != objects.end(); ++iter)
		(*iter)->Update(dt);
}

void Scene::Render()
{
	Camera *mainCam = cameraMgr->GetMainCamera();

	if(mainCam == nullptr)
		return;

	graphics->BeginScene();
	{
		OnRenderPreview();

		//for(vector<Camera*>::iterator iter = cameraMgr->GetIteratorBegin(); iter != cameraMgr->GetIteratorEnd(); ++iter)
		//	(*iter)->Run(dt);
		
		Camera::SceneRender(mainCam, &objects, lightMgr);
		//일단은, 이렇게 처리하고 추후에 각 카메라마다 RTT 세팅해준뒤, 그걸 처리하도록 해야할듯.
		//추후 조정이 필요함.

		OnRenderPost();
	}
	graphics->EndScene();
	graphics->Present();
}

void Scene::Destroy()
{
	if(destroyMgr == false)
		return;

	lightMgr->DeleteAll(true);
	shaderMgr->DeleteAll();
	textureMgr->DeleteAll();

	Utility::SAFE_DELETE(lightMgr);
	Utility::SAFE_DELETE(shaderMgr);
	Utility::SAFE_DELETE(textureMgr);
	Utility::SAFE_DELETE(cameraMgr);

	OnDestroy();
}

LightManager* Scene::GetLightManager()
{
	return lightMgr;
}

TextureManager* Scene::GetTextureManager()
{
	return textureMgr;
}

ShaderManager* Scene::GetShaderManager()
{
	return shaderMgr;
}

vector<Object*>* Scene::GetRootObjects()
{
	return &objects;
}

CameraManager* Scene::GetCameraManager()
{
	return cameraMgr;
}