#pragma once

#include "DeviceDirector.h"
#include "AABB.h"
#include "Color.h"
#include "Utility.h"
#include "Math.h"
#include "Buffer.h"
#include "VBElements.h"

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
			SOC_Vector3* binormals;

			std::pair<count, SOC_Vector2**> texcoords;

			Color *colors;

			std::pair<count, SOC_word*>  indices;

			Buffer::VertexBuffer	*vertexBuffer;
			Buffer::IndexBuffer		*indexBuffer;

			int			vertexBufferSize;
			int			numOfVertex;
			int			numOfTriangle;

			SOC_TRIANGLE triangleType;

		private:
			Device::Graphics	*graphics;
			VertexDeclaration				decl;

		public:
			MeshFilter(Device::Graphics *graphics);
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
			bool Create(VBElements &option, bool alloc);
			bool Create(SOC_Vector3 *vertices, SOC_Vector3 *normals, SOC_Vector3 *tangents,
						SOC_Vector3 *binormals, std::pair<count, SOC_Vector2**> texcoords, Color *colors, 
						int numOfVertex, int numOfTriangle, std::pair<count, SOC_word*> indices, SOC_TRIANGLE type, bool isDynamic, bool alloc);

		private:
			bool CreateVertexBuffer(bool isDynamic);
			bool CreateIndexBuffer();
			bool CreateVertexDeclaration(VertexDeclaration *out);

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