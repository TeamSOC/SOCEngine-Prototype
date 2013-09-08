#include "VertexBufferForm.h"

namespace Rendering
{
	namespace Buffer
	{
		VertexBufferForm::VertexBufferForm(int vertexBufferSize, int numOfVertex, Device::Graphics::GraphicsForm *graphics)
		{
			//NULL
			this->vertexBufferSize = vertexBufferSize;
			this->graphics = graphics;
			this->numOfVertex = numOfVertex;
		}

		int VertexBufferForm::GetNumOfVertex()
		{
			return numOfVertex;
		}
		int VertexBufferForm::GetLength()
		{
			return vertexBufferSize * numOfVertex;
		}
		int VertexBufferForm::GetSize()
		{
			return vertexBufferSize;
		}
	}
}