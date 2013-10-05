#pragma once

#define FBXSDK_NEW_API

#include <fbxsdk.h>
#pragma comment(lib, "libfbxsdk-md.lib")

#include "MaterialElements.h"
#include "Bone.h"
#include <vector>

using namespace fbxsdk_2014_1;

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

#if defined(WIN32) && !defined(_USE_GL_DEFINES)

				FbxAxisSystem axis = FbxAxisSystem::DirectX;

#elif defined(__APPLE__) || defined(_USE_GL_DEFINES)

				FbxAxisSystem axis = FbxAxisSystem::OpenGL;

#endif

				axis.ConvertScene(scene);

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

			bool BuildMesh(FbxMesh *fbxMesh)
			{
				if(fbxMesh == nullptr)
					return false;

				FbxNode *node = fbxMesh->GetNode();
				const char *meshName = fbxMesh->GetNameOnly();
				FbxVector4 *ctrlPoints = fbxMesh->GetControlPoints();

				int ctrlPtCount = fbxMesh->GetControlPointsCount();
				int polygonCount = fbxMesh->GetPolygonCount();
				if(ctrlPtCount == 0)
					return false;

				int layerCount = fbxMesh->GetLayerCount();

				int triangleAry[] = {0, 1, 2};
				int rectangleAry[] = {0, 1, 2, 0, 2, 3};

				for(int polygonIdx = 0; polygonIdx < polygonCount; ++polygonIdx)
				{
					int polygonSize = fbxMesh->GetPolygonSize(polygonIdx);					

					if(polygonSize > 4)
						return false;

					int count = polygonSize == 4 ? 6 : 3;
					int *ary  = polygonSize == 4 ? triangleAry : rectangleAry;

					for(int vertexIdx = 0; vertexIdx < count; ++vertexIdx)
					{
						int ctrlPointIdx = fbxMesh->GetPolygonVertex(polygonIdx, ary[vertexIdx]);
						FbxVector4 ctrl = ctrlPoints[ctrlPointIdx];

						//	//ctrl multnormalize(ctrl);
						//	//isSkinned
						//	//v.boneIdx = boneIndices[ctrlPoint];

						FbxLayerElement::EMappingMode mode;
						FbxLayerElement::EReferenceMode refMode;

						for(int layerNum = 0; layerNum < layerCount; ++layerNum)
						{
							FbxLayer *layer = fbxMesh->GetLayer(layerNum);					

							ParseNormals(layer, ctrlPointIdx, 0); //굳이 레이어 참조 안해도 되는듯
							ParseUV(layer, fbxMesh, ctrlPointIdx, polygonIdx, vertexIdx);
						}
					}
				}


				return true;
			}

			template <typename ElementType>
			bool ParseElements(ElementType* e, int ctrlPointIdx, int vertexCount)
			{
				if(e == nullptr)
					return false;

				int index = -1;
				FbxLayerElement::EMappingMode mappingMode = e->GetMappingMode();;
				FbxLayerElement::EReferenceMode refMode = e->GetReferenceMode();;

				if(mappingMode == FbxLayerElement::eByControlPoint)
				{
					if(refMode == FbxLayerElement::eDirect)
						index = ctrlPointIdx;
					else if(refMode == FbxLayerElement::eIndexToDirect)
						index = e->GetIndexArray().GetAt(ctrlPointIdx);
				}
				else if(mappingMode == FbxLayerElement::eByPolygonVertex)
				{
					if(refMode == FbxLayerElement::eDirect)
						index = vertexCount;
					else if(refMode == FbxLayerElement::eIndexToDirect)
						index = e->GetIndexArray().GetAt(vertexCount);
				}

				return index != -1;
			}

			bool ParseNormals(FbxLayer *layer, int ctrlPointIdx, int vertexCount)
			{
				return ParseElements<FbxLayerElementNormal>(layer->GetNormals(), ctrlPointIdx, vertexCount);
			}

			bool ParseUV(FbxLayer *layer, FbxMesh *fbxMesh, int ctrlPointIdx, int polygonIdx, int vertexIdx)
			{
				FbxLayerElementUV *fbxUV = layer->GetUVs();

				if(fbxUV == nullptr)
					return false;

				FbxLayerElement::EMappingMode mappingMode = fbxUV->GetMappingMode();;
				FbxLayerElement::EReferenceMode refMode = fbxUV->GetReferenceMode();;
				int index = -1;

				if(mappingMode == FbxLayerElement::eByControlPoint)
				{
					if(refMode == FbxLayerElement::eDirect)
						index = ctrlPointIdx;
					else if(refMode == FbxLayerElement::eIndexToDirect)
						index = fbxUV->GetIndexArray().GetAt(ctrlPointIdx);
				}
				else if(mappingMode == FbxLayerElement::eByPolygonVertex)
				{
					if(refMode == FbxLayerElement::eDirect || refMode == FbxLayerElement::eIndexToDirect)
						index = fbxMesh->GetTextureUVIndex(polygonIdx, vertexIdx);
				}

				return index != -1;
			}

			bool ParseVertexColor(FbxLayer *layer, int ctrlPointIdx, int vertexCount)
			{
				return ParseElements<FbxLayerElementVertexColor>(layer->GetVertexColors(), ctrlPointIdx, vertexCount);
			}

			bool ParseTangents(FbxLayer *layer, int ctrlPointIdx, int vertexCount)
			{
				return ParseElements<FbxLayerElementTangent>(layer->GetTangents(), ctrlPointIdx, vertexCount);
			}

			bool ParseBinomals(FbxLayer *layer, int ctrlPointIdx, int vertexCount)
			{
				return ParseElements<FbxLayerElementBinormal>(layer->GetBinormals(), ctrlPointIdx, vertexCount);
			}

			bool IsSkeleton(FbxNode *node)
			{
				FbxNodeAttribute *attribute = node->GetNodeAttribute();
				if(attribute == nullptr)
					return false;

				return (attribute->GetAttributeType() == FbxNodeAttribute::eSkeleton) &&
					(FbxCast<FbxSkeleton>(attribute)->GetSkeletonType() == FbxSkeleton::eLimbNode);
			}

			FbxNode* FindSkeletonRoot(FbxNode  *parent)
			{
				FbxNode *parentNode = parent->GetParent();

				if( IsSkeleton(parent) && parentNode != nullptr && IsSkeleton(parentNode) == false)
					return parent;

				int count = parent->GetChildCount();
				for(int i=0; i<count; ++i)
				{
					FbxNode *res = FindSkeletonRoot(parent->GetChild(i));

					if(res != nullptr)
						return res;
				}

				return nullptr;
			}

			void ParseBoneRecursive(const FbxNode* boneNode, int parentBoneIdx, std::vector<Animation::Bone*> *outBones)
			{
				Animation::Bone *bone = new Animation::Bone;

				bone->name = boneNode->GetName();
				bone->index = outBones->size();
				bone->indexParnet = parentBoneIdx;
				outBones->push_back(bone);

				int count = boneNode->GetChildCount();

				for(int i=0; i<count; ++i)
				{
					const FbxNode *child = boneNode->GetChild( i );
					ParseBoneRecursive( child, bone->index, outBones );
				}
			}

			bool ParseBone(FbxSkeleton *skeleton, std::vector<Animation::Bone*> *outBones)
			{
				if(skeleton == nullptr)
					return false;

				FbxNode *boneNode = skeleton->GetNode();
				ParseBoneRecursive(boneNode, -1, outBones);

				return true;
			}

			bool ParseTexture(FbxSurfaceMaterial *fbxMaterial, FbxProperty fbxProperty)
			{
				if( fbxProperty.IsValid() == false )
					return false;

				int textureCount = fbxProperty.GetSrcObjectCount(FbxTexture::ClassId);

				for(int i = 0; i < textureCount; ++i)
				{
					FbxFileTexture *tex = FbxCast<FbxFileTexture>(fbxProperty.GetSrcObject(FbxTexture::ClassId, i));

					if(tex == nullptr)
						continue;

					const char* fileName = tex->GetFileName();
					if( fileName == nullptr )
						continue;

					//texture name
					//textureAlpha = tex->GetAlphaSource();
					break;
				}

				return true;
			}

			bool ParseMaterialElements(FbxSurfaceMaterial *fbxMaterial)
			{
				FbxClassId id = fbxMaterial->GetClassId();

				std::pair<FbxPropertyT<FbxDouble3>, double> ambient, diffuse, emissive;
				double transparency;

				if(id.Is(FbxSurfacePhong::ClassId) == false)
				{
					FbxSurfacePhong *phong = static_cast<FbxSurfacePhong*>(fbxMaterial);

					FbxPropertyT<FbxDouble3> specular;
					double specularFactor;

					ambient.first = phong->Ambient;
					ambient.second = phong->AmbientFactor;

					diffuse.first = phong->Diffuse;
					diffuse.second = phong->DiffuseFactor;

					specular = phong->Specular;
					specularFactor = phong->SpecularFactor;

					emissive.first = phong->Emissive;
					emissive.second = phong->EmissiveFactor;

					transparency = phong->TransparencyFactor;
				}
				else if(id.Is(FbxSurfaceLambert::ClassId) == false)
				{
					FbxSurfaceLambert *lambert = static_cast<FbxSurfaceLambert*>(fbxMaterial);

					ambient.first = lambert->Ambient;
					ambient.second = lambert->AmbientFactor;

					diffuse.first = lambert->Diffuse;
					diffuse.second = lambert->DiffuseFactor;

					emissive.first = lambert->Emissive;
					emissive.second = lambert->EmissiveFactor;

					transparency = lambert->TransparencyFactor;
				}

				return true;
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