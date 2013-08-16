#pragma once

//추후 계속 업데이트.
//우선은 렌더링만 할 수 있도록 구현.
#include "D3DDevice.h"
#include "Windows.h"

namespace Engine
{
	class DeviceDirector
	{
	private:
		Device::D3DDevice	*d3dDevice;
		Device::Windows		*windows;

	private:
		float elapse;
		float  fps;	

	public:
		DeviceDirector(Device::D3DDevice::PRESENT_INTERVAL interval, Device::Windows::Options option);
		~DeviceDirector(void);

	public:
		void Init();
		void Run();

	private:
		void CalcElapse();
		void CalculateFPS();
	};
}