#pragma once

enum PRESENT_INTERVAL
{
	PRESENT_INTERVAL_DEFAULT,
	PRESENT_INTERVAL_IMMEDIATE,
	PRESENT_INTERVAL_VERTICALSYNC
};

#if defined(WIN32) && !defined(_USE_GL_DEFINES)

#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>


#pragma comment(lib, "d3d9.lib")

#if _DEBUG

#pragma comment(lib, "d3dx9d.lib")

#else

#pragma comment(lib, "d3dx9.lib")

#endif

#define SOC_FMT_R8G8B8		D3DFMT_R8G8B8
#define SOC_FMT_A8R8G8B8	D3DFMT_A8R8G8B8

#define SOC_FMT_A4R4G4B4	D3DFMT_A4R4G4B4
#define SOC_FMT_A8			D3DFMT_A8

#define SOC_FMT_X4R4G4B4	D3DFMT_X4R4G4B4
#define SOC_FMT_A8B8G8R8	D3DFMT_A8B8G8R8

#define SOC_FMT_G16R16		 D3DFMT_G16R16
#define SOC_FMT_A16B16G16R16 D3DFMT_A16B16G16R16

#define SOC_FMT_D32			D3DFMT_D32
#define SOC_FMT_D24X8		D3DFMT_D24X8
#define SOC_FMT_D16			D3DFMT_D16
#define SOC_FMT_VERTEXDATA	D3DFMT_VERTEXDATA
#define SOC_FMT_INDEX16		D3DFMT_INDEX16
#define SOC_FMT_INDEX32		D3DFMT_INDEX32

#define SOC_FMT_R16F		D3DFMT_R16F
#define SOC_FMT_R32F		D3DFMT_R32F
#define SOC_FMT_G32R32F		D3DFMT_G32R32F

#define SOC_USAGE_DEPTHSTENCIL			D3DUSAGE_DEPTHSTENCIL
#define SOC_USAGE_DMAP					D3DUSAGE_DMAP
#define SOC_USAGE_DONOTCLIP				D3DUSAGE_DONOTCLIP
#define SOC_USAGE_DYNAMIC				D3DUSAGE_DYNAMIC
#define SOC_USAGE_RENDERTARGET			D3DUSAGE_RENDERTARGET
#define SOC_USAGE_SOFTWAREPROCESSING	D3DUSAGE_SOFTWAREPROCESSING
#define SOC_USAGE_WRITEONLY				D3DUSAGE_WRITEONLY

enum SOC_POOL
{
	SOC_POOL_DEFAULT,
	SOC_POOL_MANAGED
};

enum SOC_TRIANGLE
{
	SOC_TRIANGLE_LIST = D3DPT_TRIANGLELIST,
	SOC_TRIANGLE_STRIP = D3DPT_TRIANGLESTRIP
};

//typedef VOID				SOC_void;
typedef CHAR				SOC_char;
typedef unsigned int		SOC_enum;
typedef BOOL				SOC_bool;
typedef unsigned int		SOC_bitfield;
typedef BYTE				SOC_byte;
typedef SHORT				SOC_short;
typedef WORD				SOC_word;
typedef INT					SOC_int;
typedef DWORD				SOC_dword;
typedef SIZE_T				SOC_sizei;
typedef USHORT				SOC_ushort;
typedef UWORD				SOC_uword;
typedef UINT				SOC_uint;
typedef FLOAT				SOC_float;
typedef float				SOC_clampf;
typedef FIXED				SOC_fixed;

typedef PINT				SOC_intptr;
typedef PSIZE_T				SOC_sizeiptr;

//typedef INT64				SOC_int64;
//typedef INT64				SOC_qword;
//typedef UINT64				SOC_uint64;
//typedef UINT64				SOC_uqword;

typedef double				SOC_double;

