#include "Scene.h"

using namespace Rendering;
using namespace Texture;
using namespace Shader;
using namespace Light;
using namespace std;

//static Scene* nowScene = nullptr;

Scene::Scene(void) : BaseScene()
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

	NextState();
	OnInitialize();
}

void Scene::Run(float dt)
{
	Camera *camera = Camera::GetMainCamera();

	if(camera == nullptr)
		return;

	graphics->BeginScene();
	{
		OnPreview(dt);

		OnUpdate(dt);
		camera->Run(dt);

		OnPost(dt);
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