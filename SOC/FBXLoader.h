#pragma once

#define FBXSDK_NEW_API

#include <fbxsdk.h>
#pragma comment(lib, "libfbxsdk-md.lib")

namespace Rendering
{
	namespace Loader
	{
		class FBXLoader
		{
		private:
			FbxManager	*manager;
			FbxScene	*scene;

		public:
			FBXLoader(void)
			{
				manager = nullptr;
				scene = nullptr;
			}

			~FBXLoader(void)
			{
			}

		public:
			bool Initialize(const char *sceneName)
			{
				manager = FbxManager::Create();

				if(manager == nullptr)
					return false;

				FbxIOSettings *ioSetting = FbxIOSettings::Create(manager, IOSROOT);
				manager->SetIOSettings(ioSetting);

				FbxString path = fbxsdk_2014_1::FbxGetApplicationDirectory();

#if defined (FBXSDK_ENV_WIN)
				FbxString IExtension = "dll";
#elif defined (FBXSDK_ENV_MAC)
				FbxString IExtension = "dylib";				
#elif defined (FBXSDK_ENV_LINUX)
				FbxString IExtension = "so";
#endif

				manager->LoadPluginsDirectory(path.Buffer(), IExtension.Buffer());
				scene = FbxScene::Create(manager, sceneName);

				return scene != nullptr;
			}

			bool LoadScene(const char *fileName, const char *password = nullptr)
			{
				int fileMajor, fileMinor, fileRevision;
				int sdkMajor, sdkMinor, sdkRevision;

//				int  animStackCount;
				bool status;
//				char password[1024];

				//파일의 버젼번호는 sdk에 의해 생성됩니다?
				//Get the file version number generate by the FBX SDK
				FbxManager::GetFileFormatVersion(sdkMajor, sdkMinor, sdkRevision);

				//임포터를 생성합니다.
				FbxImporter* importer = FbxImporter::Create(manager, "");

				//파일 이름을 제공하여 임포터를 초기화 시킵니다.
				bool importStatus = importer->Initialize(fileName, -1, manager->GetIOSettings());

				//디버깅 용도이긴 한데, 뭐 굳이 느리진 않을테니 걍 둠
				//누가 지워주겠지
				importer->GetFileVersion(fileMajor, fileMinor, fileRevision);

				if(importStatus == false)
				{
					FbxString error = importer->GetStatus().GetErrorString();
					// error 내용은, error Buffer에
				}

				if(importer->IsFBX())
				{
//					animStackCount = importer->GetAnimStackCount();

					//for(int i = 0; i < animStackCount; ++i)
					//{
					//	FbxTakeInfo* takeInfo = importer->GetTakeInfo(i);
					//	//정보를 얻어 온 다
					//}


					manager->GetIOSettings()->SetBoolProp(IMP_FBX_MATERIAL,        true);
					manager->GetIOSettings()->SetBoolProp(IMP_FBX_TEXTURE,         true);
					manager->GetIOSettings()->SetBoolProp(IMP_FBX_LINK,            true);
					manager->GetIOSettings()->SetBoolProp(IMP_FBX_SHAPE,           true);
					manager->GetIOSettings()->SetBoolProp(IMP_FBX_GOBO,            true);
					manager->GetIOSettings()->SetBoolProp(IMP_FBX_ANIMATION,       true);
					manager->GetIOSettings()->SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
				}

				status = importer->Import(scene);

				if(status == false && 
					importer->GetStatus().GetCode() == FbxStatus::ePasswordError)
				{
					//패스워드가 필요함니다? 내놔
					FbxString str(password);
					manager->GetIOSettings()->SetStringProp(IMP_FBX_PASSWORD, str);
					manager->GetIOSettings()->SetBoolProp(IMP_FBX_PASSWORD_ENABLE, true);

					status = importer->Import(scene);

					if(status == false && importer->GetStatus().GetCode() == FbxStatus::ePasswordError)
						return false;
				}

				importer->Destroy();

				return status;
			}

			bool AllNodes(FbxNode *node)
			{
				if( node == nullptr )
					return false;

				FbxNodeAttribute *attribute = node->GetNodeAttribute();

				if(attribute != nullptr)
				{
					FbxNodeAttribute::EType type = attribute->GetAttributeType();

					if(type == FbxNodeAttribute::eMesh)
					{}
					else if(type == FbxNodeAttribute::eSkeleton)
					{}
					else if(type == FbxNodeAttribute::eCamera)
					{}
					else if(type == FbxNodeAttribute::eNurbs)
					{}
					else if(type == FbxNodeAttribute::ePatch)
					{}
					else
					{

					}
				}

				int childCount = node->GetChildCount();
				for(int i=0; i<childCount; ++i)
				{

				}

				return true;
			}

