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
//	success = importer->LoadScene("testcarl.fbx");
	success = importer->LoadScene("dxsphere.fbx");

	meshObject = importer->BuildObject(nullptr);
	rootObjects->Add(meshObject);
	meshObject->GetTransform()->SetPosition(SOC_Vector3(-100, 0, 0));

	//	SOC_Vector3 v = SOC_Vector3(0.0, 30, 100);

	meshObject2 = importer->BuildObject(nullptr);
	rootObjects->Add(meshObject2);
	meshObject2->GetTransform()->SetPosition(SOC_Vector3(100, 0, 0));

//	camObject->GetTransform()->SetPosition(SOC_Vector3(0, 0, -300));
	camObject->GetTransform()->SetPosition(SOC_Vector3(0, 0, -300));
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

}

void TestScene::OnUpdate(float dt)
{
	SOC_Vector3 eular = meshObject->GetTransform()->GetLocalEulerAngle();
	meshObject->GetTransform()->Rotate(0, 0.0001f, 0.0f);
	meshObject2->GetTransform()->Rotate(0, -0.0001f, 0.0f);
	//	meshObject->GetTransform()->Translate(SOC_Vector3(0, 0, 0.01));
}

void TestScene::OnRenderPreview()
{
}

void TestScene::OnRenderPost()
{
//#define PI           3.14159265f
//#define FOV          (PI/4.0f)							// 시야각
//#define ASPECT_RATIO (800/(float)800)		// 화면의 종횡비
//#define NEAR_PLANE   1									// 근접 평면
//#define FAR_PLANE    10000								// 원거리 평면
//
//	D3DXVECTOR4 gWorldCameraPosition = D3DXVECTOR4(0, 0, -200, 1.0f);
//	D3DXVECTOR4	gWorldLightPosition(500, 500, -500, 1.0f);
//
//	D3DXMATRIXA16 matView;
//	D3DXVECTOR3 vEyePt( gWorldCameraPosition.x, gWorldCameraPosition.y, gWorldCameraPosition.z ); 
//	D3DXVECTOR3 vLookatPt( 0.0f, 0.0f,  1.0f );
//	D3DXVECTOR3 vUpVec(    0.0f, 1.0f,  0.0f );
// 	D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
//
//	matView._11 = matView._22 = matView._33 = matView._44 = 1.0f;
//	
//	// 투영행렬을 만든다.
//	D3DXMATRIXA16			matProjection;
//	D3DXMatrixPerspectiveFovLH( &matProjection, FOV, ASPECT_RATIO, NEAR_PLANE, FAR_PLANE );
//
//	static float gRotationY = 0.0f;
//	// 프레임마다 0.4도씩 회전을 시킨다.
//	gRotationY += 0.4f * PI / 180.0f;
//	if ( gRotationY > 2 * PI )
//	{
//		gRotationY -= 2 * PI;
//	}
//
//	// 월드행렬을 만든다.
//	D3DXMATRIXA16			matWorld;
//	D3DXMatrixRotationY(&matWorld, gRotationY);
//	matWorld._43 = 5.0f;
//
//	// 쉐이더 전역변수들을 설정
//	ls->SetMatrix("gWorldMatrix", &matWorld);
//	ls->SetMatrix("gViewMatrix",  &matView);
//	ls->SetMatrix("gProjectionMatrix",  &matProjection);
//
//	ls->SetVector("gWorldLightPosition", &gWorldLightPosition);
//	ls->SetVector("gWorldCameraPosition", &gWorldCameraPosition);
//
//	// 쉐이더를 시작한다.
//	UINT numPasses = 0;
//	ls->Begin(&numPasses, NULL);
//	{
//		for (UINT i = 0; i < numPasses; ++i )
//		{
//			ls->BeginPass(i);
//			{
//				// 구체를 그린다.
//				gpSphere->DrawSubset(0);
//			}
//			ls->EndPass();
//		}
//	}
//	ls->End();
}

void TestScene::OnDestroy()
{
	camObject->DeleteAllComponent();
	meshObject->DeleteAllComponent();

	Utility::SAFE_DELETE(camObject);
	Utility::SAFE_DELETE(meshObject);
}