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
			binomals = nullptr;

			numOfVertex = 0;
			numOfTriangle = 0;

			texcoords.first = 0;
			texcoords.second = nullptr;

			colors = nullptr;

			indices.first = 0;
			indices.second = nullptr;

			type = SOC_TRIANGLE::SOC_TRIANGLE_LIST;

			skinIndices.first = 0;
			skinIndices.second = nullptr;
		}


		VBElements::~VBElements(void)
		{
			SAFE_DELETE(vertices);
			SAFE_DELETE(normals);
			SAFE_DELETE(tangents);
			SAFE_DELETE(binomals);

			if(texcoords.second)
			{
				for(int i=0; i<texcoords.first; ++i)
					SAFE_ARRARY_DELETE(texcoords.second[i]);

				SAFE_ARRARY_DELETE(texcoords.second);
			}

			SAFE_DELETE(colors);
			SAFE_ARRARY_DELETE(indices.second);
			SAFE_ARRARY_DELETE(skinIndices.second);
		}
	}
}