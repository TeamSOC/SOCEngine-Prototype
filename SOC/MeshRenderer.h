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
			std::vector<Material::Material*> materials;
			bool castShadow;
			bool reciveShadow;

		public:
			MeshRenderer(void (**beginFunc)(MeshRenderer*) = nullptr, void (**endFunc)(MeshRenderer*) = nullptr);
			~MeshRenderer(void);

		public:
			void AddMaterial(Material::Material *material, bool copy);
			bool DeleteMaterial(Material::Material *material);
			void DeleteAllMaterial();
			Material::Material* FindMaterial(const char *name);

			void ConnectParameters(TransformParameters *transform, Light::LightParameters *light);
			void UpdateParamaters();

		private:
			static void Begin(MeshRenderer *renderer);
			static void End(MeshRenderer *renderer);

		public:
			SOC_uint GetMaterialCount();
			Material::Material* GetMaterial(int idx = 0);
		};

	}
}