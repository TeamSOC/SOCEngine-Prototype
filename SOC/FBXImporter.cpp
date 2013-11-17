#include "FBXImporter.h"
#include "Scene.h"
#include "ResourcesFolder.h"

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

//#if defined(WIN32) && !defined(_USE_GL_DEFINES)
//
//			FbxAxisSystem axis = FbxAxisSystem::DirectX;
//
//#elif defined(__APPLE__) || defined(_USE_GL_DEFINES)
//
//			FbxAxisSystem axis = FbxAxisSystem::OpenGL;
//
//#endif
//
//			axis.ConvertScene(scene);

			return scene != nullptr;
		}

		bool FBXImporter::LoadScene(const char *fileName, bool inResourcesFolder, const char *password)
		{
			int sdkMajor, sdkMinor, sdkRevision;

			//파일의 버젼번호는 sdk에 의해 생성됩니다?
			//Get the file version number generate by the FBX SDK
			FbxManager::GetFileFormatVersion(sdkMajor, sdkMinor, sdkRevision);

			//임포터를 생성합니다.
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

			//파일 이름을 제공하여 임포터를 초기화 시킵니다.

			std::string &path = Utility::ResourcesFolder::GetPath(fileName);

			bool importStatus = importer->Initialize(path.data(), -1, manager->GetIOSettings());
			if(importStatus == false)
			{
				FbxString error = importer->GetStatus().GetErrorString();
				// error 내용은, error Buffer에
			}

			//디버깅 용도이긴 한데, 뭐 굳이 느리진 않을테니 걍 둠
			//누가 지워주겠지
			int fileMajor, fileMinor, fileRevision;
			importer->GetFileVersion(fileMajor, fileMinor, fileRevision);

			bool status = importer->Import(scene);
			if(status == false && 
				importer->GetStatus().GetCode() == FbxStatus::ePasswordError)
			{
				//패스워드가 필요함니다? 내놔
				FbxString str(password);
				manager->GetIOSettings()->SetStringProp(IMP_FBX_PASSWORD, str);
				manager->GetIOSettings()->SetBoolProp(IMP_FBX_PASSWORD_ENABLE, true);

				status = importer->Import(scene);

				FbxStatus::EStatusCode code = importer->GetStatus().GetCode();
				if(code == FbxStatus::ePasswordError)
					return false;//디버깅 용도
			}

			importer->Destroy();

			return status;
		}

		void FBXImporter::BuildSkeleton(Object *parent, FbxNode *node)
		{
			//뭔가 좀 부실한데..
			//FbxSkeleton *fbxSkeleton = node->GetSkeleton();

		}

		void FBXImporter::CreateMeshComponent(Object *obj, FbxNode *node)
		{
			FbxMesh *fbxMesh = node->GetMesh();
			Mesh::Mesh *mesh = obj->AddComponent<Mesh::Mesh>();

			Scene *scene = dynamic_cast<Scene*>(Device::DeviceDirector::GetInstance()->GetScene());
			MeshDataManager *mgr = scene->GetMeshDataMgr();

			/*material*/
			const char *key = node->GetName();
			MeshDatas *meshData = mgr->Find(key);

			Intersection::AABB bound;
			float radius;

			if(meshData == nullptr)
			{
				meshData = new MeshDatas;

				BuildMesh(fbxMesh, &meshData->vb, &bound, &radius);
				ParseMaterial(fbxMesh, &meshData->material, &meshData->textureNames);

				meshData->radius = radius;
				meshData->aabb = bound;

				mgr->Add(key, meshData);
			}
			else
			{
				bound = meshData->aabb;
				radius = meshData->radius;
			}

			mesh->Create(meshData);

			obj->GetTransform()->SetRadius(radius);
			obj->GetTransform()->SetBound(bound);

			SetFbxTransform(obj, node);
		}

		void FBXImporter::SetFbxTransform(Object *obj, FbxNode *node)
		{
			Transform *transform = obj->GetTransform();

			FbxDouble3 p, s, r;
			p = node->LclTranslation.Get();
			s = node->LclScaling.Get();
			r = node->LclRotation.Get();

			transform->SetPosition(SOC_Vector3((float)p[0], (float)p[1], (float)p[2]));
			transform->SetEulerAngles(SOC_Vector3((float)r[0], (float)r[1], (float)r[2]));
			transform->SetScale(SOC_Vector3((float)s[0], (float)s[1], (float)s[2]));
		}

		Object* FBXImporter::BuildObject(Object *parent)
		{
			FbxNode *rootNode = scene->GetRootNode();
			int childCount = rootNode->GetChildCount();

			Object *rootObject = new Object(parent);

			for(int i=0; i<childCount; ++i)
				Decode(rootObject, rootNode->GetChild(i));

			return rootObject;
		}

		//애가 재귀형이니까, 아닌곳에서 얘 좀 호출해줘야해
		Object* FBXImporter::Decode(Object *parent, FbxNode *fbxNode)
		{
			FbxNodeAttribute *fbxNodeAttri = fbxNode->GetNodeAttribute();

			if(fbxNodeAttri == nullptr)
				return nullptr;

			FbxNodeAttribute::EType atType = fbxNodeAttri->GetAttributeType();
			Object *obj = new Object(parent);
			obj->name = fbxNode->GetName() ? fbxNode->GetName() : "None Node";
			SetFbxTransform(obj, fbxNode);

			if(parent->Has(obj) == false)
				parent->Add(obj, false);

			if(atType == FbxNodeAttribute::eMesh)
				CreateMeshComponent(obj, fbxNode);
			else if(atType == FbxNodeAttribute::eSkeleton)
				BuildSkeleton(obj, fbxNode);

			int childCount = fbxNode->GetChildCount();
			for(int i=0; i<childCount; ++i)
				Decode(obj, fbxNode->GetChild(i));

			return obj;
		}

		bool FBXImporter::BuildMesh(FbxMesh *fbxMesh, Mesh::VBElements *outVBElements, Intersection::AABB *outBounds, float *outRadius)
		{
			if(fbxMesh == nullptr)
				return false;

			if(fbxMesh->GetControlPointsCount() == 0)
				return false;

			FbxVector4 *ctrlPoints	= fbxMesh->GetControlPoints();
			int layerCount			= fbxMesh->GetLayerCount();
			int polygonCount		= fbxMesh->GetPolygonCount();

			//std::vector<int> skinIndices;
			//BuildskinningMesh(fbxMesh, skinIndices);
			//bool isSkinned = skinIndices.empty() == false;

			//if(isSkinned)
			//{
			//	outVBElements->skinIndices.first = skinIndices.size();
			//	outVBElements->skinIndices.second = new int[skinIndices.size()];
			//}

			int indexCount =  0;

			for(int i=0; i<polygonCount; ++i)
			{
				int polySize = fbxMesh->GetPolygonSize(i);

				if( polySize == 3 )					indexCount += 3;
				else if(polySize == 4)				indexCount += 6;
				else 
					return false;
			}

			int numOfVertex = fbxMesh->GetControlPointsCount();
			outVBElements->indices.first = indexCount;
			outVBElements->indices.second = new SOC_word[indexCount];
			outVBElements->numOfVertex = numOfVertex;
			outVBElements->vertices = new SOC_Vector3[outVBElements->numOfVertex];
			outVBElements->numOfTriangle = indexCount / 3;
			outVBElements->isDynamic = false;

			//FbxGeometryElementNormal *fgn = fbxMesh->GetElementNormal(0);
			//FbxLayerElementNormal *gln = fbxMesh->GetLayer(0)->GetNormals();

			//int test = 0;
			//test = fbxMesh->GetElementNormalCount();
			//test = fbxMesh->GetElementUVCount();
			//test = fbxMesh->GetElementBinormalCount();
			//test = fbxMesh->GetElementTangentCount();

			if(fbxMesh->GetElementNormal() != nullptr)
				outVBElements->normals = new SOC_Vector3[numOfVertex];

			if(fbxMesh->GetLayer(0)->GetVertexColors() != nullptr)
				outVBElements->colors = new Color[numOfVertex];

			if(fbxMesh->GetLayer(0)->GetBinormals() != nullptr)
				outVBElements->binormals = new SOC_Vector3[numOfVertex];

			if(fbxMesh->GetLayer(0)->GetTangents() != nullptr)
				outVBElements->tangents = new SOC_Vector3[numOfVertex];

			if(fbxMesh->GetLayerCount() > 0)
			{
				outVBElements->texcoords.second = new SOC_Vector2*[layerCount];

				for(int i=0; i<layerCount; ++i)
					outVBElements->texcoords.second[i] = new SOC_Vector2[numOfVertex];

				outVBElements->texcoords.first = fbxMesh->GetLayerCount();
			}

			outVBElements->type = SOC_TRIANGLE::SOC_TRIANGLE_LIST;
			//스트립 ㅗ

			SOC_word *indices = outVBElements->indices.second;
			SOC_Vector3 *vertices = outVBElements->vertices;
			SOC_Vector3 *normals = outVBElements->normals;
			SOC_Vector3 *binormals = outVBElements->binormals;
			SOC_Vector3 *tangents = outVBElements->tangents;
			Color *colors = outVBElements->colors;
			SOC_Vector2 **texcoords = outVBElements->texcoords.second;

			//bool check[2009];
			//ZeroMemory(check, sizeof(bool) * 2009);

			int skinIdx		= 0;

			float radius = 0.0f, maxRadius = 0.0f;

			SOC_Vector3 minSize(0, 0, 0), maxSize(0, 0, 0);
			for(int i=0; i<numOfVertex; ++i)
			{
				FbxVector4  v = fbxMesh->GetControlPointAt(i);
				vertices[i] = SOC_Vector3((float)v[0], (float)v[1], -(float)v[2]);

				radius = SOCVec3Length(&vertices[i]);

				if( maxRadius < radius )
					maxRadius = radius;

				for(int j=0; j<3; ++j)
				{
					if(minSize[j] > vertices[i][j])	minSize[j] = vertices[i][j];
					else if(maxSize[j] < vertices[i][j]) maxSize[j] = vertices[i][j];
				}
			}

			if(outRadius)
				(*outRadius) = maxRadius;
			if(outBounds)
				outBounds->SetMinMax(minSize, maxSize);

			int vertexCount = 0;
			for(int polyIdx = 0; polyIdx < polygonCount; ++polyIdx)
			{
				int polySize = fbxMesh->GetPolygonSize(polyIdx);

				for(int i=0; i<polySize; ++i)
				{
					int ctrlIdx = fbxMesh->GetPolygonVertex(polyIdx, i);					

					for(int layerIdx = 0; layerIdx < layerCount; ++layerIdx)
					{
						FbxLayer *layer = fbxMesh->GetLayer(layerIdx);

						if(layer)
							ParseUV(layer, fbxMesh, ctrlIdx, polyIdx, vertexCount, i, &texcoords[layerIdx][ctrlIdx]);
					}

					FbxLayer *layer = fbxMesh->GetLayer(0);

					if(normals)
						ParseNormals(layer, ctrlIdx, vertexCount, &normals[ctrlIdx]);

					if(binormals)
						ParseBinormals(layer, ctrlIdx, vertexCount, &binormals[ctrlIdx]);

					if(tangents)
						ParseTangents(layer, ctrlIdx, vertexCount, &tangents[ctrlIdx]);

					if(colors)
						ParseVertexColor(layer, ctrlIdx, vertexCount, &colors[ctrlIdx]);

					vertexCount++;
				}
			}

			int triangleAry[3] = { 0, 1, 2 };
			int rectAry[6] = { 0, 1, 2, 0, 2, 3 };
			int *ary = nullptr;

			int index = 0;
			for(int polygonIdx = 0; polygonIdx < polygonCount; ++polygonIdx)
			{
				int polygonSize = fbxMesh->GetPolygonSize(polygonIdx);					

				ary = polygonSize == 3 ? triangleAry : rectAry;
				int count = polygonSize == 3 ? 3 : 6;

				for(int vertexIdx = 0; vertexIdx < count; ++vertexIdx)
				{
					indices[index] = fbxMesh->GetPolygonVertex(polygonIdx, ary[vertexIdx]);

					//skin mesh??

					++index;
				}
			}

			return true;
		}

		void FBXImporter::ParseMaterial(fbxsdk_2014_1::FbxMesh *fbxMesh, Material::MaterialElements *outMaterialElements, MeshTextureNames *outTextureNames)
		{
			FbxNode *node = fbxMesh->GetNode();

			int materialCount = node->GetMaterialCount();
			for(int materialIdx = 0; materialIdx < materialCount; ++materialIdx)
			{
				FbxSurfaceMaterial *fbxMaterial = node->GetMaterial(materialIdx);

				if(fbxMaterial == nullptr)
					continue;

				ParseMaterialElements(fbxMaterial, outMaterialElements);

				FbxProperty fbxProperty;

				fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
				ParseTexture(fbxProperty, &outTextureNames->diffuse);

				fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sEmissive);
				ParseTexture(fbxProperty, &outTextureNames->emissive);

				fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sSpecular);
				ParseTexture(fbxProperty, &outTextureNames->specular);

				fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sSpecularFactor);
				ParseTexture(fbxProperty, &outTextureNames->specularFactor);

				fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sBump);
				ParseTexture(fbxProperty, &outTextureNames->bump);

				fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sBumpFactor);
				ParseTexture(fbxProperty, &outTextureNames->bumpFactor);

				fbxProperty = fbxMaterial->FindProperty(FbxSurfaceMaterial::sTransparentColor);
				ParseTexture(fbxProperty, &outTextureNames->transparent);
			}


		}

		void FBXImporter::BuildskinningMesh(FbxMesh *fbxMesh, std::vector<int> &boneIndices)
		{
			int skinCount = fbxMesh->GetDeformerCount(FbxDeformer::eSkin);

			if(skinCount > 0)
				boneIndices.resize(fbxMesh->GetControlPointsCount());

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

		bool FBXImporter::ParseNormals(FbxLayer *layer, int ctrlPointIdx, int vertexIdx, SOC_Vector3 *out)
		{
			int index = -1;
			bool res = ParseElements(layer->GetNormals(), ctrlPointIdx, vertexIdx, &index);

			if(res)
			{				
				FbxLayerElementNormal *fbxNormal = layer->GetNormals();
				FbxVector4 v = fbxNormal->GetDirectArray().GetAt(index);
				v.Normalize();
				(*out) = SOC_Vector3((float)v[0], (float)v[1], -(float)v[2]);
			}

			return res;
		}

		bool FBXImporter::ParseUV(FbxLayer *layer, FbxMesh *fbxMesh, int ctrlPointIdx, int polygonIdx, int vertexIdx, int pointIdx, SOC_Vector2 *out)
		{
			FbxLayerElementUV *fbxUV = layer->GetUVs();

			if(fbxUV == nullptr)
				return false;

			int index = -1;

			{
				FbxLayerElement::EMappingMode mappingMode = fbxUV->GetMappingMode();
				FbxLayerElement::EReferenceMode refMode = fbxUV->GetReferenceMode();

				if(mappingMode == FbxLayerElement::eByControlPoint)
				{
					if(refMode == FbxLayerElement::eDirect)
						index = ctrlPointIdx;
					else if(refMode == FbxLayerElement::eIndexToDirect)
						index = fbxUV->GetIndexArray().GetAt(ctrlPointIdx);
				}
				else if(mappingMode == FbxLayerElement::eByPolygonVertex)
				{
					if(refMode == FbxLayerElement::eDirect)
						index = vertexIdx;
					else if(refMode == FbxLayerElement::eIndexToDirect)
						index = fbxMesh->GetTextureUVIndex(polygonIdx, pointIdx);
				}
			}

			if(index != -1)
			{
				FbxVector2 v = fbxUV->GetDirectArray().GetAt(index);
				(*out) = SOC_Vector2((float)v[0], 1.0f - (float)v[1]);
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
			bool res = ParseElements(layer->GetBinormals(), ctrlPointIdx, vertexCount, &index);

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


		bool FBXImporter::ParseTexture(FbxProperty &fbxProperty, std::string* outFileName)
		{
			if( fbxProperty.IsValid() == false )
				return false;

			//무조건 텍스쳐는 1개만..
			if(fbxProperty.GetSrcObjectCount<FbxSurfaceMaterial>() != 0) 
				return false;

			int textureCount = fbxProperty.GetSrcObjectCount<FbxSurfaceMaterial>();

			//무조건 텍스쳐는 1개만..
			if( textureCount == 1 )
			{
				FbxFileTexture *texture = FbxCast<FbxFileTexture>(fbxProperty.GetSrcObject<FbxSurfaceMaterial>());
				const char *textureFileName = texture->GetFileName();
				*outFileName = textureFileName;
			}

			return true;
		}

		bool FBXImporter::ParseMaterialElements(FbxSurfaceMaterial *fbxMaterial, Material::MaterialElements *out)
		{
			FbxClassId id = fbxMaterial->GetClassId();

			std::pair<FbxDouble3, double> ambient, diffuse, emissive;
			double transparency = 1.0f;
			double shininess = 0.0f;

			if(id.Is(FbxSurfacePhong::ClassId))
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

				out->shininess = phong->Shininess.Get();
				out->specular = Color(specular[0], specular[1], specular[2]) * specularFactor;
			}
			else if(id.Is(FbxSurfaceLambert::ClassId))
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

			else return false;

			out->ambient = Color(ambient.first[0], ambient.first[1], ambient.first[2]) * ambient.second;
			out->diffuse = Color(diffuse.first[0], diffuse.first[1], diffuse.first[2]) * diffuse.second;
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