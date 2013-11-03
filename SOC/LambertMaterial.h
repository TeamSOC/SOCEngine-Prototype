#pragma once

#include "Material.h"
#include "Scene.h"

namespace Rendering
{
	namespace Material
	{
		class LambertMaterial : public Material
		{
		private:
			Shader::Shader *diffuse;
			Texture::Texture *texture;

		public:
			LambertMaterial(Texture::Texture *texture) : Material("Lambert")
			{
				Scene *scene = dynamic_cast<Scene*>(Device::DeviceDirector::GetInstance()->GetScene());
				
				if(scene->GetShaderManager()->LoadShaderFromFile("diffuse", &diffuse, false))
				{
					AddShader(diffuse);
					SelectUseShader((SOC_uint)0);
				}

				this->texture = texture;
			}

			~LambertMaterial(void)
			{

			}

		public:
			virtual void ConnectParamater()
			{
				diffuse->SetVariable("mainTex", texture);
			}
		};
	}
}