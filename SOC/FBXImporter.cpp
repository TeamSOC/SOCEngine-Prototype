#include "FBXImporter.h"

using namespace fbxsdk_2014_1;
#pragma warning( disable : 4244 )

namespace Rendering
{
	namespace Importer
	{
		FBXImporter::FBXImporter(FbxManager *manager)
		{
			this->manager = manager;
			scene = nullptr;
		}

		FBXImporter::~FBXImporter(void)
		{
			Destroy();
		}

		bool FBXImporter::Initialize(const char *sceneName)
		{
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

		bool FBXImporter::LoadScene(const char *fileName, const char *password)
		{
			int sdkMajor, sdkMinor, sdkRevision;

			//������ ������ȣ�� sdk�� ���� �����˴ϴ�?
			//Get the file version number generate by the FBX SDK
			FbxManager::GetFileFormatVersion(sdkMajor, sdkMinor, sdkRevision);

			//�����͸� �����մϴ�.
			FbxImporter* importer = FbxImporter::Create(manager, "");
			if(importer == nullptr)
				return false;

			FbxIOSettings *ioSetting = manager->GetIOSettings();
			ioSetting->SetBoolProp(IMP_FBX_MATERIAL,        true);
			ioSetting->SetBoolProp(IMP_FBX_TEXTURE,         true);
			ioSetting->SetBoolProp(IMP_FBX_LINK,            true);
			ioSetting->SetBoolProp(IMP_FBX_SHAPE,           true);
			ioSetting->SetBoolProp(IMP_FBX_GOBO,            true);
			ioSetting->SetBoolProp(IMP_FBX_ANIMATION,       true);
			ioSetting->SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);


			//���� �̸��� �����Ͽ� �����͸� �ʱ�ȭ ��ŵ�ϴ�.
			bool importStatus = importer->Initialize(fileName, -1, manager->GetIOSettings());
			if(importStatus == false)
			{
				FbxString error = importer->GetStatus().GetErrorString();
				// error ������, error Buffer��
			}

			//����� �뵵�̱� �ѵ�, �� ���� ������ �����״� �� ��
			//���� �����ְ���
			int fileMajor, fileMinor, fileRevision;
			importer->GetFileVersion(fileMajor, fileMinor, fileRevision);

			bool status = importer->Import(scene);
			if(status == false && 
				importer->GetStatus().GetCode() == FbxStatus::ePasswordError)
			{
				//�н����尡 �ʿ��Դϴ�? ����
				FbxString str(password);
				manager->GetIOSettings()->SetStringProp(IMP_FBX_PASSWORD, str);
				manager->GetIOSettings()->SetBoolProp(IMP_FBX_PASSWORD_ENABLE, true);

				status = importer->Import(scene);

				FbxStatus::EStatusCode code = importer->GetStatus().GetCode();
				if(code == FbxStatus::ePasswordError)
					return false;//����� �뵵
			}

			importer->Destroy();

			return status;
		}

		bool FBXImporter::Decode(MaterialElements *outMaterialElements, VertexBufferElements *outMeshFliterElements, MaterialTextures *outTextureNames)
		{
			if(scene == nullptr)
				return false;

			FbxNode *rootNode = scene->GetRootNode();
			int childCount = rootNode->GetChildCount();

			FbxMesh *fbxMesh		 = nullptr;
			FbxSkeleton *fbxSkeleton = nullptr;

			for(int childIdx = 0; childIdx < childCount; ++childIdx)
			{
				FbxNode *childNode = rootNode->GetChild(childIdx);
				FbxNodeAttribute *nodeAttribute = childNode->GetNodeAttribute();

				if(nodeAttribute == nullptr)
					continue;

				FbxNodeAttribute::EType attributeType = nodeAttribute->GetAttributeType();

				if(attributeType == FbxNodeAttribute::eMesh)
					fbxMesh = childNode->GetMesh();
				else if(attributeType == FbxNodeAttribute::eSkeleton)
					fbxSkeleton = childNode->GetSkeleton();

				if(fbxMesh != nullptr && fbxSkeleton != nullptr)
					break;
			}

			if(fbxSkeleton == nullptr)
			{
				FbxNode *skeletonNode = FindSkeletonRoot(rootNode);
				if(skeletonNode != nullptr)
					fbxSkeleton = skeletonNode->GetSkeleton();
			}

			BuildMesh(fbxMesh, outMeshFliterElements, outMaterialElements, outTextureNames);

			bool animation = 0;

			if( /*animation*/ true)
			{

				BuildSkeleton(fbxSkeleton, nullptr);
			}

			return true;
		}

