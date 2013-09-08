#pragma once

#include "Application.h"
//#include "Device.h"
#include <Windows.h>

namespace Device
{
	namespace Application
	{
		class Windows : public Application
		{
		private:
			WNDCLASSEX		windowInfo;
			const char*	name;
			HWND			parentHandle;
			HWND			handle;
			unsigned int	options;
			bool			windowsMode;

		private:
			static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		public:
			Windows(Common::Rect<int> &rect, HINSTANCE Instance, const char* name, bool windowMode, bool isChild, HWND parentHandle = NULL);
			~Windows(void);

		public:
			bool Initialize();
			void Destroy();

			void Run();

		public:
			bool IsChild();
			bool IsWindowMode();
			HWND GetHandle();
		};
	}
}