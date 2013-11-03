#pragma once

#define FBXSDK_NEW_API

#include <fbxsdk.h>
#pragma comment(lib, "libfbxsdk-md.lib")

#include "MaterialElements.h"
#include "VBElements.h"

#include <vector>

#include "Object.h"

namespace Rendering
{
	namespace Importer
	{
		class FBXImporter
		{
		private:
			fbxsdk_2014_1::FbxManager	*manager;
			fbxsdk_2014_1::FbxScene	*scene;

		public:
			FBXImporter(fbxsdk_2014_1::FbxManager *manager);
			~FBXImporter(void);

		public:
			bool Initialize(const char *sceneName);
			bool LoadScene(const char *fileName, const char *password = nullptr);

			Object* BuildObject(Object *parent);

			void Destroy();

		private:
			Object* Decode(Object *parent, FbxNode *fbxNode);
			void BuildSkeleton(Object *parent, FbxNode *node);
			void CreateMeshComponent(Object *obj, FbxNode *node);
			void SetFbxTransform(Object *obj, FbxNode *node);

			bool BuildMesh(fbxsdk_2014_1::FbxMesh *fbxMesh, Mesh::VBElements *outVBElements);
			void BuildskinningMesh(fbxsdk_2014_1::FbxMesh *fbxMesh, std::vector<int> &skinIndices);

			void ParseMaterial(fbxsdk_2014_1::FbxMesh *fbxMesh, Material::MaterialElements *outMaterialElements, MeshTextureNames *outTextureNames);

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
			bool ParseMaterialElements(fbxsdk_2014_1::FbxSurfaceMaterial *fbxMaterial, Material::MaterialElements *out);			
		};
	}
}