		bool FBXImporter::BuildMesh(FbxMesh *fbxMesh, VertexBufferElements *outMeshFilterElements, MaterialElements *outMaterialElements, MaterialTextures *outTextures)
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

			int numOfVertex = fbxMesh->GetControlPointsCount();
			outMeshFilterElements->indices.first = polygonCount * 3;
			outMeshFilterElements->indices.second = new SOC_word[polygonCount * 3];
			outMeshFilterElements->numOfVertex = numOfVertex;
			outMeshFilterElements->vertices = new SOC_Vector3[outMeshFilterElements->numOfVertex];
			outMeshFilterElements->numOfTriangle = fbxMesh->GetPolygonCount();
			outMeshFilterElements->isDynamic = isSkinned;

			if(fbxMesh->GetLayer(0)->GetNormals() != nullptr)
				outMeshFilterElements->normals = new SOC_Vector3[numOfVertex];

			if(fbxMesh->GetLayer(0)->GetVertexColors() != nullptr)
				outMeshFilterElements->colors = new Color[numOfVertex];

			if(fbxMesh->GetLayer(0)->GetBinormals() != nullptr)
				outMeshFilterElements->binomals = new SOC_Vector3[numOfVertex];

			if(fbxMesh->GetLayer(0)->GetTangents() != nullptr)
				outMeshFilterElements->tangents = new SOC_Vector3[numOfVertex];

			outMeshFilterElements->texcoords.second = new SOC_Vector2*[layerCount];
			for(int i=0; i<layerCount; ++i)
				outMeshFilterElements->texcoords.second[i] = new SOC_Vector2[numOfVertex];

			if(fbxMesh->GetLayerCount() > 0)
			{
				outMeshFilterElements->texcoords.first = fbxMesh->GetLayerCount();
				outMeshFilterElements->texcoords.second[0];
			}

			outMeshFilterElements->type = SOC_TRIANGLE::SOC_TRIANGLE_LIST;
			//��Ʈ�� ��

			SOC_word *indices = outMeshFilterElements->indices.second;
			SOC_Vector3 *vertices = outMeshFilterElements->vertices;
			SOC_Vector3 *normals = outMeshFilterElements->normals;
			SOC_Vector3 *binormals = outMeshFilterElements->binomals;
			SOC_Vector3 *tangents = outMeshFilterElements->tangents;
			Color *colors = outMeshFilterElements->colors;
			SOC_Vector2 **texcoords = outMeshFilterElements->texcoords.second;

			for(int polygonIdx = 0; polygonIdx < polygonCount; ++polygonIdx)
			{
				int polygonSize = fbxMesh->GetPolygonSize(polygonIdx);					

				//���ʿ� �ﰢ���� �ƴϸ� ���ƹ�����
				if(polygonSize != 3)
					return false;

				for(int vertexIdx = 0; vertexIdx < polygonSize; ++vertexIdx)
				{
					int ctrlPointIdx = fbxMesh->GetPolygonVertex(polygonIdx, vertexIdx);
					//�̳��� index�ε�..
					indices[vertexCount] = ctrlPointIdx;

					FbxVector4 ctrl = ctrlPoints[ctrlPointIdx];

					vertices[vertexCount] = SOC_Vector3((float)ctrl[0], (float)ctrl[1], (float)ctrl[2]);
					//ctrl�� vertex��, skinned�������� vertex�� boneIdx�� �ְ�!
					if(isSkinned)
					{
						//add born Index.
						outMeshFilterElements->boneIndices.push_back(boneIndices[ctrlPointIdx]);
					}

					for(int layerNum = 0; layerNum < layerCount; ++layerNum)
					{
						FbxLayer *layer = fbxMesh->GetLayer(layerNum);		

						if( texcoords )
							ParseUV(layer, fbxMesh, ctrlPointIdx, polygonIdx, vertexIdx, &texcoords[layerNum][vertexCount]);
					}
					//����.. ���࿡ ���߿� ����ִٸ� �׳༮�� ��ŵ�ϰ� �׾���߳�
					//�� ������ ���ݾ� ������ � ���ϸ� ���� �� ��

					//������ 0�� ���̾ ����.  ���� ���� ���̾ ���� �ʴ´ٰ� �Ѵ�.
					FbxLayer *layer = fbxMesh->GetLayer(0);

					if(normals)
						ParseNormals(layer, ctrlPointIdx, vertexCount, &normals[vertexCount]);

					if(binormals)
						ParseBinormals(layer, ctrlPointIdx, vertexCount, &binormals[vertexCount]);

					if(tangents)
						ParseTangents(layer, ctrlPointIdx, vertexCount, &tangents[vertexCount]);

					if(colors)
						ParseVertexColor(layer, ctrlPointIdx, vertexCount, &colors[vertexCount]);

					++vertexCount;
					//���� ���׸����� ���ؽ� ���� �� �ʿ䰡 �����ʳ�
					//�� ���� ������ �� �� �󸶳� �������ڴٰ� ��
				}

			}

