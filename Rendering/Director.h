#pragma once

//추후 계속 업데이트.
//우선은 렌더링만 할 수 있도록 구현.
#include "../Device/D3DDevice.h"
#include "../Device/Windows.h"

namespace Engine
{
	namespace Renderer
	{
		class Director
		{
		public:
			Director(void);
			~Director(void);
		};
	}
}