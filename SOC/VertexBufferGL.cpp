//
//  VertexBufferGL.cpp
//  Rendering
//
//  Created by Jiman Jeong on 13. 9. 19..
//  Copyright (c) 2013년 SOC. All rights reserved.
//

#include "VertexBufferGL.h"

using namespace Rendering;
using namespace Buffer;

VertexBufferGL::VertexBufferGL(int vertexBufferSize, int numOfVertex, Device::Graphics::GraphicsForm *graphics)
: VertexBufferForm(vertexBufferSize, numOfVertex, graphics)
{
	
}

bool VertexBufferGL::Create(SOC_dword usage, SOC_POOL pool)
{
	return false;
}

bool VertexBufferGL::Lock(void **inputData)
{
	return false;
}

bool VertexBufferGL::UnLock()
{
	return false;
}

DeviceVertexBuffer VertexBufferGL::GetDeviceBuffer()
{
	return DeviceVertexBuffer();
}