#include "MeshRenderer.h"

namespace Rendering
{
	namespace Mesh
	{
		MeshRenderer::MeshRenderer(void (**beginFunc)(MeshRenderer*), void (**endFunc)(MeshRenderer*))
		{
			castShadow = false;
			reciveShadow = false;
			this->materialElements = nullptr;

			if(beginFunc && endFunc)
			{
				(*beginFunc)	= this->Begin;
				(*endFunc)		= this->End;
			}
		}

		MeshRenderer::~MeshRenderer(void)
		{
			DeleteMaterial();
		}

		void MeshRenderer::SetMaterial(Material::Material *material)
		{
			this->material = material;

			if(materialElements)
				material->SetElements(*materialElements);
		}

		void MeshRenderer::DeleteMaterial()
		{
			Utility::SAFE_DELETE(material);
		}

		void MeshRenderer::Begin(MeshRenderer *renderer)
		{
			Material::Material* material = renderer->material;
			material->Begin();
			material->BeginPass(0);
		}

		void MeshRenderer::End(MeshRenderer *renderer)
		{
			Material::Material* material = renderer->material;
			material->EndPass();
			material->End();
		}

		void MeshRenderer::ConnectParameters(TransformParameters *transform, std::vector<Light::LightParameters> *lights, SOC_Vector4 &viewPos)
		{
			material->SetUseShaderRequiredParameters(transform, lights, viewPos);
			material->ConnectParamater();
		}

		bool MeshRenderer::HasMaterial()
		{
			return material != nullptr;
		}

		void MeshRenderer::SetMaterialElements(Material::MaterialElements *materialElements)
		{
			this->materialElements = materialElements;
			if(material)
				material->SetElements(*materialElements);
		}
	}
}