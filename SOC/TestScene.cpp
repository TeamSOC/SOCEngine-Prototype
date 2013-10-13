#include "TestScene.h"

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
	meshObject = new Object;

	AddObject(camObject);
	AddObject(meshObject);

	camObject->AddComponent<Camera>();
	
	Mesh::Mesh *mesh = meshObject->AddComponent<Mesh::Mesh>();
	Mesh::MeshFilter *filter = mesh->GetFilter();

	fbxsdk_2014_1::FbxManager *manager = fbxsdk_2014_1::FbxManager::Create();
	Rendering::Importer::FBXImporter *importer = new Rendering::Importer::FBXImporter(manager);

	bool success;

	success = importer->Initialize("");
	success = importer->LoadScene("turret_anim_v2_5.fbx");

	Rendering::MaterialElements ematerial;
	Rendering::MeshFilterElements emesh;
	Rendering::MaterialTextures etex;

	success = importer->Decode(&ematerial, &emesh, &etex);

	filter->Create(
		emesh.vertices, emesh.normals, emesh.tangents,
		emesh.binomals, emesh.texcoords, emesh.colors,
		emesh.numOfVertex, emesh.numOfTriangle, emesh.indices,
		SOC_TRIANGLE_LIST, emesh.isDynamic, false);
}

void TestScene::OnUpdate(float dt)
{

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