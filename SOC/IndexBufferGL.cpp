//
//  IndexBufferGL.cpp
//  Rendering
//
//  Created by Jiman Jeong on 13. 9. 19..
//  Copyright (c) 2013년 SOC. All rights reserved.
//

#include "IndexBufferGL.h"

using namespace Rendering;
using namespace Buffer;

IndexBufferGL::IndexBufferGL(int count, Device::Graphics::GraphicsForm *graphics)
: IndexBufferForm(count, graphics)
{
	
}

bool IndexBufferGL::Create(SOC_POOL pool)
{
	return false;
}

bool IndexBufferGL::Lock(void** inputData)
{
	return false;
}

bool IndexBufferGL::UnLock()
{
	return false;
}

DeviceIndexBuffer IndexBufferGL::GetDeviceBuffer()
{
	return DeviceIndexBuffer();
}