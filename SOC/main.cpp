#if defined(WIN32)
#include "DeviceDirector.h"
/// header of HSB
#include "pch/pch.h"
///

using namespace Device::Application;
using namespace Common;

INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
	Device::DeviceDirector::WindowsInitOption options(hInst);
	Device::DeviceDirector::GetInstance()->Initialize(PresentInterval::Immediate, options);
	Device::DeviceDirector::GetInstance()->Run();
	Device::DeviceDirector::GetInstance()->GetApplication()->Destroy();

	return 0;
}

#endif