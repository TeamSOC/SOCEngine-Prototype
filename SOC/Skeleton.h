#pragma once

#include <vector>
#include "Bone.h"

namespace Rendering
{
	namespace Animation
	{
		class Skeleton
		{
		private:
			std::vector<Bone*> bones;

		public:
			Skeleton(void)
			{

			}

			~Skeleton(void)
			{

			}

		public:
			void AddBone( Bone* bone )
			{
			}

			Bone* GetBone( unsigned int index )
			{
			}

			Bone* FindBone( std::string &name )
			{
			}
		};
	}
}