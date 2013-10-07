#include "MeshFilterElements.h"


namespace Rendering
{
	namespace Mesh
	{

		MeshFilterElements::MeshFilterElements(void)
		{
			vertices = nullptr;
			normals = nullptr;
			tangents = nullptr;
			binomals = nullptr;

			std::vector<SOC_Vector2*> *texturCoord;
			Color *colors;

			numOfVertex = 0;
			numOfTriangle = 0;

			std::pair<count, SOC_word*> indices;
			bool isDynamic = false;
		}


		MeshFilterElements::~MeshFilterElements(void)
		{
		}

	}
}