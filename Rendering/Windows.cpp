#include "Windows.h"

using namespace std;
using namespace Common;

namespace Device
{
	static Common::Rect<int> rect;

	Windows::Options::Options( Common::Rect<int> &rect, HINSTANCE Instance, const wchar_t* name,	bool windowMode,
		HWND parentHandle/* = NULL */, wchar_t* menu/* = NULL */, WNDPROC proc/* = NULL */,  bool isChild/* = false*/)
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
		windowInfo.lpszMenuName		= menu;
		windowInfo.lpszClassName	= name;

		windowInfo.lpfnWndProc = proc;
		windowType = isChild ? WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN : WS_OVERLAPPEDWINDOW | WS_SYSMENU;

		this->rect = rect;
		this->name = windowInfo.lpszClassName;
		this->parentHandle = parentHandle;
		this->windowMode = windowMode;		
	}

	Windows::Windows( Options option )
	{
		windowInfo = option.windowInfo;
		options = option.windowType;
		rect = option.rect;
		name = option.name;
		parentHandle = option.parentHandle;
		handle = option.handle;
		windowMode = option.windowMode;
	}

	Windows::~Windows(void)
	{
		UnregisterClass( name, windowInfo.hInstance );

		if( options != (WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN) )
			 DestroyWindow(handle);
		else PostQuitMessage(0);
	}

	void Windows::Create()
	{
		RegisterClassEx(&windowInfo);

		handle = CreateWindow(name, name, options, 
			rect.x, rect.y, 
			rect.size.w, rect.size.h, 
			parentHandle, NULL, windowInfo.hInstance, NULL);
	}

	void Windows::Show()
	{
		if( options != (WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN) )
			ShowWindow(handle, SW_SHOWDEFAULT);
	}

	LRESULT WINAPI Windows::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return DefWindowProc( hWnd, msg, wParam, lParam );
	}

	//bool Windows::IsChild()
	//{
	//	return (options == (WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN));
	//}

	//Common::Rect<int> Windows::GetRect()
	//{
	//	return rect;
	//}
	//
	//Common::Size<int> Windows::GetSize()
	//{
	//	return rect.size;
	//}

	//bool Windows::IsWindowMode()
	//{
	//	return windowMode;
	//}

	//HWND Windows::GetHandle()
	//{
	//	return handle;
	//}

	Common::Rect<int> Windows::GetRect()
	{
		return rect;
	}

	Common::Size<int> Windows::GetSize()
	{
		return rect.size;
	}
}