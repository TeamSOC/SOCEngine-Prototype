#pragma once

#define FBXSDK_NEW_API

#include <fbxsdk.h>
#pragma comment(lib, "libfbxsdk-md.lib")

#include "MaterialElements.h"
#include "MeshFilterElements.h"

#include "Bone.h"
#include <vector>

#include "Object.h"

namespace Rendering
{
	namespace Importer
	{
		class MeshImporter
		{
		private:
			fbxsdk_2014_1::FbxManager	*manager;
			fbxsdk_2014_1::FbxScene	*scene;

		public:
			MeshImporter(fbxsdk_2014_1::FbxManager *manager);
			~MeshImporter(void);

		public:
			bool Initialize(const char *sceneName);
			bool LoadScene(const char *fileName, const char *password = nullptr);

			void BuildSkeleton(Object *obj, FbxNode *node)
			{
				FbxSkeleton *fbxSkeleton = node->GetSkeleton();
				FbxNode *fbxNode = fbxSkeleton->GetNode();

				ParseBoneRecursive(obj, fbxNode);
			}

			void AssignMesh(Object *obj, FbxNode *node)
			{
				FbxMesh *fbxMesh = node->GetMesh();
				Mesh::Mesh *mesh = obj->AddComponent<Mesh::Mesh>();

				MeshFilterElements fe;
				MaterialElements me;
				MaterialTextures te;

				BuildMesh(fbxMesh, &fe);
				ParseMaterial(fbxMesh, &me, &te);

				mesh->Create(fe, me, te);
				SetFbxTransform(obj, node);
			}

			void SetFbxTransform(Object *obj, FbxNode *node)
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

			void ParseBoneRecursive(Object *parent, FbxNode *node)
			{
				Object *obj = new Object(parent);
				obj->name = node->GetName();
				parent->AddObject(obj);
				SetFbxTransform(obj, node);

				int count = node->GetChildCount();
				for(int i=0; i<count; ++i)
				{
				    FbxNode *child = node->GetChild( i );
					ParseBoneRecursive( obj, child );
				}
			}

			Object* Decode(Object *parent, FbxNode *fbxNode)
			{
				FbxNodeAttribute *fbxNodeAttri = fbxNode->GetNodeAttribute();

				if(fbxNodeAttri == nullptr)
					return;

				FbxNodeAttribute::EType atType = fbxNodeAttri->GetAttributeType();
				Object *obj = new Object(parent);

				if(parent->HasObject(obj) == false)
					parent->AddObject(obj, false);

				if(atType == FbxNodeAttribute::eMesh)
					AssignMesh(obj, fbxNode);
				else if(atType == FbxNodeAttribute::eSkeleton)
					BuildSkeleton(obj, fbxNode);
				else
					SetFbxTransform(obj, fbxNode);

				int childCount = fbxNode->GetChildCount();
				for(int i=0; i<childCount; ++i)
					Decode(obj, fbxNode->GetChild(i));

				return obj;
			}

			void Destroy();

		private:
			bool BuildMesh(fbxsdk_2014_1::FbxMesh *fbxMesh, MeshFilterElements *outMeshFilterElements);
			void BuildskinningMesh(fbxsdk_2014_1::FbxMesh *fbxMesh, std::vector<int> &skinIndices);

			void ParseMaterial(fbxsdk_2014_1::FbxMesh *fbxMesh, MaterialElements *outMaterialElements, MaterialTextures *outTextures);

			template <typename ElementType>
			bool ParseElements(ElementType* e, int ctrlPointIdx, int vertexCount, int *outIdx)
			{
				if(e == nullptr)
					return false;

				int index = -1;
				FbxLayerElement::EMappingMode mappingMode = e->GetMappingMode();
				FbxLayerElement::EReferenceMode refMode = e->GetReferenceMode();

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

				*outIdx = index;

				return index != -1;
			}

			bool ParseNormals(fbxsdk_2014_1::FbxLayer *layer, int ctrlPointIdx, int vertexCount, SOC_Vector3 *out);
			bool ParseUV(fbxsdk_2014_1::FbxLayer *layer, FbxMesh *fbxMesh, int ctrlPointIdx, int polygonIdx, int vertexIdx, SOC_Vector2 *out);
			bool ParseVertexColor(fbxsdk_2014_1::FbxLayer *layer, int ctrlPointIdx, int vertexCount, Color *out);
			bool ParseTangents(fbxsdk_2014_1::FbxLayer *layer, int ctrlPointIdx, int vertexCount, SOC_Vector3 *out);
			bool ParseBinormals(fbxsdk_2014_1::FbxLayer *layer, int ctrlPointIdx, int vertexCount, SOC_Vector3 *out);

			bool IsSkeleton(fbxsdk_2014_1::FbxNode *node);

			FbxNode* FindSkeletonRoot(fbxsdk_2014_1::FbxNode  *parent);
			bool ParseTexture(fbxsdk_2014_1::FbxProperty &fbxProperty, std::string* outFileName);
			bool ParseMaterialElements(fbxsdk_2014_1::FbxSurfaceMaterial *fbxMaterial, MaterialElements *out);			
		};
	}
}
