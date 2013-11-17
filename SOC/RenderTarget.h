#pragma once

#include "RenderingMath.h"
#include "Buffer.h"
#include <vector>
#include "Texture.h"

namespace Rendering
{
	namespace Texture
	{
		class RenderTarget
		{
		private:			
			Buffer::VertexBuffer *vertexBuffer;
			Buffer::IndexBuffer  *indexBuffer;
			VertexDeclaration decl;
			Texture *texture;

		public:
			RenderTarget(void)
			{
			}

			~RenderTarget(void)
			{
				Utility::SAFE_DELETE(vertexBuffer);
				Utility::SAFE_DELETE(indexBuffer);

				decl->Release();
			}

		public:
			bool Create(int width, int height)
			{
				Device::Graphics *graphics = Device::DeviceDirector::GetInstance()->GetGraphics();

				vertexBuffer = new Buffer::VertexBuffer( sizeof(SOC_Vector3) + sizeof(SOC_Vector2) , 4, graphics );
				indexBuffer = new Buffer::IndexBuffer(6, graphics );

				if( CreateVertexBuffer() == false )
					return false;

				if( CreateIndexBuffer() == false )
					return false;

				if( CreateVertexDeclaration(graphics, &decl) == false )
					return false;

				texture = new Texture;
				texture->Create(width, height);

				return true;
			}

		private:
			bool CreateVertexDeclaration(Device::Graphics *graphics, VertexDeclaration *out)
			{
				VertexDeclarationElements ves;

				VertexDeclarationElement e;
				std::vector<VertexDeclarationElement> *decls = &ves.vertexElement;
				
				e = VertexDeclarationElement(0, 0, SOC_VERTEX_DECLTYPE_FLOAT3, SOC_VERTEX_USAGE_POSITION, 0);
				decls->push_back(e);

				e.offset = sizeof(SOC_Vector3);
				e.type = SOC_VERTEX_DECLTYPE_FLOAT2;
				e.usage = SOC_VERTEX_USAGE_TEXCOORD;
				decls->push_back(e);

				ves.description = "RTR";
				(*out) = graphics->CreateVertexDeclation(&ves);

				return true;
			}

			bool CreateVertexBuffer()
			{
				if( vertexBuffer->Create(SOC_USAGE_WRITEONLY, SOC_POOL_DEFAULT) == false )
					return false;

				void *vertexBufferData = nullptr;
				if( vertexBuffer->Lock(&vertexBufferData) == false )
					return false;

				*((SOC_Vector3*)vertexBufferData) = SOC_Vector3(-1, 1, 0);
				vertexBufferData = (SOC_Vector3*)vertexBufferData + 1;
				*((SOC_Vector2*)vertexBufferData) = SOC_Vector2(0, 0);
				vertexBufferData = (SOC_Vector2*)vertexBufferData + 1;

				*((SOC_Vector3*)vertexBufferData) = SOC_Vector3(1, 1, 0);
				vertexBufferData = (SOC_Vector3*)vertexBufferData + 1;
				*((SOC_Vector2*)vertexBufferData) = SOC_Vector2(1, 0);
				vertexBufferData = (SOC_Vector2*)vertexBufferData + 1;

				*((SOC_Vector3*)vertexBufferData) = SOC_Vector3(1, -1, 0);
				vertexBufferData = (SOC_Vector3*)vertexBufferData + 1;
				*((SOC_Vector2*)vertexBufferData) = SOC_Vector2(1, 1);
				vertexBufferData = (SOC_Vector2*)vertexBufferData + 1;

				*((SOC_Vector3*)vertexBufferData) = SOC_Vector3(-1, -1, 0);
				vertexBufferData = (SOC_Vector3*)vertexBufferData + 1;
				*((SOC_Vector2*)vertexBufferData) = SOC_Vector2(0, 1);
				vertexBufferData = (SOC_Vector2*)vertexBufferData + 1;

				if( vertexBuffer->UnLock() == false )
					return false;

				return true;
			}

			bool CreateIndexBuffer()
			{
				if( indexBuffer->Create(SOC_POOL_DEFAULT) == false )
					return false;

				SOC_word *data = nullptr;
				if( indexBuffer->Lock((void**)&data) == false )
					return false;

				*data++ = 0; *data++ = 1; *data++ = 2;
				*data++ = 0; *data++ = 2; *data++ = 3;

				if( indexBuffer->UnLock() == false )
					return false;

				return true;
			}
		};

	}
}