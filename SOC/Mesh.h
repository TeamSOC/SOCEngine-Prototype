#pragma once

#include "MeshFilter.h"
#include "MeshRenderer.h"
#include "Device.h"

namespace Rendering
{
	namespace Mesh
	{
		class Mesh
		{
		private:
			MeshFilter						*filter;
			MeshRenderer					*renderer;
			Device::Graphics::GraphicsForm	*graphics;

		private:
			void (*beginFunc)(MeshRenderer*);
			void (*endFunc)(MeshRenderer*);

		public:
			Mesh(Device::Graphics::GraphicsForm	*graphics, MeshFilter *filter = nullptr, MeshRenderer *renderer = nullptr)
				:beginFunc(nullptr), endFunc(nullptr)
			{
				this->graphics	= graphics;
				this->filter	= filter == nullptr ? new MeshFilter() : filter;
				this->renderer	= renderer == nullptr ? new MeshRenderer(&beginFunc, &endFunc) : renderer;
			}

			~Mesh(void)
			{
				Utility::SAFE_DELETE(filter);
				Utility::SAFE_DELETE(renderer);
			}

		public:
			void Render()
			{
				if( (beginFunc && endFunc) == false)
					return;

				beginFunc(renderer);
				{
					void* idxBuffer = filter->GetIndexBuffer()->GetBuffer();
					SOC_uint numOfVertex = filter->GetNumOfVertex();
					SOC_uint triangleCount = filter->GetTriangleCount();
					SOC_TRIANGLE type = filter->GetTriangleType();

					bool b;

					Buffer::VertexBuffer *vb = filter->GetVertexBuffer();

					b = graphics->SetVertexStream(0, vb->GetDeviceBuffer(), vb->GetSize());
 					b = graphics->SetIndices(idxBuffer);
					b = graphics->DrawIndexedPrimitive(type, 0, 0, numOfVertex, 0, 12);

					int a = 5;
					a = 3;
				}
				endFunc(renderer);
			}

		public:
			MeshRenderer* GetRenderer()
			{
				return renderer;
			}
			MeshFilter* GetFilter()
			{
				return filter;
			}
		};

	}
}