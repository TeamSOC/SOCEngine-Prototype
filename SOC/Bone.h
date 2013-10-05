#pragma once

#include <string>
#include "RenderingMath.h"

namespace Rendering
{
	namespace Animation
	{
		class Bone
		{
		public:
			std::string name;
			int index;
			int indexParnet;

			SOC_Vector3 position;
			SOC_Vector3 eularAngle;

			SOC_Matrix relativeMatrix;
			SOC_Matrix absoluteMatrix;
			SOC_Matrix absoluteInvMatrix;

		public:
			Bone(void)
			{
			}

			~Bone(void)
			{
			}
		};
	}
}