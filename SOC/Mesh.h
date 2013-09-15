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
			Mesh(Device::Graphics::GraphicsForm	*graphics, MeshFilter *filter = nullptr, MeshRenderer *renderer = nullptr);
			~Mesh(void);

		public:
			void Render();


		public:
			MeshRenderer* GetRenderer();
			MeshFilter* GetFilter();
		};

	}
}