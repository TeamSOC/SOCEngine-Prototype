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

	rootObjects->Add(camObject);

	Rendering::Camera *camera = camObject->AddComponent<Camera>();	

	fbxsdk_2014_1::FbxManager *manager = fbxsdk_2014_1::FbxManager::Create();
	Rendering::Importer::FBXImporter *importer = new Rendering::Importer::FBXImporter(manager);

	bool success;
	success = importer->Initialize("");
//	success = importer->LoadScene("carl.fbx");
//	success = importer->LoadScene("GR_attack.fbx");
//	success = importer->LoadScene("dxsphere.fbx");
//	success = importer->LoadScene("turret_anim_v2_5.fbx");
	success = importer->LoadScene("AS_FatZombie_FBX.fbx");

	meshObject = importer->BuildObject(nullptr);
	rootObjects->Add(meshObject);
	meshObject->GetTransform()->SetPosition(SOC_Vector3(0, -100, 0));
//	meshObject->GetTransform()->SetPosition(SOC_Vector3(0, 0, -180));
	meshObject->GetTransform()->SetEulerAngles(SOC_Vector3(90, 0, 0));

	//	SOC_Vector3 v = SOC_Vector3(0.0, 30, 100);

	//meshObject2 = importer->BuildObject(nullptr);
	//rootObjects->Add(meshObject2);
	//meshObject2->GetTransform()->SetPosition(SOC_Vector3(100, 0, 0));

	camObject->GetTransform()->SetPosition(SOC_Vector3(0, 0, -200));
//	camObject->GetTransform()->SetPosition(SOC_Vector3(0, 30, -100));
	camObject->GetTransform()->LookAt(SOC_Vector3(0, 0, 0));
//	camObject->GetTransform()->SetDirection(SOC_Vector3(0, 0, 1));

	camera = camObject->GetComponent<Camera>();
	cameraMgr->SetMainCamera(camera);

	//meshObject->Get(1)->GetComponent<Mesh::Mesh>()->GetRenderer()->DeleteMaterial();

	//Texture::Texture *texture = textureMgr->AddTexture("Test.jpg");
	//Material::LambertMaterial *lambert = new Material::LambertMaterial(texture);
	//meshObject->Get(1)->GetComponent<Mesh::Mesh>()->GetRenderer()->SetMaterial(lambert);

	lightObj = new Object;
	rootObjects->Add(lightObj);
	Light::DirectionalLight *light = lightObj->AddComponent<Light::DirectionalLight>();
	light->diffuse.r = 0.0f;
	light->diffuse.g = 0.0f;
	light->diffuse.b = 1.0f;
	lightMgr->AddLight(light);
	lightObj->GetTransform()->SetPosition(SOC_Vector3(500, 500, -500));
	lightObj->GetTransform()->LookAt(meshObject->GetTransform()->GetWorldPosition());

	lightObj2 = new Object;
	rootObjects->Add(lightObj2);
	Light::DirectionalLight *light2 = lightObj2->AddComponent<Light::DirectionalLight>();
	light2->diffuse.r = 1.0f;
	light2->diffuse.g = 0.0f;
	light2->diffuse.b = 0.0f;
	lightMgr->AddLight(light2);
	lightObj2->GetTransform()->SetPosition(SOC_Vector3(-500, -500, 500));
	lightObj2->GetTransform()->LookAt(meshObject->GetTransform()->GetWorldPosition());


//	lightObj2->GetTransform()->SetEulerAngles(SOC_Vector3(10, 10, 10));
}

void TestScene::OnUpdate(float dt)
{
	SOC_Vector3 eular = meshObject->GetTransform()->GetLocalEulerAngle();
	meshObject->GetTransform()->Rotate(0, 1, 0.0f);
//	meshObject2->GetTransform()->Rotate(0, -1.0f, 0.0f);
	//	meshObject->GetTransform()->Translate(SOC_Vector3(0, 0, 0.01));
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