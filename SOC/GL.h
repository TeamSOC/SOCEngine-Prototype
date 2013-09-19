//
//  GL.h
//  Rendering
//
//  Created by Jiman Jeong on 13. 9. 17..
//  Copyright (c) 2013년 SOC. All rights reserved.
//

#ifndef Rendering_GL_h
#define Rendering_GL_h

#include "GraphicsForm.h"
#include "SOCHashMap.h"
#include <string>

namespace Device
{
	namespace Graphics
	{
		class GL : public GraphicsForm
		{
		public:
			GL(PRESENT_INTERVAL interval, Application::Application* app);
			virtual ~GL();
			
		public:
			virtual bool Initialize();
			
		public:
			virtual bool Clear(clearFlag flags, Rendering::Color &color);
			virtual bool Clear(unsigned int count, const Common::Rect<int> *rect, clearFlag flags, Rendering::Color &color, float z, unsigned int stencil);
			
		public:
			virtual bool CreateVertexBuffer(int bufferLength, SOC_dword usage, SOC_POOL pool, DeviceVertexBuffer* outBuffer);
			virtual bool CreateIndexBuffer(int bufferLength, SOC_POOL pool, DeviceIndexBuffer* outBuffer);
			virtual bool SetIndices( DeviceIndexBuffer indexBuffer );
			virtual bool DrawIndexedPrimitive(SOC_TRIANGLE type, SOC_int baseVertexIdx, SOC_uint minVertexIdx, SOC_uint numVertices, SOC_uint startIdx, SOC_uint primitiveCount);
			virtual bool SetVertexStream(SOC_uint stream, DeviceVertexBuffer deviceVertexBuffer, SOC_uint vertexBufferSize);
			virtual bool SetVertexStremFrequency(SOC_uint stream, SOC_uint frequency);
			
		public:
			virtual VertexDeclaration CreateVertexDeclation( VertexElements *ve );
			virtual bool SetVertexDeclaration( const char *description );
			virtual bool SetVertexDeclaration( VertexDeclaration decl );
			
		public:
			virtual bool BeginScene();
			virtual bool EndScene();
			virtual void Present();
		};
		
	}
}

#endif
