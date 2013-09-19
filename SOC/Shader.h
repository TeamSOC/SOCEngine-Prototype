#pragma once

#if defined(WIN32) && !defined(_USE_GL_DEFINES)

#include "ShaderDX.h"

namespace Rendering
{
	namespace Shader
	{
		typedef ShaderDX Shader;
	}
}

#elif defined(__APPLE__) || defined(_USE_GL_DEFINES)

#include "ShaderGL.h"

namespace Rendering
{
	namespace Shader
	{
		typedef ShaderGL Shader;
	}
}

#endif