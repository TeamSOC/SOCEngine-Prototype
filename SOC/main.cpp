#if defined(WIN32)

#include "DeviceDirector.h"
#include "Scene.h"

using namespace Device::Application;
using namespace Common;

INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
	//Windows *windows = new Windows( Rect<int>(0, 0, 800, 800), hInst, "TEST", true, false);
	//windows->Initialize();

	Device::DeviceDirector::WindowsInitOption options(hInst);

	Device::DeviceDirector::GetInstance()->Initialize(PRESENT_INTERVAL_IMMEDIATE, options);
	//	Device::DeviceDirector::GetInstance()->Run();

	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );

	TestScene *testScene = new TestScene();
	testScene->init();

	while( msg.message != WM_QUIT )
	{
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			testScene->loop();
		}
	}

	return 0;
}

#endif