#pragma once

#include "RenderingMath.h"
#include "Buffer.h"
#include <vector>
#include "Texture.h"
#include "Shader.h"
#include <cassert>

namespace Rendering
{
	namespace Texture
	{
		class RenderTarget : public Texture
		{
		private:			
			Buffer::VertexBuffer *vertexBuffer;
			Buffer::IndexBuffer  *indexBuffer;
			VertexDeclaration decl;
			Shader::Shader *shader;

			Buffer::Surface *surface;

		public:
			RenderTarget()
			{
				vertexBuffer	= nullptr;
				indexBuffer		= nullptr;
				decl			= nullptr;
				shader			= nullptr;
				surface			= nullptr;
			}

			~RenderTarget(void)
			{
				Utility::SAFE_DELETE(vertexBuffer);
				Utility::SAFE_DELETE(indexBuffer);

				decl->Release();
			}

		public:
			bool Create(int width, int height, Shader::Shader *shader)
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

				this->shader = shader;

				if(FAILED(D3DXCreateTexture(graphics->GetD3DDevice(), width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &texture)))
					return false;

				size.w = width;
				size.h = height;

				surface = new Buffer::Surface(graphics);

				return true;
			}

			void GetRenderTarget(SOC_uint renderTargetIdx)
			{
				surface->GetRenderTarget(renderTargetIdx);
			}

			void SetRenderTarget(SOC_uint renderTargetIdx)
			{
				surface->SetRenderTarget(renderTargetIdx);
			}

			void GetSurfaceLevel(SOC_uint level=0)
			{
				surface->GetSurfaceLevel(texture, level);
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