			bool AssignMesh(FbxNode *node)
			{
				if(node == nullptr)
					return false;

				FbxMesh *mesh = node->GetMesh();

				if(mesh == nullptr)
					return false;

				int polygonCount = mesh->GetPolygonCount();
				int controlPointCount = mesh->GetControlPointsCount();

				FbxVector4 *controlPoints = mesh->GetControlPoints();

				int vertexIndex = 0;

				if( polygonCount < 0 || controlPointCount < 0 )
					return false;

				//AssignMaterials

				//vertex
				for(int i=0; i<controlPointCount; ++i)
				{
					//이해 ㄴㄴ 인게 아래가 예제코드야
					//controlPoint[i][0] push to vertex
					// ''            [1] push to vertex
					// ''            [2] push to vertex
					//mesh.mutable_vertex_list.pushback(vertex)
					//뭐지 이게 대체
				}

				for(int i=0; i<polygonCount; ++i)
				{
					//int list idxlist

					int count = mesh->GetLayerCount();
					for(int j=0; j<count; ++j)
					{
						//material index
						FbxLayerElementMaterial *fbxMaterials = mesh->GetLayer(j)->GetMaterials();
						if(fbxMaterials != nullptr)
						{
							FbxLayerElement::EMappingMode mode = fbxMaterials->GetMappingMode();
							FbxLayerElement::EReferenceMode refMode = fbxMaterials->GetReferenceMode();

							if(mode == FbxLayerElement::eByPolygon)
							{
								if(refMode == FbxLayerElement::eIndexToDirect)
								{
									int materialIdx = fbxMaterials->GetIndexArray().GetAt(i);
									//mesh mutable material index push materialidx
								}
							}
						}
					}

					int polyGonSize = mesh->GetPolygonSize(i);
					for(int j=0; j<polyGonSize; ++j, ++vertexIndex)
					{
						int ctrlPointIdx = mesh->GetPolygonVertex(i, j);
						//FbxVector4 point = ctrlPoints[ctrlPointIdx];

						//vertex idx
						//vertex idx push back ctrl point idx
						int size = mesh->GetLayerCount();
						for(int k=0; k<size; ++k)
						{
							FbxLayer *layer = mesh->GetLayer(k);
							if(layer != __nullptr)
							{
								//assign normals
								//assign uvs
								//assign vertex colors
							}
						}
					}
					//mesh mutable vertex list push back vertexidx
				}

				//blend shape
				//assign blend shapes
				//skin
				//assign skins

				return true;
			}

			bool AssignMaterials(FbxNode *node)
			{
				if(node == nullptr)
					return false;

				int count = node->GetMaterialCount();

				for(int i=0; i<count; ++i)
				{
					FbxSurfaceMaterial *fbxMaterial = node->GetMaterial(i);
					if(fbxMaterial)
					{
						//Material material;
						FbxClassId id = fbxMaterial->GetClassId();

						//Shading
						if( id.Is(FbxSurfacePhong::ClassId) )
						{
							FbxSurfacePhong *phong = static_cast<FbxSurfacePhong*>(fbxMaterial);
							//ambient color 세팅, factor diffuse specular emissive 등등등
							//TransparentColor factor는 뭐지 reflection은 specular인데 -;
							//reflectionfactor, shininess???
							//재질을 좀 다시 짜야겠어
							//지금 쉐이더만 담고 있는데 좀 바꿔야겠다
						}
						else if(id.Is(FbxSurfaceLambert::ClassId))
						{
							FbxSurfaceLambert *lambert = static_cast<FbxSurfaceLambert*>(fbxMaterial);
							//ambient, diffuse, emissive, transparent, bump(?), bumpfactor, vectorDisplacementColor, Factor
						}

						FbxProperty fbxProperty = fbxMaterial->GetFirstProperty();
						for(; fbxProperty.IsValid(); fbxMaterial->GetNextProperty(fbxProperty))
						{
							//AssignTexture
						}
						//mesh.push(material);
					}

					return true;
				}
			}

			bool AssignTextures(FbxProperty *fbxProperty)
			{
				int layeredTextureCount = fbxProperty->GetSrcObjectCount<FbxLayeredTexture>();

				if(layeredTextureCount > 0)
				{
					FbxLayeredTexture *layeredTexture;
					
					for(int i=0; i<layeredTextureCount; ++i)
					{
						layeredTexture = fbxProperty->GetSrcObject<FbxLayeredTexture>();

						if(layeredTexture == nullptr)
							continue;

						//texture list
						int count = layeredTexture->GetSrcObjectCount<FbxTexture>();
						for(int j=0; j<count; ++j)
						{
							FbxTexture *texture = layeredTexture->GetSrcObject<FbxTexture>(j);
							if(texture == nullptr)
								continue;

							FbxFileTexture *fileTexture = FbxCast<FbxFileTexture>(texture);
							if(fileTexture)
								continue;

							FbxLayeredTexture::EBlendMode blendMode;
							if(layeredTexture->GetTextureBlendMode(j, blendMode))
							{
								//texture set blend mode
							}

							double alpha = 0.0f;
							if(layeredTexture->GetTextureAlpha(j, alpha))
							{
								//texture set alpha
							}

							//texture 꺼내다가 세팅해
							//name을 아니까 뭐 어느정도 세팅은 가능하가? relativeFileName도 있고
							//이름은 아니까, 텏쳐 매니저에서 빼다가 쓰면 될듯 싶어
							//그리고, texture list에 add해
						}
						//메테리얼 레이어드텍스쳐에 이 리스트를 추가하라는데?
						//뭐긴 블랜딩이지
					}
				}
				else
				{
					int count  = fbxProperty->GetSrcObjectCount<FbxTexture>();

					for(int i=0; i<count; ++i)
					{
						FbxTexture *texture = fbxProperty->GetSrcObject<FbxTexture>();
						if(texture == nullptr)
							continue;

						FbxFileTexture *fileTexture = FbxCast<FbxFileTexture>(texture);
						if(fileTexture)
							continue;

						//위 처럼 texture Mgr 받아와서 처리 해줌
					}
				}

				return true;
			}



			void GetPolygon(FbxMesh *fbxMesh)
			{

			}

			void Destroy()
			{
				if(manager)
				{
					manager->Destroy();
					manager = nullptr;
				}

				if(scene)
				{
					scene->Destroy();
					scene = nullptr;
				}
			}
		};
	}
}