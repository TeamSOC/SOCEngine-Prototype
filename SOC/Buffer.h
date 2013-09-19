#pragma once

#if defined(WIN32) && !defined(_USE_GL_DEFINES)

#include "VertexBufferDX.h"
#include "IndexBufferDX.h"

namespace Rendering
{
	namespace Buffer
	{
		typedef VertexBufferDX	VertexBuffer;
		typedef IndexBufferDX	IndexBuffer;
	}
}

#elif defined(__APPLE__) || defined(_USE_GL_DEFINES)

#include "VertexBufferGL.h"
#include "IndexBufferGL.h"

namespace Rendering
{
	namespace Buffer
	{
		typedef VertexBufferGL	VertexBuffer;
		typedef IndexBufferGL	IndexBuffer;
	}
}


#endif