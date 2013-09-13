#if defined(WIN32)

#include "DeviceDirector.h"
#include "TScene.h"

using namespace Device::Application;
using namespace Common;

INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
	Device::DeviceDirector::WindowsInitOption options(hInst);
	Device::DeviceDirector::GetInstance()->Initialize(PRESENT_INTERVAL_IMMEDIATE, options);

	//MSG msg;
	//ZeroMemory( &msg, sizeof( msg ) );

	//TestScene *testScene = new TestScene();
	//testScene->init();

	//while( msg.message != WM_QUIT )
	//{
	//	if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
	//	{
	//		TranslateMessage( &msg );
	//		DispatchMessage( &msg );
	//	}
	//	else
	//	{
	//		testScene->loop();
	//	}
	//}
	Device::DeviceDirector::GetInstance()->Run();

	Device::DeviceDirector::GetInstance()->GetApplication()->Destroy();

	return 0;
}

#endif