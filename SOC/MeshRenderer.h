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
			MeshRenderer(void (**beginFunc)(MeshRenderer*) = nullptr, void (**endFunc)(MeshRenderer*) = nullptr)
			{
				castShadow = false;
				reciveShadow = false;

				if(beginFunc && endFunc)
				{
					(*beginFunc)	= this->Begin;
					(*endFunc)		= this->End;
				}
			}

			~MeshRenderer(void)
			{
				DeleteAllMaterial();
			}

		public:
			void AddMaterial(Material *material, bool copy)
			{
				Material *m = copy ? new Material(*material) : material; // Material::Copy(material) : material;
				materials.push_back(m);
			}
			bool DeleteMaterial(Material *material)
			{
				std::vector<Material*>::iterator iter;
				for(iter = materials.begin(); iter != materials.end(); ++iter)
				{
					if(material == (*iter))
					{
						Utility::SAFE_DELETE(*iter);
						materials.erase(iter);
						return true;
					}
				}

				return false;
			}
			void DeleteAllMaterial()
			{
				std::vector<Material*>::iterator iter;
				for(iter = materials.begin(); iter != materials.end(); ++iter)
					Utility::SAFE_DELETE(*iter);

				materials.clear();
			}
			Material* FindMaterial(const char *name)
			{
				std::vector<Material*>::iterator iter;
				for(iter = materials.begin(); iter != materials.end(); ++iter)
				{
					if( strcmp( (*iter)->GetName(), name ) == 0 )
						return (*iter);
				}

				return nullptr;
			}

		private:
			static void Begin(MeshRenderer *renderer)
			{
				std::vector<Material*>::iterator iter;
				std::vector<Material*>::iterator begin = renderer->materials.begin();
				std::vector<Material*>::iterator end = renderer->materials.end();

				for(iter = begin; iter != end; ++iter)
				{
					(*iter)->Begin();
					(*iter)->BeginPass();
				}
			}
			static void End(MeshRenderer *renderer)
			{
				std::vector<Material*>::iterator iter;
				std::vector<Material*>::iterator begin = renderer->materials.begin();
				std::vector<Material*>::iterator end = renderer->materials.end();

				for(iter = begin; iter != end; ++iter)
				{
					(*iter)->EndPass();
					(*iter)->End();
				}
			}

		public:
			SOC_uint GetMaterialCount()
			{
				return materials.size();
			}

			Material* GetMaterial(int idx)
			{
				return *( materials.begin() + idx );
			}
		};

	}
}