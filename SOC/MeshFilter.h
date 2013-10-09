#pragma once

#include "DeviceDirector.h"
#include "AABB.h"
#include "Color.h"
#include "Utility.h"
#include "Math.h"
#include "Buffer.h"
#include "VertexBufferElements.h"

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

			SOC_Vector3* tangents;
			SOC_Vector3* binomals;

			std::pair<count, SOC_Vector2**> texcoords;

			Color *colors;

			std::pair<count, SOC_word*>  indices;

			Buffer::VertexBuffer	*vertexBuffer;
			Buffer::IndexBuffer		*indexBuffer;

			int			vertexBufferSize;
			int			numOfVertex;
			int			numOfTriangle;

			float				radius;
			Intersection::AABB  bounds;

			SOC_TRIANGLE triangleType;

		private:
			Device::Graphics::GraphicsForm	*graphics;
			VertexDeclaration				decl;

		public:
			MeshFilter(Device::Graphics::GraphicsForm *graphics);
			~MeshFilter();

		private:
			void CalcVertexBufferSize();
			template <typename VertexBufferData, typename CreateType>
			bool SetVertexData(VertexBufferData *out, VertexBufferData inputData, CreateType createType, bool alloc)
			{
				if(inputData == NULL)
					return false;

				if(alloc == false)
					*out = inputData;
				else
				{
					*out = new CreateType[this->numOfVertex];
					memcpy(*out, inputData, sizeof(CreateType) * numOfVertex);
				}
		
				return true;
			}

		public:
			bool Create(VertexBufferElements &option, bool alloc);
			bool Create(SOC_Vector3 *vertices, SOC_Vector3 *normals, SOC_Vector3 *tangents,
						SOC_Vector3 *binomals, std::pair<count, SOC_Vector2**> texcoords, Color *colors, 
						int numOfVertex, int numOfTriangle, std::pair<count, SOC_word*> indices, SOC_TRIANGLE type, bool isDynamic, bool alloc);

		private:
			bool CreateVertexBuffer(bool isDynamic);
			bool CreateIndexBuffer();
			VertexDeclaration CreateVertexDeclaration();

		public:
			Buffer::VertexBuffer* GetVertexBuffer();
			Buffer::IndexBuffer* GetIndexBuffer();
			int GetNumOfVertex();
			int GetNumOfTriangle();
			SOC_TRIANGLE GetTriangleType();
			VertexDeclaration GetDeclaration();
		};

	}

}