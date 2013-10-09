#include "VertexBufferElements.h"


namespace Rendering
{

		VertexBufferElements::VertexBufferElements(void)
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
		}


		VertexBufferElements::~VertexBufferElements(void)
		{
		}
}