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
			enum ClearFlagType
			{
				FlagTarget	= 1,
				FlagZBuffer	= 2,
				FlagStencil	= 4
			};

			typedef SOC_dword ClearFlag;

		public:
			GraphicsForm(PresentInterval interval, Application::Application* app);
			virtual ~GraphicsForm() = 0;

		public:
			virtual bool Initialize() = 0;

		public:
			virtual bool Clear(ClearFlag flags, Rendering::Color &color) = 0;
			virtual bool Clear(unsigned int count, const Common::Rect<int> *rect, ClearFlag flags, Rendering::Color &color, float z, unsigned int stencil) = 0;

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