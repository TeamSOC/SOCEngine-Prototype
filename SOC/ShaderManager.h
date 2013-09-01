#pragma once

#if defined(WIN32) && !defined(_USE_GL_DEFINES)
#include "ShaderManagerDX.h"

namespace Rendering
{
	namespace Shader
	{
		typedef ShaderManagerDX ShaderManager;
	}
}

#elif defined(__APPLE__) || defined(_USE_GL_DEFINES)

#endif