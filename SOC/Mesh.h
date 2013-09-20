#pragma once

#include "MeshFilter.h"
#include "MeshRenderer.h"
#include "Device.h"
#include "Component.h"

namespace Rendering
{
	namespace Mesh
	{
		class Mesh : public Component
		{
		public:
			static const Component::Type ComponentType = Component::Type::Mesh;

		private:
			MeshFilter						*filter;
			MeshRenderer					*renderer;
			Device::Graphics::GraphicsForm	*graphics;

		private:
			void (*beginFunc)(MeshRenderer*);
			void (*endFunc)(MeshRenderer*);

		public:
			Mesh(void);
			~Mesh(void);

		public:
			virtual void Render(Rendering::TransformParameters *transform, Rendering::Light::LightParameters *light);

		public:
			MeshRenderer* GetRenderer();
			MeshFilter* GetFilter();
		};

	}
}