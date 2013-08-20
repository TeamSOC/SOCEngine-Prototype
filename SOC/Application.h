#pragma once

#include "Rect.h"

namespace Device
{
	namespace Application
	{
		static Common::Rect<int>	rect;

		class Application
		{
		public:
			Application(void)
			{

			}

		public:
			virtual bool Initialize() = 0;
			virtual void Destroy() = 0;

		public:
			static Common::Rect<int> GetRect()
			{
				return rect;
			}

			static Common::Size<int> GetSize()
			{
				return rect.size;
			}

		protected:
			void SetRect(Common::Rect<int> r)
			{
				rect = r;
			}
		};

	}
}