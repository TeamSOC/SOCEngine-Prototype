#pragma once

#include "RenderingMath.h"

#if defined(WIN32) && !defined(_USE_GL_DEFINES)

#include "Graphics.h"

#elif defined(__APPLE__) || defined(_USE_GL_DEFINES)

#include "GL.h"


#endif