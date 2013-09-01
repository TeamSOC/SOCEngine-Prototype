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
			MeshRenderer(void (**beginFunc)(void) = nullptr, void (**endFunc)(void) = nullptr)
			{
				castShadow = false;
				reciveShadow = false;

				if(beginFunc && endFunc)
				{
					*beginFunc = &this->Begin;
					*endFunc = &this->End;
				}
			}

			~MeshRenderer(void)
			{
				DeleteAllMaterial();
			}

		public:
			void AddMaterial(Material *material, bool copy)
			{
				Material *m = copy ? Material::Copy(material) : material;
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
			void Begin()
			{
				std::vector<Material*>::iterator iter;
				for(iter = materials.begin(); iter != materials.end(); ++iter)
				{
					(*iter)->Begin();
					(*iter)->BeginPass();
				}
			}
			void End()
			{
				std::vector<Material*>::iterator iter;
				for(iter = materials.begin(); iter != materials.end(); ++iter)
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