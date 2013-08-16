#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include "Windows.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//∑ª¥ı ≈∏±Í ∏∏µÈ¡ˆ æ ¿Ω.

namespace Device
{
	class D3DDevice
	{
	public:
		enum PRESENT_INTERVAL
		{
			PRESENT_INTERVAL_DEFAULT,
			PRESENT_INTERVAL_IMMEDIATE,
			PRESENT_INTERVAL_VERTICALSYNC
		};

	private:
		LPDIRECT3D9			d3dHandle;
		LPDIRECT3DDEVICE9	device;

		D3DPRESENT_PARAMETERS d3dpp;

	public:
		D3DDevice(PRESENT_INTERVAL type, Windows* windows);
		~D3DDevice(void);

	public:
		bool Init();

	public:
		inline LPDIRECT3DDEVICE9 GetDevice() { return device; }
	};

}