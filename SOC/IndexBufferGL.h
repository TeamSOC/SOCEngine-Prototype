//
//  IndexBufferGL.h
//  Rendering
//
//  Created by Jiman Jeong on 13. 9. 19..
//  Copyright (c) 2013년 SOC. All rights reserved.
//

#pragma once

#include "IndexBufferForm.h"

namespace Rendering
{
	namespace Buffer
	{
		class IndexBufferGL : public IndexBufferForm
		{
		public:
			IndexBufferGL(int count, Device::Graphics::GraphicsForm *graphics);
			
		public:
			virtual bool	Create(SOC_POOL pool);
			virtual bool	Lock(void** inputData);
			virtual bool	UnLock();
			
		public:
			virtual DeviceIndexBuffer GetDeviceBuffer();
		};
		
	}
}