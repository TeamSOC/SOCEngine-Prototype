#include "MeshFilter.h"

namespace Rendering
{
	namespace Mesh
	{
		MeshFilter::MeshFilter(Device::Graphics *graphics) : vertices(NULL), normals(NULL), tangents(NULL), binormals(NULL), colors(NULL), decl(nullptr)
		{
			vertexBufferSize = 0;
			numOfVertex = 0;
			numOfTriangle = 0;
			triangleType = SOC_TRIANGLE_LIST;

			vertexBuffer = nullptr;
			indexBuffer = nullptr;
			this->graphics = graphics;

			this->texcoords.first = 0;
			this->texcoords.second = nullptr;
		}
		MeshFilter::~MeshFilter()
		{
		}
		void MeshFilter::CalcVertexBufferSize()
		{
			vertexBufferSize = sizeof(SOC_Vector3);

			if(normals)			vertexBufferSize += sizeof(SOC_Vector3);

			//for(std::vector<SOC_Vector2*>::iterator iter = texcoord.begin(); iter != texcoord.end(); ++iter)
			//	vertexBufferSize += sizeof(SOC_Vector2);
			if(texcoords.second)
				vertexBufferSize += sizeof(SOC_Vector2) * texcoords.first;

			if(tangents)		vertexBufferSize += sizeof(SOC_Vector3);
			if(binormals)		vertexBufferSize += sizeof(SOC_Vector3);

			if(colors)			vertexBufferSize += sizeof(SOC_Vector4);
		}

		bool MeshFilter::Create(VBElements &option, bool alloc)
		{
			return Create(
				option.vertices, option.normals, 
				option.tangents, option.binormals, 
				option.texcoords, option.colors, 
				option.numOfVertex, option.numOfTriangle, 
				option.indices, option.type, 
				option.isDynamic, alloc);
		}

		bool MeshFilter::Create(SOC_Vector3 *vertices, SOC_Vector3 *normals, SOC_Vector3 *tangents,
			SOC_Vector3 *binormals, std::pair<count, SOC_Vector2**> texcoords, Color *colors, 
			int numOfVertex, int numOfTriangle, std::pair<count, SOC_word*> indices, SOC_TRIANGLE type, bool isDynamic, bool alloc)
		{
			if(vertices == NULL ) return false;

			this->triangleType = type;
			this->numOfVertex = numOfVertex;

			SetVertexData(&this->vertices, vertices, SOC_Vector3(), alloc);
			SetVertexData(&this->normals, normals, SOC_Vector3(), alloc);
			SetVertexData(&this->tangents, tangents, SOC_Vector3(), alloc);
			SetVertexData(&this->binormals, binormals, SOC_Vector3(), alloc);
			SetVertexData(&this->colors, colors, Color(), alloc);

			if(texcoords.first > 0)
			{
//				this->texcoords = texcoords;

				if(alloc)
				{
					if(this->texcoords.second)
					{
						for(int i=0; i<this->texcoords.first; ++i)
							Utility::SAFE_ARRARY_DELETE(this->texcoords.second[i]);
						Utility::SAFE_DELETE(this->texcoords.second);
					}

					int count = texcoords.first;
					this->texcoords.second = new SOC_Vector2*[count];

					for(int i=0; i<count; ++i)
					{
						SOC_Vector2 *ary = nullptr;				
						SetVertexData(&ary, texcoords.second[i], SOC_Vector2(), alloc);
						this->texcoords.second[i] = ary;
					}
				}
				else this->texcoords = texcoords;
			}

			CalcVertexBufferSize();

			if(alloc)
			{
				this->indices.second = new SOC_word[indices.first];
				this->indices.first = indices.first;
				memcpy(this->indices.second, indices.second, sizeof(SOC_word) * indices.first);
			}
			else
			{
				this->indices.second = indices.second;
				this->indices.first = indices.first;
			}

			this->numOfTriangle = numOfTriangle;

			Utility::SAFE_DELETE(vertexBuffer);
			Utility::SAFE_DELETE(indexBuffer);

			vertexBuffer = new Buffer::VertexBuffer( vertexBufferSize, numOfVertex, graphics );
			indexBuffer = new Buffer::IndexBuffer( indices.first, graphics);

			if( CreateVertexBuffer(isDynamic) == false )
				return false;

			if( CreateIndexBuffer() == false )
				return false;				

			if( CreateVertexDeclaration(&decl) == false )
				return false;

			return true; 
		}

