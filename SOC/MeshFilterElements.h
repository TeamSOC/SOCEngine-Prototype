#pragma once

#include "RenderingMath.h"
#include <vector>
#include "Color.h"
#include "Bone.h"

namespace Rendering
{
	struct MeshFilterElements
	{
	public:
		typedef int count;

	public:
		SOC_Vector3 *vertices;
		SOC_Vector3 *normals;
		SOC_Vector3 *tangents;
		SOC_Vector3 *binomals;
		std::pair<count, SOC_Vector2**> texcoords;
		Color *colors;
		int numOfVertex;
		int numOfTriangle;
		std::pair<count, SOC_word*> indices;
		SOC_TRIANGLE type;
		bool isDynamic;
		std::pair<count, int*> skinIndices;
		//std::pair<count, Animation::Bone*> boneIndices;
		std::vector<Animation::Bone*> *boneIndices;

	public:
		MeshFilterElements(void);
		~MeshFilterElements(void);

	//public:
	//	MeshFilterElements& operator= (MeshFilterElements& other)
	//	{
	//		this->vertices = other.vertices;

	//		return *this;
	//	}
	};

}