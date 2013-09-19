#include "GL.h"

namespace Device
{
	namespace Graphics
	{
		GL::GL(PRESENT_INTERVAL interval, Application::Application *app)
		: GraphicsForm(interval, app)
		{
		}
		
		GL::~GL(void)
		{
		}
		
		bool GL::Initialize()
		{
			return false;
		}
		
		bool GL::Clear(unsigned int count, const Common::Rect<int> *rect, clearFlag flags, Rendering::Color &color, float z, unsigned int stencil)
		{
			return false;
		}
		
		bool GL::Clear(clearFlag flags, Rendering::Color &color)
		{
			return false;
		}
		
		bool GL::CreateVertexBuffer(int bufferLength, SOC_dword usage, SOC_POOL pool, DeviceVertexBuffer* outDeviceBuffer)
		{
			return false;
		}
		
		bool GL::CreateIndexBuffer(int bufferLength, SOC_POOL pool, DeviceIndexBuffer* outDeviceBuffer)
		{
			return false;
		}
		
		bool GL::SetIndices( DeviceIndexBuffer indexBuffer )
		{
			return false;
		}
		
		bool GL::DrawIndexedPrimitive(SOC_TRIANGLE type, SOC_int baseVertexIdx, SOC_uint minVertexIdx, SOC_uint numVertices, SOC_uint startIdx, SOC_uint primitiveCount)
		{
			return false;
		}
		
		bool GL::SetVertexStream(SOC_uint stream, DeviceVertexBuffer deviceVertexBuffer, SOC_uint stride)
		{
			return false;
		}
		
		bool GL::SetVertexStremFrequency(SOC_uint stream, SOC_uint frequency)
		{
			return false;
		}
		
		VertexDeclaration GL::CreateVertexDeclation( VertexElements *ve )
		{
			return false;
		}
		
		bool GL::SetVertexDeclaration( const char *description )
		{
			return false;
		}
		
		bool GL::SetVertexDeclaration( VertexDeclaration decl )
		{
			return false;
		}
		
		
		bool GL::BeginScene()
		{
			return false;
		}
		
		bool GL::EndScene()
		{
			return false;
		}
		
		void GL::Present()
		{
		}
	}
}