		bool MeshFilter::CreateVertexBuffer(bool isDynamic)
		{
			SOC_dword usage = SOC_USAGE_WRITEONLY | (isDynamic ? SOC_USAGE_DYNAMIC : 0);

			if( vertexBuffer->Create( usage, SOC_POOL_DEFAULT) == false )
				return false;

			void *vertexBufferData = nullptr;
			if( vertexBuffer->Lock(&vertexBufferData) == false )
				return false;

			for(int i=0; i<numOfVertex; ++i)
			{
				*( (SOC_Vector3*)vertexBufferData ) = vertices[i];
				vertexBufferData = (SOC_Vector3*)vertexBufferData + 1;

				if(normals)
				{
					*( (SOC_Vector3*)vertexBufferData ) = normals[i];
					vertexBufferData = (SOC_Vector3*)vertexBufferData + 1;
				}

				if(tangents && binormals)
				{
					*( (SOC_Vector3*)vertexBufferData ) = tangents[i];
					vertexBufferData = (SOC_Vector3*)vertexBufferData + 1;

					*( (SOC_Vector3*)vertexBufferData ) = binormals[i];
					vertexBufferData = (SOC_Vector3*)vertexBufferData + 1;
				}

				if(colors)
				{
					SOC_Vector4 vec4 = SOC_Vector4(colors[i].r, colors[i].g, colors[i].b, colors[i].a);
					*( (SOC_Vector4*)vertexBufferData ) = vec4;
					vertexBufferData = (SOC_Vector4*)vertexBufferData + 1;
				}

				if(texcoords.second)
				{
					for(int layer = 0; layer < texcoords.first; ++layer)
					{
						*( (SOC_Vector2*)vertexBufferData ) = texcoords.second[layer][i];
						vertexBufferData = (SOC_Vector2*)vertexBufferData + 1;
					}
				}

				//for(std::vector<SOC_Vector2*>::iterator iter = texcoord.begin(); iter != texcoord.end(); ++iter)
				//{
				//	*( (SOC_Vector2*)vertexBufferData ) = (*iter)[i];
				//	vertexBufferData = (SOC_Vector2*)vertexBufferData + 1;
				//}
			}

			if( vertexBuffer->UnLock() == false)
				return false;

			return true;
		}

		bool MeshFilter::CreateIndexBuffer()
		{
			if( indexBuffer->Create(SOC_POOL_DEFAULT) == false)
				return false;

			SOC_word *indexBufferData = nullptr;
			if( indexBuffer->Lock((void**)&indexBufferData) == false)
				return false;

			memcpy(indexBufferData, this->indices.second, sizeof(SOC_word) * indexBuffer->GetCount());
			if( indexBuffer->UnLock() == false)
				return false;

			return true;
		}

		bool MeshFilter::CreateVertexDeclaration(VertexDeclaration *out)
		{
			VertexDeclarationElements ves;
			std::string description = "P";
			VertexDeclarationElement e = VertexDeclarationElement(0, 0, SOC_VERTEX_DECLTYPE_FLOAT3, SOC_VERTEX_USAGE_POSITION, 0);

			std::vector<VertexDeclarationElement> *v = &ves.vertexElement;

			//add position declaraction
			v->push_back(e);
			e.offset = sizeof(SOC_Vector3);

			if(normals)
			{
				e.usage = SOC_VERTEX_USAGE_NORMAL;
				v->push_back(e);

				e.offset += sizeof(SOC_Vector3);
				description += "N";
			}

			if(tangents)
			{
				e.usage = SOC_VERTEX_USAGE_TANGENT;
				v->push_back(e);

				e.offset += sizeof(SOC_Vector3);
				description += "T";
			}

			if(binormals)
			{
				e.usage = SOC_VERTEX_USAGE_BINORMAL;
				v->push_back(e);

				e.offset += sizeof(SOC_Vector3);
				description += "B";
			}

			if(colors)
			{
				e.usage = SOC_VERTEX_USAGE_COLOR;
				e.type = SOC_VERTEX_DECLTYPE_COLOR;

				v->push_back(e);

				e.offset += sizeof(SOC_Vector4);
				description += "C";
			}

			if(texcoords.first > 0)
			{
				e.usage = SOC_VERTEX_USAGE_TEXCOORD;
				e.type = SOC_VERTEX_DECLTYPE_FLOAT2;
			}

			int size = texcoords.first;
			for(int i=0; i<size; ++i)
			{
				e.usageIndex = i;
				v->push_back(e);

				e.offset += sizeof(SOC_Vector2);
				description += "T";

				description += ('0' + i);
			}

			ves.description = description.c_str();
			(*out) = graphics->CreateVertexDeclation(&ves);

			return true;
		}

		Buffer::VertexBuffer* MeshFilter::GetVertexBuffer()
		{
			return vertexBuffer;
		}

		Buffer::IndexBuffer* MeshFilter::GetIndexBuffer()
		{
			return indexBuffer;
		}

		int MeshFilter::GetNumOfVertex()
		{
			return numOfVertex;
		}

		int MeshFilter::GetNumOfTriangle()
		{
			return numOfTriangle;
		}

		SOC_TRIANGLE MeshFilter::GetTriangleType()
		{
			return triangleType;
		}

		VertexDeclaration MeshFilter::GetDeclaration()
		{
			return decl;
		}
	}

}