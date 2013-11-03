#include "VBElements.h"
#include "Utility.h"

using namespace Utility;

namespace Rendering
{
	namespace Mesh
	{
		VBElements::VBElements(void)
		{
			vertices = nullptr;
			normals = nullptr;
			tangents = nullptr;
			binormals = nullptr;

			numOfVertex = 0;
			numOfTriangle = 0;

			texcoords.first = 0;
			texcoords.second = nullptr;

			colors = nullptr;

			indices.first = 0;
			indices.second = nullptr;

			type = SOC_TRIANGLE::SOC_TRIANGLE_LIST;
			isDynamic = false;
		}

		VBElements::VBElements(SOC_Vector3 *vertices, SOC_Vector3 *normals, SOC_Vector3 *tangents,
				SOC_Vector3 *binormals, std::pair<count, SOC_Vector2**> &texcoords,
				Color *colors, int numOfVertex, int numOfTriangle, std::pair<count, SOC_word*> &indices,
				SOC_TRIANGLE type, bool isDynamic)
		{
			this->vertices = vertices;
			this->normals = normals;
			this->tangents = tangents;
			this->binormals = binormals;
			this->numOfVertex = numOfVertex;
			this->numOfTriangle = numOfTriangle;
			this->texcoords = texcoords;
			this->colors = colors;
			this->indices = indices;
			this->type = type;
			this->isDynamic = false;
		}

		VBElements::~VBElements(void)
		{
			SAFE_DELETE(vertices);
			SAFE_DELETE(normals);
			SAFE_DELETE(tangents);
			SAFE_DELETE(binormals);

			if(texcoords.second)
			{
				for(int i=0; i<texcoords.first; ++i)
					SAFE_ARRARY_DELETE(texcoords.second[i]);

				SAFE_ARRARY_DELETE(texcoords.second);
			}

			SAFE_DELETE(colors);
			SAFE_ARRARY_DELETE(indices.second);
		}
	}
}