			//				outMeshFilterElements->numOfVertex = vertexCount;

			FbxNode *node = fbxMesh->GetNode();
			int materialCount = node->GetSrcObjectCount<FbxSurfaceMaterial>();
			for(int materialIdx = 0; materialIdx < materialCount; materialIdx)
			{
				FbxSurfaceMaterial *fbxMaterial = FbxCast<FbxSurfaceMaterial>(node->GetSrcObject<FbxSurfaceMaterial>(materialIdx));

				if(fbxMaterial == nullptr)
					continue;

				ParseMaterialElements(fbxMaterial, outMaterialElements);

				FbxProperty fbxProperty;

				fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
				ParseTexture(fbxProperty, &outTextures->diffuse);

				fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sEmissive);
				ParseTexture(fbxProperty, &outTextures->emissive);

				fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sSpecular);
				ParseTexture(fbxProperty, &outTextures->specular);

				fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sSpecularFactor);
				ParseTexture(fbxProperty, &outTextures->specularFactor);

				fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sBump);
				ParseTexture(fbxProperty, &outTextures->bump);

				fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sBumpFactor);
				ParseTexture(fbxProperty, &outTextures->bumpFactor);

				fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sTransparentColor);
				ParseTexture(fbxProperty, &outTextures->transparentColor);
			}

			return true;
		}

		void FBXImporter::BuildskinningMesh(FbxMesh *fbxMesh, std::vector<int> &boneIndices)
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

		bool FBXImporter::ParseNormals(FbxLayer *layer, int ctrlPointIdx, int vertexCount, SOC_Vector3 *out)
		{
			int index = -1;
			bool res = ParseElements(layer->GetNormals(), ctrlPointIdx, vertexCount, &index);

			if(res)
			{
				FbxLayerElementNormal *fbxNormal = layer->GetNormals();
				FbxVector4 v = fbxNormal->GetDirectArray().GetAt(index);
				(*out) = SOC_Vector3((float)v[0], (float)v[1], (float)v[2]);
			}

			return res;
		}

		bool FBXImporter::ParseUV(FbxLayer *layer, FbxMesh *fbxMesh, int ctrlPointIdx, int polygonIdx, int vertexIdx, SOC_Vector2 *out)
		{
			FbxLayerElementUV *fbxUV = layer->GetUVs();

			if(fbxUV == nullptr)
				return false;

			int index = -1;

			{
				FbxLayerElement::EMappingMode mappingMode = fbxUV->GetMappingMode();;
				FbxLayerElement::EReferenceMode refMode = fbxUV->GetReferenceMode();;

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
			}

			if(index != -1)
			{
				FbxVector2 v = fbxUV->GetDirectArray().GetAt(index);
				(*out) = SOC_Vector2((float)v[0], (float)v[1]);
			}

			return index != -1;
		}

		bool FBXImporter::ParseVertexColor(FbxLayer *layer, int ctrlPointIdx, int vertexCount, Color *out)
		{
			int index = -1;
			bool res = ParseElements(layer->GetVertexColors(), ctrlPointIdx, vertexCount, &index);

			if(res)
			{
				FbxLayerElementVertexColor *fbxColor = layer->GetVertexColors();
				FbxColor v = fbxColor->GetDirectArray().GetAt(index);
				(*out) = Color(v.mRed, v.mGreen, v.mBlue, v.mAlpha);
			}

			return res;
		}

		bool FBXImporter::ParseTangents(FbxLayer *layer, int ctrlPointIdx, int vertexCount, SOC_Vector3 *out)
		{
			int index = -1;
			bool res = ParseElements(layer->GetTangents(), ctrlPointIdx, vertexCount, &index);

			if(res)
			{
				FbxLayerElementTangent *fbxTangent = layer->GetTangents();
				FbxVector4 v = fbxTangent->GetDirectArray().GetAt(index);
				(*out) = SOC_Vector3((float)v[0], (float)v[1], (float)v[2]);
			}

			return res;
		}

		bool FBXImporter::ParseBinormals(FbxLayer *layer, int ctrlPointIdx, int vertexCount, SOC_Vector3 *out)
		{
			int index = -1;
			bool res = ParseElements<FbxLayerElementBinormal>(layer->GetBinormals(), ctrlPointIdx, vertexCount, &index);

			if(res)
			{
				FbxLayerElementBinormal *fbxBinormal = layer->GetBinormals();
				FbxVector4 v = fbxBinormal->GetDirectArray().GetAt(index);
				(*out) = SOC_Vector3((float)v[0], (float)v[1], (float)v[2]);
			}

			return res;
		}

		bool FBXImporter::IsSkeleton(FbxNode *node)
		{
			FbxNodeAttribute *attribute = node->GetNodeAttribute();
			if(attribute == nullptr)
				return false;

			return (attribute->GetAttributeType() == FbxNodeAttribute::eSkeleton) &&
				(FbxCast<FbxSkeleton>(attribute)->GetSkeletonType() == FbxSkeleton::eLimbNode);
		}

		FbxNode* FBXImporter::FindSkeletonRoot(FbxNode  *parent)
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

		void FBXImporter::ParseBoneRecursive(const FbxNode* boneNode, int parentBoneIdx, std::vector<Animation::Bone*> *outBones)
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

		bool FBXImporter::BuildSkeleton(FbxSkeleton *skeleton, std::vector<Animation::Bone*> *outBones)
		{
			if(skeleton == nullptr)
				return false;

			FbxNode *boneNode = skeleton->GetNode();
			ParseBoneRecursive(boneNode, -1, outBones);

			return true;
		}

		bool FBXImporter::ParseTexture(FbxProperty &fbxProperty, std::string* outFileName)
		{
			if( fbxProperty.IsValid() == false )
				return false;

			//������ �ؽ��Ĵ� 1����..
			if(fbxProperty.GetSrcObjectCount<FbxSurfaceMaterial>() != 0) 
				return false;

			int textureCount = fbxProperty.GetSrcObjectCount<FbxSurfaceMaterial>();

			//������ �ؽ��Ĵ� 1����..
			if( textureCount == 1 )
			{
				FbxFileTexture *texture = FbxCast<FbxFileTexture>(fbxProperty.GetSrcObject<FbxSurfaceMaterial>());
				const char *textureFileName = texture->GetFileName();
				*outFileName = textureFileName;
			}

			return true;
		}

		bool FBXImporter::ParseMaterialElements(FbxSurfaceMaterial *fbxMaterial, MaterialElements *out)
		{
			FbxClassId id = fbxMaterial->GetClassId();

			std::pair<FbxDouble3, double> ambient, diffuse, emissive;
			double transparency;

			if(id.Is(FbxSurfacePhong::ClassId) == false)
			{
				FbxSurfacePhong *phong = static_cast<FbxSurfacePhong*>(fbxMaterial);

				FbxDouble3 specular;
				double specularFactor;

				ambient.first = phong->Ambient.Get();
				ambient.second = phong->AmbientFactor;

				diffuse.first = phong->Diffuse.Get();
				diffuse.second = phong->DiffuseFactor;

				specular = phong->Specular.Get();
				specularFactor = phong->SpecularFactor;

				emissive.first = phong->Emissive.Get();
				emissive.second = phong->EmissiveFactor;

				transparency = phong->TransparencyFactor;

				out->specularColor = Color(specular[0], specular[1], specular[2]) * specularFactor;
			}
			else if(id.Is(FbxSurfaceLambert::ClassId) == false)
			{
				FbxSurfaceLambert *lambert = static_cast<FbxSurfaceLambert*>(fbxMaterial);

				ambient.first = lambert->Ambient.Get();
				ambient.second = lambert->AmbientFactor;

				diffuse.first = lambert->Diffuse.Get();
				diffuse.second = lambert->DiffuseFactor;

				emissive.first = lambert->Emissive.Get();
				emissive.second = lambert->EmissiveFactor;

				transparency = lambert->TransparencyFactor;
			}


			out->ambientColor = Color(ambient.first[0], ambient.first[1], ambient.first[2]) * ambient.second;
			out->diffuseColor = Color(diffuse.first[0], diffuse.first[1], diffuse.first[2]) * diffuse.second;
			out->emissive = Color(emissive.first[0], emissive.first[1], emissive.first[2]) * emissive.second;
			out->transparentFactor = transparency;

			return true;
		}

		void FBXImporter::Destroy()
		{
			if(scene)
			{
				scene->Destroy();
				scene = nullptr;
			}
		}
	}
}