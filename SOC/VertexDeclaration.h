#pragma once

#include "Device.h"
#include <string>
#include <vector>

//vertex decl only use d3d.

enum SOC_VERTEX_DECLTYPE
{
    SOC_VERTEX_DECLTYPE_FLOAT1 = 0,
    SOC_VERTEX_DECLTYPE_FLOAT2,
    SOC_VERTEX_DECLTYPE_FLOAT3,
    SOC_VERTEX_DECLTYPE_FLOAT4,
    SOC_VERTEX_DECLTYPE_COLOR,
    SOC_VERTEX_DECLTYPE_UBYTE4,
    SOC_VERTEX_DECLTYPE_SHORT2,
    SOC_VERTEX_DECLTYPE_SHORT4,
    SOC_VERTEX_DECLTYPE_UBYTE4N,
    SOC_VERTEX_DECLTYPE_SHORT2N,
    SOC_VERTEX_DECLTYPE_SHORT4N,
    SOC_VERTEX_DECLTYPE_USHORT2N,
    SOC_VERTEX_DECLTYPE_USHORT4N,
    SOC_VERTEX_DECLTYPE_UDEC3,
    SOC_VERTEX_DECLTYPE_DEC3N,
    SOC_VERTEX_DECLTYPE_FLOAT16_2,
    SOC_VERTEX_DECLTYPE_FLOAT16_4,
    SOC_VERTEX_DECLTYPE_UNUSED
};

enum SOC_VERTEX_USAGE
{
    SOC_VERTEX_USAGE_POSITION = 0,		// 0
    SOC_VERTEX_USAGE_NORMAL   = 3,      // 3
    SOC_VERTEX_USAGE_TEXCOORD = 5,      // 5
    SOC_VERTEX_USAGE_TANGENT  = 6,      // 6
    SOC_VERTEX_USAGE_BINORMAL = 7,      // 7
    SOC_VERTEX_USAGE_COLOR	  = 10,     // 10
};

struct VertexElement
{
	SOC_byte stream;
	SOC_byte offset;
	SOC_VERTEX_DECLTYPE type;
	SOC_VERTEX_USAGE usage;
	SOC_byte usageIndex;

	VertexElement() : stream(0), offset(0), type((SOC_VERTEX_DECLTYPE)0), usage((SOC_VERTEX_USAGE)0), usageIndex(0)
	{}
	VertexElement(SOC_byte stream, SOC_byte offset, SOC_VERTEX_DECLTYPE type, SOC_VERTEX_USAGE usage, SOC_byte usageIndex)
	{
		this->stream	 = stream;
		this->offset	 = offset;
		this->type		 = type;
		this->usageIndex = usageIndex;
		this->usage		 = usage;
	}

#if defined(WIN32) && !defined(_USE_GL_DEFINES)

	void GetD3DElemnts(D3DVERTEXELEMENT9 *vertexElement)
	{
		vertexElement->Method	  = D3DDECLMETHOD_DEFAULT;
		vertexElement->Stream	  = stream;
		vertexElement->Offset	  = offset;
		vertexElement->Type		  = (BYTE)type;
		vertexElement->Usage	  = (BYTE)usage;
		vertexElement->UsageIndex = usageIndex;
	}
#endif

};

struct VertexElements
{
	std::string description;
	std::vector<VertexElement> vertexElement;

	VertexElements()
	{}
	VertexElements( const char *description, std::vector<VertexElement> &ve )
	{
		this->description = description;
		this->vertexElement = ve;
	}
};

#if defined(WIN32) && !defined(_USE_GL_DEFINES)

typedef IDirect3DVertexDeclaration9 VertexDeclaration;

#elif defined(__APPLE__) || defined(_USE_GL_DEFINES)

typedef void* VertexDeclaration;

#endif