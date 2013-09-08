#include "Mesh.h"

namespace Rendering
{
	namespace Mesh
	{
		Mesh::Mesh(Device::Graphics::GraphicsForm	*graphics, MeshFilter *filter, MeshRenderer *renderer)
			:beginFunc(nullptr), endFunc(nullptr)
		{
			this->graphics	= graphics;
			this->filter	= filter == nullptr ? new MeshFilter(graphics) : filter;
			this->renderer	= renderer == nullptr ? new MeshRenderer(&beginFunc, &endFunc) : renderer;
		}

		Mesh::~Mesh(void)
		{
			Utility::SAFE_DELETE(filter);
			Utility::SAFE_DELETE(renderer);
		}

		void Mesh::Render()
		{
			if( (beginFunc && endFunc) == false)
				return;

			beginFunc(renderer);
			{
				DeviceIndexBuffer idxBuffer = filter->GetIndexBuffer()->GetDeviceBuffer();
				SOC_uint numOfVertex = filter->GetNumOfVertex();
				SOC_uint triangleCount = filter->GetNumOfTriangle();
				SOC_TRIANGLE type = filter->GetTriangleType();

				bool b;

				Buffer::VertexBuffer *vb = filter->GetVertexBuffer();

				b = graphics->SetVertexDeclaration( filter->GetDeclaration() );
				b = graphics->SetVertexStream(0, vb->GetDeviceBuffer(), vb->GetSize());
				b = graphics->SetIndices(idxBuffer);

				b = graphics->DrawIndexedPrimitive(type, 0, 0, numOfVertex, 0, triangleCount);
			}
			endFunc(renderer);
		}

		MeshRenderer* Mesh::GetRenderer()
		{
			return renderer;
		}

		MeshFilter* Mesh::GetFilter()
		{
			return filter;
		}
	}
}