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
				
				if(fbxMesh->GetControlPointsCount() == 0)
					return false;

				const char *meshName = fbxMesh->GetNameOnly();

				FbxVector4 *ctrlPoints	= fbxMesh->GetControlPoints();
				int layerCount			= fbxMesh->GetLayerCount();
				int polygonCount		= fbxMesh->GetPolygonCount();
				int vertexCount			= 0;

				std::vector<int> boneIndices;
				BuildskinningMesh(fbxMesh, boneIndices);
				bool isSkinned = boneIndices.empty() == false;

				for(int polygonIdx = 0; polygonIdx < polygonCount; ++polygonIdx)
				{
					int polygonSize = fbxMesh->GetPolygonSize(polygonIdx);					

					//애초에 삼각형이 아니면 막아버리자
					if(polygonSize != 3)
						return false;

					for(int vertexIdx = 0; vertexIdx < polygonSize; ++vertexIdx)
					{
						int ctrlPointIdx = fbxMesh->GetPolygonVertex(polygonIdx, vertexIdx);						
						FbxVector4 ctrl = ctrlPoints[ctrlPointIdx];

						//ctrl이 vertex고, skinned가있으면 vertex의 boneIdx에 넣고!

						for(int layerNum = 0; layerNum < layerCount; ++layerNum)
						{
							FbxLayer *layer = fbxMesh->GetLayer(layerNum);		

							ParseUV(layer, fbxMesh, ctrlPointIdx, polygonIdx, vertexIdx);
						}

						//게임은 0번 레이어만 쓴다.  굳이 다중 레이어를 쓰지 않는다고 한다.
						FbxLayer *layer = fbxMesh->GetLayer(0);
						ParseNormals(layer, ctrlPointIdx, vertexCount);
						ParseBinomals(layer, ctrlPointIdx, vertexCount);
						ParseTangents(layer, ctrlPointIdx, vertexCount);
						ParseVertexColor(layer, ctrlPointIdx, vertexCount);

						++vertexCount;
						//굳이 메테리얼은 버텍스 마다 돌 필요가 없지않나
						//걍 따로 빼주지 뭐 ㅇ 얼마나 느려지겠다고 ㅋ
					}
					
				}

				FbxNode *node = fbxMesh->GetNode();
				int materialCount = node->GetSrcObjectCount(FbxSurfaceMaterial::ClassId);
				for(int materialIdx = 0; materialIdx < materialCount; materialIdx)
				{
					FbxSurfaceMaterial *fbxMaterial = FbxCast<FbxSurfaceMaterial>(node->GetSrcObject(FbxSurfaceMaterial::ClassId, materialIdx));

					if(fbxMaterial == nullptr)
						continue;

					ParseMaterialElements(fbxMaterial);

					FbxProperty fbxProperty;
					fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
					ParseTexture(fbxProperty);

					fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sEmissive);
					ParseTexture(fbxProperty);

					fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sSpecular);
					ParseTexture(fbxProperty);

					fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sSpecularFactor);
					ParseTexture(fbxProperty);

					fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sBump);
					ParseTexture(fbxProperty);

					fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sBumpFactor);
					ParseTexture(fbxProperty);

					fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sTransparentColor);
					ParseTexture(fbxProperty);					
				}

				return true;
			}

			void BuildskinningMesh(FbxMesh *fbxMesh, std::vector<int> &boneIndices)
			{
				int skinCount = fbxMesh->GetDeformerCount(FbxDeformer::eSkin);

				if(skinCount > 0)
					boneIndices.resize(fbxMesh->GetControlPointsCount(), -1);

				for(int skinIdx = 0; skinIdx < skinCount; ++skinIdx)
				{
					FbxSkin *fbxSkin = FbxCast<FbxSkin>(fbxMesh->GetDeformer(skinIdx, FbxDeformer::eSkin));

					int clusterCount = fbxSkin->GetClusterCount();
					if( clusterCount == 0 )
						continue;

					for(int clusterIdx = 0; clusterIdx < clusterCount; ++clusterIdx)
					{
						FbxCluster *fbxCluster = fbxSkin->GetCluster(clusterIdx);
						FbxNode *bone = fbxCluster->GetLink();

						if( bone == nullptr )
							continue;

						int numInfluencedVertices = fbxCluster->GetControlPointIndicesCount();
						
						int *indexAry = fbxCluster->GetControlPointIndices();
						double *weightAry = fbxCluster->GetControlPointWeights();

						for(int ctrlPointIdx = 0; ctrlPointIdx < numInfluencedVertices; ++ctrlPointIdx)
						{
							int index = indexAry[ctrlPointIdx];
							int boneIndex = boneIndices[index];

							boneIndices[index] = clusterIdx;
						}
					}
				}
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

			bool ParseTexture(FbxProperty &fbxProperty)
			{
				if( fbxProperty.IsValid() == false )
					return false;

				//무조건 텍스쳐는 1개만..
				if(fbxProperty.GetSrcObjectCount(FbxLayeredTexture::ClassId) != 0) 
					return false;

				int textureCount = fbxProperty.GetSrcObjectCount(FbxTexture::ClassId);

				//무조건 텍스쳐는 1개만..
				if( textureCount == 1 )
				{
					FbxFileTexture *texture = FbxCast<FbxFileTexture>(fbxProperty.GetSrcObject(FbxTexture::ClassId));
					const char *textureFileName = texture->GetFileName();
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