#include "D3DDevice.h"

namespace Device
{

	D3DDevice::D3DDevice(PRESENT_INTERVAL type, Windows *windows)
	{
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		
		d3dpp.Windowed = windows->IsWindowMode();

		if(type == PRESENT_INTERVAL_DEFAULT)
			d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
		else if( type == PRESENT_INTERVAL_IMMEDIATE )
			d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		else d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

		d3dpp.BackBufferWidth				= windows->GetSize().w;
		d3dpp.BackBufferHeight				= windows->GetSize().h;
		d3dpp.BackBufferFormat				= D3DFMT_X8R8G8B8;
		d3dpp.BackBufferCount				= 1;
		d3dpp.MultiSampleType				= D3DMULTISAMPLE_NONE;
		d3dpp.MultiSampleQuality			= 0;
		d3dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow					= windows->GetHandle();
	    d3dpp.EnableAutoDepthStencil		= TRUE;
	    d3dpp.AutoDepthStencilFormat		= D3DFMT_D24X8;
	    d3dpp.Flags							= D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
	    d3dpp.FullScreen_RefreshRateInHz	= 0;
	}

	D3DDevice::~D3DDevice(void)
	{
		SAFE_RELEASE(d3dHandle);
		SAFE_RELEASE(device);
	}

	bool D3DDevice::Init()
	{
		if(FAILED(d3dHandle->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &device)))
			return false;

		return true;
	}
}