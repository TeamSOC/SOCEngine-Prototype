#include "SpotLight.h"

namespace Rendering
{
	namespace Light
	{
		SpotLight::SpotLight(Object *parent)  : LightForm(parent)
		{
			type = LIGHTTYPE_SPOT;
		}

		bool SpotLight::Intersect(SOC_Vector3 worldPos, float radius)
		{
			return true;
		}
	}
}