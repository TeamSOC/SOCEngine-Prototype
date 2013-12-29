#pragma once

#include "Component.h"
#include "Bone.h"
#include <vector>

namespace Rendering
{
	namespace Animation
	{
		class Skeleton : public Component
		{
		public:
			static const Component::Type ComponentType = Component::Type::Skeleton;

		public:
			std::vector<Bone*> bones;

		public:
			Skeleton(void)
			{
			}

			~Skeleton(void)
			{
			}

		public:
			virtual void Initialize()
			{

			}

			virtual void Destroy()
			{

			}
		};

	}
}