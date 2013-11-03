#include "TestScene.h"
#include "LambertMaterial.h"

using namespace Rendering;

TestScene::TestScene(void)
{
	camObject = nullptr;
	meshObject = nullptr;
}

TestScene::~TestScene(void)
{

}


void TestScene::OnInitialize()
{
	camObject = new Object;

	rootObjects->AddObject(camObject);

	Rendering::Camera *camera = camObject->AddComponent<Camera>();	

	fbxsdk_2014_1::FbxManager *manager = fbxsdk_2014_1::FbxManager::Create();
	Rendering::Importer::FBXImporter *importer = new Rendering::Importer::FBXImporter(manager);

	bool success;
	success = importer->Initialize("");
	success = importer->LoadScene("carl.fbx");

	meshObject = importer->BuildObject(nullptr);
	rootObjects->AddObject(meshObject);

	SOC_Vector3 v = SOC_Vector3(0.0, -100.0, 350);
	meshObject->GetTransform()->SetPosition(v);
	meshObject->GetTransform()->radius = 1000.0f;

	camObject->GetTransform()->SetPosition(SOC_Vector3(0, 0, 0));
	camObject->GetTransform()->SetDirection(SOC_Vector3(0, 0, 1));

	camera = camObject->GetComponent<Camera>();
	cameraMgr->SetMainCamera(camera);

	Texture::Texture *texture = textureMgr->AddTexture("Test.png");
	Material::LambertMaterial *lambert = new Material::LambertMaterial(texture);
	//
}

void TestScene::OnUpdate(float dt)
{
	SOC_Vector3 eular = meshObject->GetTransform()->GetLocalEulerAngle();
//	meshObject->GetTransform()->Rotate(0, 1.0f, 0.0f);
//	meshObject->GetTransform()->Translate(SOC_Vector3(0, 0, 0.0001));
}

void TestScene::OnRenderPreview()
{
}

void TestScene::OnRenderPost()
{
}

void TestScene::OnDestroy()
{
	camObject->DeleteAllComponent();
	meshObject->DeleteAllComponent();

	Utility::SAFE_DELETE(camObject);
	Utility::SAFE_DELETE(meshObject);
}