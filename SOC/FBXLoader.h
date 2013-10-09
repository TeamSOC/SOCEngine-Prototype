#pragma once

#define FBXSDK_NEW_API

#include <fbxsdk.h>
#pragma comment(lib, "libfbxsdk-md.lib")

#include "MaterialElements.h"
#include "MeshFilterElements.h"

#include "Bone.h"
#include <vector>

using namespace fbxsdk_2014_1;

namespace Rendering
{
	namespace Importer
	{
		class FBXLoader
		{
		private:
			FbxManager	*manager;
			FbxScene	*scene;

		public:
			FBXLoader(fbxsdk_2014_1::FbxManager *manager);
			~FBXLoader(void);

		public:
			bool Initialize(const char *sceneName);
			bool LoadScene(const char *fileName, const char *password = nullptr);
			bool Decode(MaterialElements *outMaterialElements, Mesh::MeshFilterElements *outMeshFliterElements, MaterialTextures *outTextureNames);

		private:

			bool BuildMesh(FbxMesh *fbxMesh, Mesh::MeshFilterElements *outMeshFilterElements, MaterialElements *outMaterialElements, MaterialTextures *outTextures);
			void BuildskinningMesh(FbxMesh *fbxMesh, std::vector<int> &boneIndices);

			template <typename ElementType>
			bool ParseElements(ElementType* e, int ctrlPointIdx, int vertexCount, int *outIdx)
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

				*outIdx = index;

				return index != -1;
			}

			bool ParseNormals(FbxLayer *layer, int ctrlPointIdx, int vertexCount, SOC_Vector3 *out);
			bool ParseUV(FbxLayer *layer, FbxMesh *fbxMesh, int ctrlPointIdx, int polygonIdx, int vertexIdx, SOC_Vector2 *out);
			bool ParseVertexColor(FbxLayer *layer, int ctrlPointIdx, int vertexCount, Color *out);
			bool ParseTangents(FbxLayer *layer, int ctrlPointIdx, int vertexCount, SOC_Vector3 *out);
			bool ParseBinormals(FbxLayer *layer, int ctrlPointIdx, int vertexCount, SOC_Vector3 *out);

			bool IsSkeleton(FbxNode *node);

			FbxNode* FindSkeletonRoot(FbxNode  *parent);
			void ParseBoneRecursive(const FbxNode* boneNode, int parentBoneIdx, std::vector<Animation::Bone*> *outBones);
			bool BuildSkeleton(FbxSkeleton *skeleton, std::vector<Animation::Bone*> *outBones);
			bool ParseTexture(FbxProperty &fbxProperty, std::string* outFileName);
			bool ParseMaterialElements(FbxSurfaceMaterial *fbxMaterial, MaterialElements *out);

			void Destroy();
		};
	}
}