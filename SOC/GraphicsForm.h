#pragma once

#include "Application.h"
#include "Utility.h"
#include "Color.h"
#include "Device.h"
#include "VertexDeclaration.h"

namespace Device
{
	namespace Graphics
	{
		class GraphicsForm
		{
		public:
			enum CLEAR_FLAG
			{
				CLEAR_FLAG_TARGET	= 1,
				CLEAR_FLAG_ZBUFFER	= 2,
				CLEAR_FLAG_STENCIL	= 4
			};

			typedef unsigned int clearFlag;

		public:
			GraphicsForm(PRESENT_INTERVAL interval, Application::Application* app);
			virtual ~GraphicsForm() = 0;

		public:
			virtual bool Initialize() = 0;

		public:
			virtual bool Clear(clearFlag flags, Rendering::Color &color) = 0;
			virtual bool Clear(unsigned int count, const Common::Rect<int> *rect, clearFlag flags, Rendering::Color &color, float z, unsigned int stencil) = 0;

			virtual bool CreateVertexBuffer(int bufferLength, SOC_dword usage, SOC_POOL pool, DeviceVertexBuffer* outBuffer) = 0;
			virtual bool CreateIndexBuffer(int bufferLength, SOC_POOL pool, DeviceIndexBuffer* outBuffer) = 0;
			virtual bool SetIndices( DeviceIndexBuffer indexBuffer ) = 0;
			virtual bool DrawIndexedPrimitive(SOC_TRIANGLE type, SOC_int baseVertexIdx, SOC_uint minVertexIdx, SOC_uint numVertices, SOC_uint startIdx, SOC_uint primitiveCount) = 0;
			virtual bool SetVertexStream(SOC_uint stream, DeviceVertexBuffer deviceVertexBuffer, SOC_uint vertexBufferSize) = 0;
			virtual bool SetVertexStremFrequency(SOC_uint stream, SOC_uint frequency) = 0;

			virtual VertexDeclaration CreateVertexDeclation( VertexElements *ve ) = 0;
			virtual bool SetVertexDeclaration( const char *description ) = 0;
			virtual bool SetVertexDeclaration( VertexDeclaration decl ) = 0;

			virtual bool BeginScene() = 0;
			virtual bool EndScene() = 0;
			virtual void Present() = 0;
		};
	}
}