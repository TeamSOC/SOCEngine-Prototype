#pragma once

#include "DeviceDirector.h"
#include "AABB.h"
#include "Color.h"
#include "Utility.h"
#include "Math.h"
#include "Buffer.h"

namespace Rendering
{
	namespace Mesh
	{
		class MeshFilter
		{
		public:
			typedef int count;

		private:
			SOC_Vector3* vertices;
			SOC_Vector3* normals;

			SOC_Vector2* uv;
			SOC_Vector2* uv2;

			SOC_Vector3* tangents;
			SOC_Vector3* binomals;

			Color *colors;

			std::pair<count, SOC_dword*>  indices;

			Buffer::VertexBuffer	*vertexBuffer;
			Buffer::IndexBuffer		*indexBuffer;

			int			vertexBufferSize;
			int			numOfVertex;

			float				radius;
			Intersection::AABB  bounds;

			SOC_TRIANGLE triangleType;

		public:
			MeshFilter(void) : vertices(NULL), normals(NULL), uv(NULL), uv2(NULL), tangents(NULL), binomals(NULL), colors(NULL)
			{
				vertexBufferSize = 0;
				numOfVertex = 0;
				radius = 0.0f;
				triangleType = SOC_TRIANGLE_LIST;

				vertexBuffer = nullptr;
				indexBuffer = nullptr;
			}

			~MeshFilter()
			{
			}

		private:
			void CalcVertexBufferSize()
			{
				vertexBufferSize = sizeof(SOC_Vector3);

				if(normals)			vertexBufferSize += sizeof(SOC_Vector3);
				if(uv) 				vertexBufferSize += sizeof(SOC_Vector2);
				if(uv2)				vertexBufferSize += sizeof(SOC_Vector2);

				if(tangents)		vertexBufferSize += sizeof(SOC_Vector3);
				if(binomals)		vertexBufferSize += sizeof(SOC_Vector3);

				if(colors)			vertexBufferSize += sizeof(SOC_Vector4);
			}

			template <typename VertexBufferData, typename CreateType>
			bool SetVertexData(VertexBufferData *out, VertexBufferData inputData, CreateType createType)
			{
				if(inputData == NULL)
					return false;

				Utility::SAFE_ARRARY_DELETE(*out);
				*out = new CreateType[this->numOfVertex];
				memcpy(*out, inputData, sizeof(CreateType) * numOfVertex);

				//for(int i=0; i<numOfVertex; ++i)
				//{
				//	data[i] = inputData[i];					
				//}
				return true;
			}

		public:
			bool Create(SOC_Vector3 *vertices, SOC_Vector3 *normals, SOC_Vector2 *uv, SOC_Vector2 *uv2,	SOC_Vector3 *tangents, SOC_Vector3 *binomals, Color *colors, int numOfVertex, std::pair<count, SOC_dword*> indices, SOC_TRIANGLE type, bool isDynamic)
			{
				if(vertices == NULL ) return false;

				this->triangleType = type;
				this->numOfVertex = numOfVertex;

				SetVertexData(&this->vertices, vertices, SOC_Vector3());
				SetVertexData(&this->normals, normals, SOC_Vector3());
				SetVertexData(&this->uv, uv, SOC_Vector2());

				if(uv != NULL)
					SetVertexData(&this->uv2, uv2, SOC_Vector2());

				SetVertexData(&this->tangents, tangents, SOC_Vector3());
				SetVertexData(&this->binomals, binomals, SOC_Vector3());
				SetVertexData(&this->colors, colors, Color());

				CalcVertexBufferSize();

				//SetData(&this->indices.second, indices.second, SOC_word(0));
				//this->indices.first = indices.first;

				this->indices.second = new SOC_dword[indices.first];
				this->indices.first = indices.first;
				memcpy(this->indices.second, indices.second, sizeof(SOC_dword) * indices.first);

				if(vertexBuffer || indexBuffer)
				{
					Utility::SAFE_DELETE(vertexBuffer);
					Utility::SAFE_DELETE(indexBuffer);
				}

				Device::Graphics::GraphicsForm *gp = Device::DeviceDirector::GetInstance()->GetGraphics();

				vertexBuffer = new Buffer::VertexBuffer( vertexBufferSize, numOfVertex, gp );
				indexBuffer = new Buffer::IndexBuffer( indices.first, gp);

				if( CreateVertexBuffer(isDynamic) == false )
					return false;

				if( CreateIndexBuffer() == false )
					return false;

				return true; 
			}

