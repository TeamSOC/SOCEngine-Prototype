#include "DeviceDirector.h"

using namespace Device;
using namespace Utility;

namespace Engine
{
	DeviceDirector::DeviceDirector(D3DDevice::PRESENT_INTERVAL interval, Windows::Options option)
		:windows(NULL), d3dDevice(NULL)
	{
		windows = new Windows(option);
		d3dDevice = new D3DDevice(interval,  windows);

		elapse = 0.0f;
	}

	DeviceDirector::~DeviceDirector(void)
	{
		SAFE_DELETE(windows);
		SAFE_DELETE(d3dDevice);
	}

	void DeviceDirector::Init()
	{
		windows->Create();
		windows->Show();

		d3dDevice->Init();
	}

	void DeviceDirector::Run()
	{
		MSG msg;

		ZeroMemory( &msg, sizeof( msg ) );

		while( msg.message != WM_QUIT )
		{
			if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
			else
			{
				//µ¹·Á

				CalcElapse();
				CalculateFPS();
			}
		}

	}

	void DeviceDirector::CalcElapse()
	{
		static float	lastTime;
		float			now;
		static DWORD	staticTime = GetTickCount();

		now = (float)(GetTickCount() - staticTime) / 1000;

		elapse = now - lastTime;
		elapse = Utility::Max((float)0, elapse);

		lastTime = now;
	}

	void DeviceDirector::CalculateFPS()
	{
		static int frameCnt = 0;
		static float elapsed = 0;

		frameCnt++;
		elapsed += elapse;

		if( elapsed >= 1.f )
		{
			fps = (float)frameCnt / elapsed;
			elapsed = 0;
			frameCnt = 0;
		}
	}
}