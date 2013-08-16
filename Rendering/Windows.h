#pragma once

#include <Windows.h>
#include <string>
#include "Utility.h"

#define DEFAULT_WINDOW_NAME L"Framework"

#define SAFE_RELEASE(D3D)\
	if(D3D){D3D->Release(); D3D=NULL;}

/*
현재 구현 안한것
1. 해상도 조절
2. 기본 해상도
*/

namespace Device
{
	class Windows
	{
	public:
		struct Options
		{
			WNDCLASSEX			windowInfo;
			unsigned int		windowType;
			Common::Rect<int>	rect;
			const wchar_t*		name;
			HWND				parentHandle;
			HWND				handle;
			bool				windowMode;

			Options(Common::Rect<int> &rect, HINSTANCE Instance, const wchar_t* name, bool windowMode,
					HWND parentHandle = NULL, wchar_t* menu = NULL,	WNDPROC proc = NULL,   
					bool isChild = false);
		};

	protected:
		WNDCLASSEX			windowInfo;
		unsigned int		options;
//		Common::Rect<int>	rect;
		const wchar_t*		name;
		HWND				parentHandle;
		HWND				handle;
		bool				windowMode;

	public:

		Windows( Options option );

		~Windows(void);

	public:
		void Create();
		void Show();
		void UnRegist();

	public:
		inline bool IsChild()					{ return options == (WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN); }
		static Common::Rect<int> GetRect();
		static Common::Size<int> GetSize();
		inline bool IsWindowMode()				{ return windowMode; }
		inline HWND GetHandle()					{ return handle; }

	public:
		static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};

}