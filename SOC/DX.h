#pragma once

#include "GraphicsForm.h"
#include "Windows.h"
#include "SOCHashMap.h"
#include <string>

namespace Device
{
	namespace Graphics
	{
		class DX : public GraphicsForm
		{
		private:
			SOCHashMap<const char *, LPDIRECT3DVERTEXDECLARATION9> declMap;

		private:
			LPDIRECT3D9			d3dHandle;
			LPDIRECT3DDEVICE9	device;

			D3DPRESENT_PARAMETERS d3dpp;

		public:
			DX(PRESENT_INTERVAL interval, Application::Application *app);
			~DX(void);

		public:
			bool DX::Initialize();

		public:
			bool Clear(unsigned int count, const Common::Rect<int> *rect, clearFlag flags, Rendering::Color &color, float z, unsigned int stencil);
			bool Clear(clearFlag flags, Rendering::Color &color);

			bool CreateVertexBuffer(int bufferLength, SOC_dword usage, SOC_POOL pool, DeviceVertexBuffer* outDeviceBuffer);
			bool CreateIndexBuffer(int bufferLength, SOC_POOL pool, DeviceIndexBuffer* outDeviceBuffer);
			VertexDeclaration CreateVertexDeclation( VertexElements *ve );

			bool SetIndices( DeviceIndexBuffer indexBuffer );
			bool SetVertexStream(SOC_uint stream, DeviceVertexBuffer deviceVertexBuffer, SOC_uint stride);
			bool SetVertexStremFrequency(SOC_uint stream, SOC_uint frequency);
			bool SetVertexDeclaration( const char *description );
			bool SetVertexDeclaration( VertexDeclaration decl );

			bool DrawIndexedPrimitive(SOC_TRIANGLE type, SOC_int baseVertexIdx, SOC_uint minVertexIdx, SOC_uint numVertices, SOC_uint startIdx, SOC_uint primitiveCount);

			bool BeginScene();
			bool EndScene();
			void Present();

		public:
			LPDIRECT3DDEVICE9 GetD3DDevice();
		};

	}
}