		private:
			bool CreateVertexBuffer(bool isDynamic)
			{
				SOC_dword usage = SOC_USAGE_WRITEONLY | (isDynamic ? SOC_USAGE_DYNAMIC : 0);

				if( vertexBuffer->Create( usage, SOC_POOL_MANAGED) == false )
					return false;

				void *vertexBufferData = nullptr;
				if( vertexBuffer->Lock(&vertexBufferData) == false )
					return false;

				float maxRadius = 0.0f;
				float rad = 0.0f;
				SOC_Vector3 minSize(0, 0, 0), maxSize(0, 0, 0);

				for(int i=0; i<numOfVertex; ++i)
				{
					*( (SOC_Vector3*)vertexBufferData ) = vertices[i];
					vertexBufferData = (SOC_Vector3*)vertexBufferData + 1;

					/* calculate radius */
					rad = Math::Tool::Distance(SOC_Vector3(0, 0, 0), vertices[i]);

					if( maxRadius < rad )
						maxRadius = rad;
					/* end */

					/* calculate AABB */

					for(int j=0; j<3; ++j)
					{
						if(minSize[j] > vertices[i][j])	minSize[j] = vertices[i][j];
						else if(maxSize[j] < vertices[i][j]) maxSize[j] = vertices[i][j];
					}

					/* end */
					if(normals)
					{
						*( (SOC_Vector3*)vertexBufferData ) = normals[i];
						vertexBufferData = (SOC_Vector3*)vertexBufferData + 1;
					}

					if(uv)
					{
						*( (SOC_Vector2*)vertexBufferData ) = uv[i];
						vertexBufferData = (SOC_Vector2*)vertexBufferData + 1;

						if(uv2) //uv가 없으면 uv2도 없는거임 ㅇㅇ
						{
							*( (SOC_Vector2*)vertexBufferData ) = uv2[i];
							vertexBufferData = (SOC_Vector2*)vertexBufferData + 1;
						}
					}

					if(colors)
					{
						SOC_Vector4 vec4 = SOC_Vector4(colors[i].r, colors[i].g, colors[i].b, colors[i].a);
						*( (SOC_Vector4*)vertexBufferData ) = vec4;
						vertexBufferData = (SOC_Vector4*)vertexBufferData + 1;
					}

					if(tangents && binomals)
					{
						*( (SOC_Vector3*)vertexBufferData ) = tangents[i];
						vertexBufferData = (SOC_Vector3*)vertexBufferData + 1;

						*( (SOC_Vector3*)vertexBufferData ) = binomals[i];
						vertexBufferData = (SOC_Vector3*)vertexBufferData + 1;
					}

				}

				if( vertexBuffer->UnLock() == false)
					return false;
				radius = maxRadius;
				bounds.SetMinMax(minSize, maxSize);

				return true;
			}
			bool CreateIndexBuffer()
			{
				if( indexBuffer->Create(SOC_POOL_MANAGED) == false)
					return false;

				WORD *indexBufferData = nullptr;
				if( indexBuffer->Lock((void**)&indexBufferData) == false)
					return false;

				memcpy(indexBufferData, this->indices.second, sizeof(SOC_dword) * indexBuffer->GetCount());
				if( indexBuffer->UnLock() == false)
					return false;

				return true;
			}

		public:
			Buffer::VertexBuffer* GetVertexBuffer()
			{
				return vertexBuffer;
			}
			Buffer::IndexBuffer* GetIndexBuffer()
			{
				return indexBuffer;
			}
			int GetNumOfVertex()
			{
				return numOfVertex;
			}
			int GetTriangleCount()
			{
				return indices.first / 3;
			}
			SOC_TRIANGLE GetTriangleType()
			{
				return triangleType;
			}
		};

	}

}