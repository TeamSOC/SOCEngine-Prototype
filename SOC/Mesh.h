#pragma once

#include "MeshFilter.h"
#include "MeshRenderer.h"
#include "Device.h"
#include "Component.h"
#include "FBXImporter.h"
#include "MeshDataManager.h"

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
			Device::Graphics	*graphics;

		private:
			MeshDatas *meshData;

		private:
			void (*beginFunc)(MeshRenderer*);
			void (*endFunc)(MeshRenderer*);

		public:
			Mesh(void);
			~Mesh(void);

		public:
			virtual void Render(TransformParameters *transform, std::vector<Light::LightParameters> *lights, SOC_Vector4 &viewPos);

		public:
			MeshRenderer* GetRenderer();
			MeshFilter* GetFilter();

		public:
			virtual void Initialize();
			virtual void Destroy();

		public:

			bool Create(MeshDatas *meshData);
		};

	}
}