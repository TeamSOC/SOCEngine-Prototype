#pragma once

#include "RenderingMath.h"

#define FBXSDK_NEW_API
#pragma comment(lib, "libfbxsdk-md.lib")
#include <fbxsdk.h>

#if defined(WIN32) && !defined(_USE_GL_DEFINES)

#include "DX.h"

#elif defined(__APPLE__) || defined(_USE_GL_DEFINES)

#include "GL.h"


#endif