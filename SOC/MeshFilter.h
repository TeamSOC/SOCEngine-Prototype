#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include "AABB.h"
#include "Color.h"
//#include <NvTriStrip.h>
#include "Utility.h"
#include "Math.h"

namespace Rendering
{
	class MeshFilter
	{
	public:
		typedef int size;
		enum TRIANGLES_TYPE { TRIANGLE_TYPE_LIST, TRIANGLE_TYPE_STRIP };

	private:
		SOC_Vector3* vertices;
		SOC_Vector3* normals;

		SOC_Vector2* uv;
		SOC_Vector2* uv2;

		SOC_Vector3* tangents;
		SOC_Vector3* binomals;

		Color *colors;

		std::pair<size, WORD*>  indices;

		LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
		LPDIRECT3DINDEXBUFFER9 indexBuffer;

		int			vertexBufferSize;
		int			numOfVertex;

		float				radius;
		Intersection::AABB  bounds;

		TRIANGLES_TYPE triangleType;

	public:
		MeshFilter(void) : vertices(NULL), normals(NULL), uv(NULL), uv2(NULL), tangents(NULL), binomals(NULL), colors(NULL)
		{
			vertexBufferSize = 0;
			numOfVertex = 0;
			radius = 0.0f;
			triangleType = TRIANGLE_TYPE_LIST;
		}

		~MeshFilter()
		{
		}

	public:
		void CalcVertexBufferSize()
		{
			vertexBufferSize = sizeof(SOC_Vector3) * 2;
			//vertex, normal는  기본 ㅇㅇ.

			if(uv) 				vertexBufferSize += sizeof(SOC_Vector2);
			if(uv2)				vertexBufferSize += sizeof(SOC_Vector2);

			if(tangents)		vertexBufferSize += sizeof(SOC_Vector3);
			if(binomals)		vertexBufferSize += sizeof(SOC_Vector3);

			if(colors)			vertexBufferSize += sizeof(SOC_Vector4);
		}

		template <typename VertexBufferData, typename CreateType>
		bool SetData(VertexBufferData data, VertexBufferData inputData, CreateType createType)
		{
			if(inputData == NULL)
				return false;

			Utility::SAFE_ARRARY_DELETE(data);
			data = new CreateType[this->numOfVertex];

			for(int i=0; i<numOfVertex; ++i)
				data[i] = inputData[i];

			return true;
		}

		bool Create(SOC_Vector3 *vertices, SOC_Vector3 *normals, SOC_Vector2 *uv, SOC_Vector2 *uv2,	SOC_Vector3 *tangents, SOC_Vector3 *binomals, Color *colors, int numOfVertex, std::pair<size, WORD*> indices, TRIANGLES_TYPE type, bool isDynamic, LPDIRECT3DDEVICE9 device)
		{
			if(vertices == NULL || normals == NULL) return false;

			this->triangleType = type;
			this->numOfVertex = numOfVertex;

			SetData(this->vertices, vertices, SOC_Vector3());
			SetData(this->normals, normals, SOC_Vector3());
			SetData(this->uv, uv, SOC_Vector2());

			SetData(this->indices.second, indices.second, WORD(0));
			this->indices.first = indices.first;

			if(uv != NULL)
				SetData(this->uv2, uv2, SOC_Vector2());

			if(tangents && binomals)
			{
				SetData(this->tangents, tangents, SOC_Vector3());
				SetData(this->binomals, binomals, SOC_Vector3());
			}

			SetData(this->colors, colors, Color());

			CalcVertexBufferSize();

			if( CreateVertexBuffer(device, isDynamic) == false )
				return false;

			if( CreateIndexBuffer(device) == false )
				return false;

			return true; 
		}

		bool CreateVertexBuffer(LPDIRECT3DDEVICE9 device, bool isDynamic)
		{
			DWORD usage = D3DUSAGE_WRITEONLY | (isDynamic ? D3DUSAGE_DYNAMIC : 0);
			if( FAILED(device->CreateVertexBuffer( numOfVertex * vertexBufferSize, usage, 0, D3DPOOL_DEFAULT, &vertexBuffer, NULL)) )
				return false;

			void *vertexBufferData;

			if( FAILED(vertexBuffer->Lock( 0, numOfVertex * vertexBufferSize, &vertexBufferData, NULL)) )
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

				*( (SOC_Vector3*)vertexBufferData ) = normals[i];
				vertexBufferData = (SOC_Vector3*)vertexBufferData + 1;

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

				if(tangents && binomals) //노멀 맵핑을 생각했을 때, 둘다 붙어다니지 않나? 붙음 ㅇ
				{
					*( (SOC_Vector3*)vertexBufferData ) = tangents[i];
					vertexBufferData = (SOC_Vector3*)vertexBufferData + 1;

					*( (SOC_Vector3*)vertexBufferData ) = binomals[i];
					vertexBufferData = (SOC_Vector3*)vertexBufferData + 1;
				}

			}

			vertexBuffer->Unlock();
			radius = maxRadius;
			bounds.SetMinMax(minSize, maxSize);

			return true;
		}
		bool CreateIndexBuffer(LPDIRECT3DDEVICE9 device)
		{
			if( FAILED( device->CreateIndexBuffer(0, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indexBuffer, NULL) ) )
				return false;

			WORD *indexBufferData;
			int indicesCount = this->indices.first;

			if( FAILED( indexBuffer->Lock( sizeof(WORD) * indicesCount, 0, (void**)&indexBufferData, NULL) ) )
				return false;

			memcpy(indexBufferData, this->indices.second, sizeof(WORD) * indicesCount);
			indexBuffer->Unlock();

			return true;
		}
	};

}