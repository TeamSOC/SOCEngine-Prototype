#pragma once

#include "RenderingMath.h"
#include <vector>
#include "Color.h"

namespace Rendering
{	
	namespace Mesh
	{
		struct VBElements
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
			//std::vector<Animation::Bone*> *boneIndices;

		public:
			VBElements(void);
			~VBElements(void);

			//public:
			//	VBElements& operator= (VBElements& other)
			//	{
			//		this->vertices = other.vertices;

			//		return *this;
			//	}
		};
	}
}