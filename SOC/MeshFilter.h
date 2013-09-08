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

			SOC_Vector3* tangents;
			SOC_Vector3* binomals;

			std::vector<SOC_Vector2*> texcoord;

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
			VertexDeclaration				*decl;

		public:
			MeshFilter(Device::Graphics::GraphicsForm *graphics);
			~MeshFilter();

		private:
			void CalcVertexBufferSize();
			template <typename VertexBufferData, typename CreateType>
			bool SetVertexData(VertexBufferData *out, VertexBufferData inputData, CreateType createType)
			{
				if(inputData == NULL)
					return false;

				Utility::SAFE_ARRARY_DELETE(*out);
				*out = new CreateType[this->numOfVertex];
				memcpy(*out, inputData, sizeof(CreateType) * numOfVertex);

				return true;
			}

		public:
			struct MeshFilterOption
			{
				SOC_Vector3 *vertices;
				SOC_Vector3 *normals;
				SOC_Vector3 *tangents;
				SOC_Vector3 *binomals;
				std::vector<SOC_Vector2*> *texcoord;
				Color *colors;
				int numOfVertex;
				int numOfTriangle;
				std::pair<count, SOC_word*> indices;
				SOC_TRIANGLE type;
				bool isDynamic;

				MeshFilterOption() : numOfTriangle(0), vertices(nullptr), normals(nullptr), tangents(nullptr), binomals(nullptr), texcoord(nullptr), colors(nullptr), numOfVertex(0), isDynamic(false){}
			};

		public:
			bool Create(MeshFilterOption &option);
			bool Create(SOC_Vector3 *vertices, SOC_Vector3 *normals, SOC_Vector3 *tangents,
						SOC_Vector3 *binomals, std::vector<SOC_Vector2*> *texcoord, Color *colors, 
						int numOfVertex, int numOfTriangle, std::pair<count, SOC_word*> indices, SOC_TRIANGLE type, bool isDynamic);

		private:
			bool CreateVertexBuffer(bool isDynamic);
			bool CreateIndexBuffer();
			VertexDeclaration* CreateVertexDeclaration();

		public:
			Buffer::VertexBuffer* GetVertexBuffer();
			Buffer::IndexBuffer* GetIndexBuffer();
			int GetNumOfVertex();
			int GetNumOfTriangle();
			SOC_TRIANGLE GetTriangleType();
			VertexDeclaration* GetDeclaration();
		};

	}

}