#include "LightForm.h"
#include "Object.h"

namespace Rendering
{
	namespace Light
	{
		LightForm::LightForm( )
		{
			range = 10.0f;
			specularPower = 20.0f;

			//worldPosition = SOC_Vector3(0, 0, 0);
			//direction = SOC_Vector3(0, 0, 0);

			diffuseColor = Color::white();
			specularColor = Color::white();
		}

		SOC_Vector3& LightForm::GetWorldPosition()
		{
			return ownerTransform->GetWorldPosition();
		}

		SOC_Vector3& LightForm::GetDirection()
		{
			return ownerTransform->GetForward();
		}
	}
}