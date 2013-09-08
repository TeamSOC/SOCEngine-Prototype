#include "Windows.h"

namespace Device
{
	namespace Application
	{
		LRESULT Windows::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
		{
			if(msg == WM_DESTROY || msg == WM_CLOSE)
			{
				PostQuitMessage(0);
				return 0;
			}

			return DefWindowProc( hWnd, msg, wParam, lParam );
		}

		Windows::Windows(Common::Rect<int> &rect, HINSTANCE Instance, const char* name, bool windowMode, bool isChild, HWND parentHandle)
		{
			windowInfo.cbSize			= sizeof(WNDCLASSEX);
			windowInfo.style			= CS_CLASSDC;
			windowInfo.hInstance		= Instance;//GetModuleHandle(NULL);
			windowInfo.cbClsExtra		= 0L;
			windowInfo.cbWndExtra		= 0L;
			windowInfo.hIcon			= NULL;
			windowInfo.hCursor			= NULL;
			windowInfo.hbrBackground	= NULL;
			windowInfo.hIconSm			= NULL;
			windowInfo.lpszMenuName		= NULL;
			windowInfo.lpszClassName	= name;

			windowInfo.lpfnWndProc		= WndProc;
			options = isChild ? WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN : WS_OVERLAPPEDWINDOW | WS_SYSMENU;

			SetRect(rect);
			this->name = name;
			this->parentHandle = parentHandle;
			this->windowsMode = windowMode;
		}

		Windows::~Windows(void)
		{
			Destroy();
		}

		bool Windows::Initialize()
		{
			RegisterClassEx(&windowInfo);

			handle = CreateWindow(name, name, options, 
				rect.x, rect.y, 
				rect.size.w, rect.size.h, 
				parentHandle, NULL, windowInfo.hInstance, NULL);

			if(handle == NULL)
				return false;

			if( options != (WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN) )
				ShowWindow(handle, SW_SHOWDEFAULT);

			return true;
		}
		void Windows::Destroy()
		{
			UnregisterClass( name, windowInfo.hInstance );

			if( options != (WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN) )
				DestroyWindow(handle);
			else PostQuitMessage(0);
		}

		void Windows::Run()
		{

		}

		bool Windows::IsChild()
		{
			return options == (WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN);
		}
		bool Windows::IsWindowMode()
		{
			return windowsMode;
		}
		HWND Windows::GetHandle()
		{
			return handle;
		}
	}
}