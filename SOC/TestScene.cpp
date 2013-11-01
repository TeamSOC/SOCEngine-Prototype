#include "TestScene.h"
//#include "MeshImporter.h"

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

	AddObject(camObject);

	Rendering::Camera *camera = camObject->AddComponent<Camera>();	

	//Mesh::MeshFilter *filter = mesh->GetFilter();

	fbxsdk_2014_1::FbxManager *manager = fbxsdk_2014_1::FbxManager::Create();
	Rendering::Importer::FBXImporter *importer = new Rendering::Importer::FBXImporter(manager);
//	Rendering::Importer::MeshImporter *importer = new Rendering::Importer::MeshImporter(manager);

	bool success;
	success = importer->Initialize("");
	success = importer->LoadScene("carl.fbx");

	meshObject = importer->BuildObject(nullptr);
	AddObject(meshObject);

	Rendering::Mesh::Mesh *mesh = meshObject->GetObject(1)->GetComponent<Mesh::Mesh>();

	SOC_Vector3 v = SOC_Vector3(0.0, 0.0, 100);
	meshObject->GetTransform()->SetPosition(v);
	meshObject->GetTransform()->radius = 1000.0f;
//	meshObject->GetTransform()->SetEulerAngles(SOC_Vector3(0, 90, 0));

	camObject->GetTransform()->SetPosition(SOC_Vector3(0, 0, 0));
	camObject->GetTransform()->SetDirection(SOC_Vector3(0, 0, 1));

	camera = camObject->GetComponent<Camera>();
	cameraMgr->SetMainCamera(camera);

	Mesh::MeshRenderer *renderer = mesh->GetRenderer();
	Material *material = new Material;
	Shader::Shader *shader = new Shader::Shader(graphics);

	std::string shaderCode;
	shaderMgr->LoadShaderFromFile("TestDiffuse2", &shaderCode, true);
	shader->Compile(shaderCode);

	material->AddShader(shader);
	renderer->AddMaterial(material, false);

	shader->Compile(shaderCode);
}

void TestScene::OnUpdate(float dt)
{
	SOC_Vector3 eular = meshObject->GetTransform()->GetLocalEulerAngle();
//	meshObject->GetTransform()->Rotate(0, 0.0000001f, 0.0f);
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