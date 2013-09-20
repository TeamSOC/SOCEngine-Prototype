#include "MeshRenderer.h"


namespace Rendering
{
	namespace Mesh
	{
		MeshRenderer::MeshRenderer(void (**beginFunc)(MeshRenderer*), void (**endFunc)(MeshRenderer*))
		{
			castShadow = false;
			reciveShadow = false;

			if(beginFunc && endFunc)
			{
				(*beginFunc)	= this->Begin;
				(*endFunc)		= this->End;
			}


		}

		MeshRenderer::~MeshRenderer(void)
		{
			DeleteAllMaterial();
		}

		void MeshRenderer::AddMaterial(Material *material, bool copy)
		{
			Material *m = copy ? new Material(*material) : material; // Material::Copy(material) : material;
			materials.push_back(m);
		}

		bool MeshRenderer::DeleteMaterial(Material *material)
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

		void MeshRenderer::DeleteAllMaterial()
		{
			std::vector<Material*>::iterator iter;
			for(iter = materials.begin(); iter != materials.end(); ++iter)
				Utility::SAFE_DELETE(*iter);

			materials.clear();
		}

		Material* MeshRenderer::FindMaterial(const char *name)
		{
			std::vector<Material*>::iterator iter;
			for(iter = materials.begin(); iter != materials.end(); ++iter)
			{
				if( strcmp( (*iter)->GetName(), name ) == 0 )
					return (*iter);
			}

			return nullptr;
		}

		void MeshRenderer::Begin(MeshRenderer *renderer)
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

		void MeshRenderer::End(MeshRenderer *renderer)
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

		SOC_uint MeshRenderer::GetMaterialCount()
		{
			return materials.size();
		}

		Material* MeshRenderer::GetMaterial(int idx)
		{
			return *( materials.begin() + idx );
		}

		void MeshRenderer::ConnectRequiredParameters(TransformParameters *transform, Light::LightParameters *light)
		{
			for(std::vector<Material*>::iterator iter = materials.begin(); iter != materials.end(); ++iter)
			(*iter)->SetUseShaderRequiredParameters(transform, light);
		}

	}
}