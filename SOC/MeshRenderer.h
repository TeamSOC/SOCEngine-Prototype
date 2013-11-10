#pragma once

#include "Platform.h"
#include "Material.h"

namespace Rendering
{
	namespace Mesh
	{
		class MeshRenderer
		{
		private:
			Material::Material* material;
			Material::MaterialElements *materialElements;

			bool castShadow;
			bool reciveShadow;

		public:
			MeshRenderer(void (**beginFunc)(MeshRenderer*) = nullptr, void (**endFunc)(MeshRenderer*) = nullptr);
			~MeshRenderer(void);

		public:
			void ConnectParameters(TransformParameters *transform, std::vector<Light::LightParameters> *lights, SOC_Vector4 &viewPos);
			void UpdateParamaters();

		private:
			static void Begin(MeshRenderer *renderer);
			static void End(MeshRenderer *renderer);

		public:
			void SetMaterial(Material::Material *material);
			void SetMaterialElements(Material::MaterialElements *materialElements);

			bool HasMaterial();

			void DeleteMaterial();
		};

	}
}