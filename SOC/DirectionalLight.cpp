#include "DirectionalLight.h"


namespace Rendering
{
	namespace Light
	{
		DirectionalLight::DirectionalLight(Object *parent) : LightForm(parent)
		{
			type = LIGHTTYPE_DIRECTIONAL;
		}

		DirectionalLight::~DirectionalLight(void)
		{
		}

		bool DirectionalLight::Intersect(SOC_Vector3 worldPos, float radius)
		{
			return true;
		}
	}
}