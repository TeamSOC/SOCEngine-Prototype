#include "Mesh.h"
#include "Transform.h"

namespace Rendering
{
	namespace Mesh
	{
		Mesh::Mesh(void) : beginFunc(nullptr), endFunc(nullptr)
		{

		}

		Mesh::~Mesh(void)
		{

		}

		void Mesh::Initialize()
		{
			this->graphics	= Device::DeviceDirector::GetInstance()->GetGraphics();
			this->filter	= new MeshFilter(graphics);
			this->renderer	= new MeshRenderer(&beginFunc, &endFunc);
		}

		void Mesh::Destroy()
		{
			Utility::SAFE_DELETE(filter);
			Utility::SAFE_DELETE(renderer);
		}

		void Mesh::Render(Rendering::TransformParameters *transform, Rendering::Light::LightParameters *light)
		{
			if( (beginFunc && endFunc) == false)
				return;

			renderer->ConnectRequiredParameters(transform, light);

			beginFunc(renderer);
			{
				DeviceIndexBuffer idxBuffer = filter->GetIndexBuffer()->GetDeviceBuffer();
				SOC_uint numOfVertex = filter->GetNumOfVertex();
				SOC_uint triangleCount = filter->GetNumOfTriangle();
				SOC_TRIANGLE type = filter->GetTriangleType();

				Buffer::VertexBuffer *vb = filter->GetVertexBuffer();

				graphics->SetVertexDeclaration( filter->GetDeclaration() );
				graphics->SetVertexStream(0, vb->GetDeviceBuffer(), vb->GetSize());
				graphics->SetIndices(idxBuffer);

				graphics->DrawIndexedPrimitive(type, 0, 0, numOfVertex, 0, triangleCount);
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

		//Component::Type Mesh::GetComponentType()
		//{
		//	return Component::Type::Mesh;
		//}
	}
}