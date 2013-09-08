#pragma once

#include "Rendering.h"
#include "Material.h"

namespace Rendering
{
	namespace Mesh
	{
		class MeshRenderer
		{
		private:
			std::vector<Material*> materials;
			bool castShadow;
			bool reciveShadow;

		public:
			MeshRenderer(void (**beginFunc)(MeshRenderer*) = nullptr, void (**endFunc)(MeshRenderer*) = nullptr);
			~MeshRenderer(void);

		public:
			void AddMaterial(Material *material, bool copy);
			bool DeleteMaterial(Material *material);
			void DeleteAllMaterial();
			Material* FindMaterial(const char *name);

		private:
			static void Begin(MeshRenderer *renderer);
			static void End(MeshRenderer *renderer);

		public:
			SOC_uint GetMaterialCount();
			Material* GetMaterial(int idx);
		};

	}
}