typedef LPDIRECT3DTEXTURE9			 DeviceTexture;
typedef LPDIRECT3DVERTEXBUFFER9		 DeviceVertexBuffer;
typedef LPDIRECT3DINDEXBUFFER9		 DeviceIndexBuffer;
typedef LPDIRECT3DVERTEXDECLARATION9 VertexDeclaration;

#elif defined(__APPLE__) || defined(_USE_GL_DEFINES)

#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#define ALIGN(x)			__attribute__((aligned(x)))

#if defined(WIN32)

#include <Windows.h>
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#define ALIGN(x)			__declspec(align(x))
#endif

#define SOC_FMT_R8G8B8		D3DFMT_R8G8B8
#define SOC_FMT_A8R8G8B8	D3DFMT_A8R8G8B8

#define SOC_FMT_A4R4G4B4	D3DFMT_A4R4G4B4
#define SOC_FMT_A8			D3DFMT_A8

#define SOC_FMT_X4R4G4B4	D3DFMT_X4R4G4B4
#define SOC_FMT_A8B8G8R8	D3DFMT_A8B8G8R8

#define SOC_FMT_G16R16		 D3DFMT_G16R16
#define SOC_FMT_A16B16G16R16 D3DFMT_A16B16G16R16

#define SOC_FMT_D32			D3DFMT_D32
#define SOC_FMT_D24X8		D3DFMT_D24X8
#define SOC_FMT_D16			D3DFMT_D16
#define SOC_FMT_VERTEXDATA	D3DFMT_VERTEXDATA
#define SOC_FMT_INDEX16		D3DFMT_INDEX16
#define SOC_FMT_INDEX32		D3DFMT_INDEX32

#define SOC_FMT_R16F		D3DFMT_R16F
#define SOC_FMT_R32F		D3DFMT_R32F
#define SOC_FMT_G32R32F		D3DFMT_G32R32F

#define SOC_USAGE_DEPTHSTENCIL			D3DUSAGE_DEPTHSTENCIL
#define SOC_USAGE_DMAP					D3DUSAGE_DMAP
#define SOC_USAGE_DONOTCLIP				D3DUSAGE_DONOTCLIP
#define SOC_USAGE_DYNAMIC				D3DUSAGE_DYNAMIC
#define SOC_USAGE_RENDERTARGET			D3DUSAGE_RENDERTARGET
#define SOC_USAGE_SOFTWAREPROCESSING	D3DUSAGE_SOFTWAREPROCESSING
#define SOC_USAGE_WRITEONLY				D3DUSAGE_WRITEONLY

enum SOC_POOL
{
	SOC_POOL_DEFAULT,
	SOC_POOL_MANAGED
};

enum SOC_TRIANGLE
{
	SOC_TRIANGLE_LIST,
	SOC_TRIANGLE_STRIP
};

typedef GLvoid				SOC_void;
typedef GLbyte				SOC_char;
typedef GLenum				SOC_enum;
typedef GLboolean			SOC_bool;
typedef GLbitfield			SOC_bitfield;
typedef GLubyte				SOC_byte;
typedef GLshort				SOC_short;
typedef GLushort			SOC_word;
typedef GLint				SOC_int;
typedef GLuint				SOC_dword;
typedef GLsizei				SOC_sizei;
typedef GLushort			SOC_ushort;
typedef GLuint				SOC_uint;
typedef GLfloat 			SOC_float;
typedef GLclampf			SOC_clampf;
typedef unsigned long		SOC_fixed;

typedef GLint*				SOC_intptr;
typedef GLsizei*			SOC_sizeiptr;

typedef double				SOC_float16;
typedef double				SOC_double;

//typedef GLint64				SOC_int64;
//typedef GLint64				SOC_qword;
//typedef GLuint64			SOC_uint64;
//typedef GLuint64			SOC_uqword;

typedef void*						 DeviceTexture;
typedef void*						 DeviceVertexBuffer;
typedef void*						 DeviceIndexBuffer;
typedef void* 						 VertexDeclaration;

#endif