#include "Application.h"

namespace Device
{
	namespace Application
	{
		Application::Application(void)
		{

		}

		Common::Rect<int> Application::GetRect()
		{
			return rect;
		}

		Common::Size<int> Application::GetSize()
		{
			return rect.size;
		}

		void Application::SetRect(Common::Rect<int> r)
		{
			rect = r;
		}
	}
}