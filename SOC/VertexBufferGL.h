//
//  VertexBufferGL.h
//  Rendering
//
//  Created by Jiman Jeong on 13. 9. 19..
//  Copyright (c) 2013년 SOC. All rights reserved.
//

#pragma once

#include "VertexBufferForm.h"

namespace Rendering
{
	namespace Buffer
	{
		class VertexBufferGL : public VertexBufferForm
		{
		public:
			VertexBufferGL(int vertexBufferSize, int numOfVertex, Device::Graphics::GraphicsForm *graphics);
			
		public:
			virtual bool Create(SOC_dword usage, SOC_POOL pool);
			virtual bool Lock(void **inputData);
			virtual bool UnLock();
			
		public:
			virtual DeviceVertexBuffer GetDeviceBuffer();
		};
	}
}

