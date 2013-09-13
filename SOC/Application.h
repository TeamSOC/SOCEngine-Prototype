#pragma once

#include "Rect.h"

namespace Device
{
	namespace Application
	{
		class Application
		{
		protected:
			Common::Rect<int> rect;

		public:
			Application(void);

		public:
			virtual bool Initialize() = 0;
			virtual void Destroy() = 0;

		public:
			Common::Rect<int> GetRect();
			Common::Size<int> GetSize();

		protected:
			void SetRect(Common::Rect<int> r);
		};

	}
}