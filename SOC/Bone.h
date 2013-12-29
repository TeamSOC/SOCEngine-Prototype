#pragma once

#include "RenderingMath.h"
#include <string>
#include <vector>

//Object를 사용해서 처리하는 방법도 있겠지만..

namespace Rendering
{
	namespace Animation
	{
		struct BoneInfluence
		{
			int			ctrlPointIdx;
			double		weight;
		};

		class Bone
		{
		public:
			std::string name;
			
			int index;
			int indexParent;
//			int parentIndex;

			SOC_Vector3 position;
			SOC_Vector3 eulerAngles;

//			SOC_Matrix matrix;
			std::vector<BoneInfluence*> influences;

		public:
			Bone(void)
			{
				index = -1;
				indexParent = -1;

				position = SOC_Vector3(0, 0, 0);
				eulerAngles = SOC_Vector3(0, 0, 0);
			}

			~Bone(void)
			{

			}
		};
	}
}