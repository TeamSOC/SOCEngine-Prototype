//
//  Rendering.h
//  Rendering
//
//  Created by Jiman Jeong on 13. 8. 16..
//  Copyright (c) 2013년 SOC. All rights reserved.
//

#pragma once

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#ifndef sqr
#define sqr(x) ((x)*(x))
#endif

#if defined(WIN32)

#include <d3d9.h>
#include <d3dx9.h>

typedef VOID				SOC_void;
typedef CHAR				SOC_char;
typedef unsigned int		SOC_enum;
typedef BOOL				SOC_bool;
typedef unsigned int		SOC_bitfield;
typedef BYTE				SOC_byte;
typedef SHORT				SOC_short;
typedef WORD				SOC_word;
typedef INT					SOC_int;
typedef DWORD				SOC_dword;
typedef SIZE_T				SOC_sizei;
typedef UBYTE				SOC_ubyte;
typedef USHORT				SOC_ushort;
typedef UWORD				SOC_uword;
typedef UINT				SOC_uint;
typedef UDWORD				SOC_udword;
typedef FLOAT				SOC_float;
typedef CLAMPF				SOC_clampf;
typedef FIXED				SOC_fixed;
typedef CLAMPX				SOC_clampx;

typedef INTPTR				SOC_intptr;
typedef SIZEPTR				SOC_sizeiptr;

typedef HALF				SOC_half;

typedef INT64				SOC_int64;
typedef QWORD				SOC_qword;
typedef UINT64				SOC_uint64;
typedef UQWORD				SOC_uqword;
typedef SYNC				SOC_sync;

typedef D3DXFLOAT16			SOC_float16;
typedef double				SOC_double;

typedef D3DVECTOR			SOC_Vector;

typedef D3DXVECTOR2			SOC_Vector2;
typedef D3DXVECTOR3			SOC_Vector3;
typedef D3DXVECTOR4			SOC_Vector4;

typedef D3DXQUATERNION		SOC_Quaternion;

typedef D3DMATRIX			SOC_MatrixBase;
typedef D3DXMATRIX			SOC_Matrix;
typedef D3DXMATRIXA16		SOC_MatrixA16;

typedef D3DXPLANE			SOC_Plane;

#define SOCVec3Length(Const_Vector3_Ptr) \
		D3DXVec3Length(Const_Vector3_Ptr)
#define SOCVec3Normalize(Out_Vector3_Ptr, In_Const_Vector3_Ptr) \
		D3DXVec3Normalize(Out_Vector3_Ptr, In_Const_Vector3_Ptr)

#define SOCQuaternionRotationMatrix(Out_Quaternion_Ptr, In_Const_Matrix_Ptr) \
		D3DXQuaternionRotationMatrix(Out_Quaternion_Ptr, In_Const_Matrix_Ptr)
#define SOCQuaternionRotationAxis(Out_Quaternion_Ptr, In_Const_Vector3_Ptr, In_Float) \
		D3DXQuaternionRotationAxis(Out_Quaternion_Ptr, In_Const_Vector3_Ptr, In_Float)

#define SOCVec3Dot(Const_Vector3_Ptr_U, Const_Vector3_Ptr_V) \
		D3DXVec3Dot(Const_Vector3_Ptr_U, Const_Vector3_Ptr_V)
#define SOCVec3Cross(Out_Const_Vector3_Ptr, In_Const_Vector3_Ptr_U, In_Const_Vector3_Ptr_V) \
		D3DXVec3Cross(Out_Const_Vector3_Ptr, In_Const_Vector3_Ptr_U, In_Const_Vector3_Ptr_V)

#define SOCQuaternionRotationAxis(Out_Quaternion_Ptr, In_Const_Vector3_Ptr, In_Float) \
		D3DXQuaternionRotationAxis(Out_Quaternion_Ptr, In_Const_Vector3_Ptr, In_Float)

#define SOCMatrixIdentity(Out_Matrix_Ptr) \
		D3DXMatrixIdentity(Out_Matrix_Ptr)
#define SOCMatrixDeterminant(In_Const_Matrix_Ptr) \
		D3DXMatrixDeterminant(In_Const_Matrix_Ptr)
#define SOCMatrixInverse(Out_Matrix_Ptr, Out_Float_Ptr, In_Const_Matrix_Ptr) \
		D3DXMatrixInverse(Out_Matrix_Ptr, Out_Float_Ptr, In_Const_Matrix_Ptr)
#define SOCMatrixTranspose(Out_Matrix_Ptr* pOut, In_Const_Matrix_Ptr) \
		D3DXMatrixTranspose(Out_Matrix_Ptr* pOut, In_Const_Matrix_Ptr)

#define SOCMatrixRotationAxis(Out_Matrix_Ptr, In_Const_Vector_Ptr, In_Float) \
		D3DXMatrixRotationAxis(Out_Matrix_Ptr, In_Const_Vector_Ptr, In_Float)
#define SOCMatrixRotationQuaternion(Out_Matrix_Ptr, In_Const_Quaternion_Ptr) \
		D3DXMatrixRotationQuaternion(Out_Matrix_Ptr, In_Const_Quaternion_Ptr)

#define SOCVec3TransformCoord(Out_Vector3_Ptr, In_Const_Vector_Ptr, In_Const_Matrix_Ptr) \
		D3DXVec3TransformCoord(Out_Vector3_Ptr, In_Const_Vector_Ptr, In_Const_Matrix_Ptr)
#define SOCVec3TransformCoordArray(Out_Vector3_Ptr, In_UInt_OutStride, In_Const_Vector3_Ptr, In_UInt_InStride, In_Const_Matrix_Ptr, In_UInt_N) \
		D3DXVec3TransformCoordArray(Out_Vector3_Ptr, In_UInt_OutStride, In_Const_Vector3_Ptr, In_UInt_InStride, In_Const_Matrix_Ptr, In_UInt_N)

#define SOCPlaneFromPoints(Out_Plane_Ptr, In_Const_Vector3_Ptr_1, In_Const_Vector3_Ptr_2, In_Const_Vector3_Ptr_3) \
		D3DXPlaneFromPoints(Out_Plane_Ptr, In_Const_Vector3_Ptr_1, In_Const_Vector3_Ptr_2, In_Const_Vector3_Ptr_3)
#define SOCPlaneDotCoord(Out_Plane_Ptr, In_Const_Vector3_Ptr) \
		D3DXPlaneDotCoord(Out_Plane_Ptr, In_Const_Vector3_Ptr)

#define SOCM_PI				D3DX_PI

#elif defined(__APPLE__)

#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

typedef GLvoid				SOC_void;
typedef GLchar				SOC_char;
typedef GLenum				SOC_enum;
typedef GLboolean			SOC_bool;
typedef GLbitfield			SOC_bitfield;
typedef GLbyte				SOC_byte;
typedef GLshort				SOC_short;
typedef GLshort				SOC_word;
typedef GLint				SOC_int;
typedef GLint				SOC_dword;
typedef GLsizei				SOC_sizei;
typedef GLubyte				SOC_ubyte;
typedef GLushort			SOC_ushort;
typedef GLushort			SOC_uword;
typedef GLuint				SOC_uint;
typedef GLuint				SOC_udword;
typedef GLfloat 			SOC_float;
typedef GLclampf			SOC_clampf;
typedef GLfixed				SOC_fixed;
typedef GLclampx			SOC_clampx;

typedef GLintptr			SOC_intptr;
typedef GLsizeiptr			SOC_sizeiptr;

typedef GLhalf				SOC_half;

typedef double				SOC_float16;
typedef double				SOC_double;

typedef GLint64				SOC_int64;
typedef GLint64				SOC_qword;
typedef GLuint64			SOC_uint64;
typedef GLuint64			SOC_uqword;
typedef GLsync				SOC_sync;

struct SOC_Vector2
{
public:
	SOC_Vector2() {}
	SOC_Vector2( const SOC_float * elements)
	{
		this->x = elements[0];
		this->y = elements[1];
	}
	SOC_Vector2( const SOC_float16 * elements)
	{
		this->x = (SOC_float)elements[0];
		this->y = (SOC_float)elements[1];
	}
	SOC_Vector2( SOC_float x, SOC_float y )
	{
		this->x = x;
		this->y = y;
	}
	
	// casting
	operator SOC_float* ()				{ return (SOC_float*)this; }
	operator const SOC_float* () const	{ return (const SOC_float*)this; }

	// assignment operators
	SOC_Vector2& operator += (const SOC_Vector2& roe)
	{
		x += roe.x;
		y += roe.y;
		
		return *this;
	}
	SOC_Vector2& operator -= (const SOC_Vector2& roe)
	{
		x -= roe.x;
		y -= roe.y;
		
		return *this;
	}
	SOC_Vector2& operator *= (SOC_float roe)
	{
		x *= roe;
		y *= roe;
		
		return *this;
	}
	SOC_Vector2& operator /= ( SOC_float roe)
	{
		x /= roe;
		y /= roe;
		
		return *this;
	}
	
	SOC_Vector2 operator + () const
	{
		return SOC_Vector2(x, y);
	}
	SOC_Vector2 operator - () const
	{
		return SOC_Vector2(-x, -y);
	}
	
	// binary operators
	SOC_Vector2 operator + (const SOC_Vector2& roe) const
	{
		return SOC_Vector2(x + roe.x, y + roe.y);
	}
	SOC_Vector2 operator - (const SOC_Vector2& roe) const
	{
		return SOC_Vector2(x - roe.x, y - roe.y);
	}
	SOC_Vector2 operator * (SOC_float roe) const
	{
		return SOC_Vector2(x * roe, y * roe);
	}
	SOC_Vector2 operator / (SOC_float roe) const
	{
		return SOC_Vector2(x / roe, y / roe);
	}

	
	friend SOC_Vector2 operator * (SOC_float, const SOC_Vector2&);
	
	SOC_bool operator == (const SOC_Vector2& roe) const
	{
		return (x == roe.x && y == roe.y);
	}
	SOC_bool operator != (const SOC_Vector2& roe) const
	{
		return (x != roe.x || y != roe.y);
	}
	
public:
	SOC_float x, y;
};

SOC_Vector2 operator * (SOC_float loe, const SOC_Vector2& roe)
{
	return SOC_Vector2(loe * roe.x, loe * roe.y);
}

struct SOC_Vector
{
	SOC_float x, y, z;
};

struct SOC_Vector3 : public SOC_Vector
{
public:
	SOC_Vector3() {}
	SOC_Vector3(const SOC_float* elements)
	{
		this->x = elements[0];
		this->y = elements[1];
		this->z = elements[2];
	}
	SOC_Vector3(const SOC_Vector& vector)
	{
		*this = vector;
	}
	SOC_Vector3(const SOC_float16* elements)
	{
		this->x = (SOC_float)elements[0];
		this->y = (SOC_float)elements[1];
		this->z = (SOC_float)elements[2];
	}
	SOC_Vector3(SOC_float x, SOC_float y, SOC_float z)
	{
		this->x = x; this->y = y; this->z = z;
	}
	
	// casting
	operator SOC_float* ()				{ return (SOC_float*)this; }
	operator const SOC_float* () const	{ return (const SOC_float*)this; }

	// assignment operators
	SOC_Vector3& operator += (const SOC_Vector3& roe)
	{
		x += roe.x;
		y += roe.y;
		z += roe.z;
		
		return *this;
	}
	SOC_Vector3& operator -= (const SOC_Vector3& roe)
	{
		x -= roe.x;
		y -= roe.y;
		z -= roe.z;
		
		return *this;
	}
	SOC_Vector3& operator *= (SOC_float roe)
	{
		x *= roe;
		y *= roe;
		z *= roe;
		
		return *this;
	}
	SOC_Vector3& operator /= (SOC_float roe)
	{
		x /= roe;
		y /= roe;
		z /= roe;
		
		return *this;
	}
	
	// unary operators
	SOC_Vector3 operator + () const
	{
		return SOC_Vector3(x, y, z);
	}
	SOC_Vector3 operator - () const
	{
		return SOC_Vector3(-x, -y, -z);
	}
	
	// binary operators
	SOC_Vector3 operator + (const SOC_Vector3& roe) const
	{
		return SOC_Vector3(x + roe.x, y + roe.y, z + roe.z);
	}
	SOC_Vector3 operator - (const SOC_Vector3& roe) const
	{
		return SOC_Vector3(x - roe.x, y - roe.y, z - roe.z);
	}
	SOC_Vector3 operator * (SOC_float roe) const
	{
		return SOC_Vector3(x * roe, y * roe, z * roe);
	}
	SOC_Vector3 operator / (SOC_float roe) const
	{
		return SOC_Vector3(x / roe, y / roe, z / roe);
	}
	
	friend SOC_Vector3 operator * (SOC_float, const struct SOC_Vector3&);
	
	SOC_bool operator == (const SOC_Vector3& roe) const
	{
		return (x == roe.x && y == roe.y && z == roe.z);
	}
	SOC_bool operator != (const SOC_Vector3& roe) const
	{
		return (x != roe.x || y != roe.y || z != roe.z);
	}
};

SOC_Vector3 operator * (SOC_float loe, const struct SOC_Vector3& roe)
{
	return SOC_Vector3(loe * roe.x, loe * roe.y, loe * roe.z);
}

struct SOC_Matrix;

struct SOC_Vector4
{
public:
	SOC_Vector4() {}
	SOC_Vector4(const SOC_float* elements)
	{
		this->x = elements[0];
		this->y = elements[1];
		this->z = elements[2];
		this->w = elements[3];
	}
	SOC_Vector4(const SOC_float16* elements)
	{
		this->x = (SOC_float)elements[0];
		this->y = (SOC_float)elements[1];
		this->z = (SOC_float)elements[2];
		this->w = (SOC_float)elements[3];
	}
	SOC_Vector4(const SOC_Vector& xyz, SOC_float w)
	{
		this->x = xyz.x;
		this->y = xyz.y;
		this->z = xyz.z;
		this->w = w;
	}
	SOC_Vector4(SOC_float x, SOC_float y, SOC_float z, SOC_float w )
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
	
	// casting
	operator SOC_float* ()				{ return (SOC_float*)this; }
	operator const SOC_float* () const	{ return (const SOC_float*)this; }
	
	// unary operators
	SOC_Vector4 operator + () const
	{
		return SOC_Vector4(x, y, z, w);
	}
	SOC_Vector4 operator - () const
	{
		return SOC_Vector4(-x, -y, -z, -w);
	}
	
	// assignment operators
	SOC_Vector4& operator += (const SOC_Vector4& roe)
	{
		x += roe.x;
		y += roe.y;
		z += roe.z;
		w += roe.w;
		
		return *this;
	}
	SOC_Vector4& operator -= (const SOC_Vector4& roe)
	{
		x -= roe.x;
		y -= roe.y;
		z -= roe.z;
		w -= roe.w;
		
		return *this;
	}
	SOC_Vector4& operator *= (SOC_float roe)
	{
		x *= roe;
		y *= roe;
		z *= roe;
		w *= roe;
		
		return *this;
	}
	SOC_Vector4& operator /= (SOC_float roe)
	{
		x /= roe;
		y /= roe;
		z /= roe;
		w /= roe;
		
		return *this;
	}
	
	// binary operators
	SOC_Vector4 operator + (const SOC_Vector4& roe) const
	{
		return SOC_Vector4(x + roe.x, y + roe.y, z + roe.z, w + roe.w);
	}
	SOC_Vector4 operator - (const SOC_Vector4& roe) const
	{
		return SOC_Vector4(x - roe.x, y - roe.y, z - roe.z, w - roe.w);
	}
	SOC_Vector4 operator * (SOC_float roe) const
	{
		return SOC_Vector4(x * roe, y * roe, z * roe, w * roe);
	}
	SOC_Vector4 operator / (SOC_float roe) const
	{
		return SOC_Vector4(x / roe, y / roe, z / roe, w / roe);
	}
	SOC_Vector4 operator * (const SOC_Matrix& matrix) const;
	
	friend SOC_Vector4 operator * ( SOC_float, const struct SOC_Vector4& );
	
	SOC_bool operator == (const SOC_Vector4& roe) const
	{
		return (x == roe.x && y == roe.y && z == roe.z && w == roe.w);
	}
	SOC_bool operator != (const SOC_Vector4& roe) const
	{
		return (x != roe.x || y != roe.y || z != roe.z || w != roe.w);
	}
	
public:
	SOC_float x, y, z, w;
};

SOC_Vector4 operator * (SOC_float loe, const SOC_Vector4& roe)
{
	return SOC_Vector4(loe * roe.x, loe * roe.y, loe * roe.z, loe * roe.w);
}
	
SOC_float SOCVec3Dot(const SOC_Vector* pU, const SOC_Vector* pV)
{
	return pU->x * pV->x + pU->y * pV->y + pU->z * pV->z;
}

SOC_float SOCVec3Length(const SOC_Vector* pV)
{
	return sqrtf(pV->x * pV->x + pV->y * pV->y + pV->z * pV->z);
}

SOC_Vector* SOCVec3Normalize(SOC_Vector* pOut, const SOC_Vector *pV)
{
	return &(*pOut = 1 / SOCVec3Length(pV) * (*pV));
}

//http://en.wikipedia.org/wiki/Cross_product
SOC_Vector* SOCVec3Cross(SOC_Vector* pOut, const SOC_Vector* pV1, const SOC_Vector* pV2)
{
	pOut->x = pV1->y*pV2->z - pV1->z*pV2->y;
	pOut->y = pV1->z*pV2->x - pV1->x*pV2->z;
	pOut->z = pV1->x*pV2->y - pV1->y*pV2->x;
	
	return pOut;
}
	
//http://content.gpwiki.org/index.php/OpenGL:Tutorials:Using_Quaternions_to_represent_rotation
struct SOC_Quaternion
{
public:
	SOC_Quaternion() {}
	SOC_Quaternion(const SOC_float* elements)
	{
		this->x = elements[0];
		this->y = elements[1];
		this->z = elements[2];
		this->w = elements[3];
	}
	SOC_Quaternion(const SOC_float16* elements)
	{
		this->x = (SOC_float)elements[0];
		this->y = (SOC_float)elements[1];
		this->z = (SOC_float)elements[2];
		this->w = (SOC_float)elements[3];
	}
	SOC_Quaternion(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
	
	// casting
	operator SOC_float* ()				{ return (SOC_float*)this; }
	operator const SOC_float* () const	{ return (const SOC_float*)this; }
	
	// assignment operators
	SOC_Quaternion& operator += (const SOC_Quaternion& roe)
	{
		x += roe.x;
		y += roe.y;
		z += roe.z;
		w += roe.w;
		
		return *this;
	}
	SOC_Quaternion& operator -= (const SOC_Quaternion& roe)
	{
		x -= roe.x;
		y -= roe.y;
		z -= roe.z;
		w -= roe.w;
		
		return *this;
	}
	SOC_Quaternion& operator *= (const SOC_Quaternion& roe)
	{
		SOC_float _x = w*roe.x + x*roe.w + y*roe.z - z*roe.y;
		SOC_float _y = w*roe.y - x*roe.z + y*roe.w + z*roe.x;
		SOC_float _z = w*roe.z + x*roe.y - y*roe.x + z*roe.w;
		SOC_float _w = w*roe.w - x*roe.x - y*roe.y - z*roe.z;
		
		x = _x;
		y = _y;
		z = _z;
		w = _w;
		
		return *this;
	}
	SOC_Quaternion& operator *= (float roe)
	{
		x *= roe;
		y *= roe;
		z *= roe;
		w *= roe;
		
		return *this;
	}
	SOC_Quaternion& operator /= (float roe)
	{
		x /= roe;
		y /= roe;
		z /= roe;
		w /= roe;
		
		return *this;
	}
	
	// unary operators
	SOC_Quaternion operator + () const
	{
		return SOC_Quaternion(x, y, z, w);
	}
	SOC_Quaternion operator - () const
	{
		return SOC_Quaternion(-x, -y, -z, -w);
	}
	
	// binary operators
	SOC_Quaternion operator + (const SOC_Quaternion& roe) const
	{
		return SOC_Quaternion(x + roe.x, y + roe.y, z + roe.z, w + roe.w);
	}
	SOC_Quaternion operator - (const SOC_Quaternion& roe) const
	{
		return SOC_Quaternion(x - roe.x, y - roe.y, z - roe.z, w - roe.w);
	}
	SOC_Quaternion operator * (const SOC_Quaternion& roe) const
	{
		SOC_float _x = w*roe.x + x*roe.w + y*roe.z - z*roe.y;
		SOC_float _y = w*roe.y - x*roe.z + y*roe.w + z*roe.x;
		SOC_float _z = w*roe.z + x*roe.y - y*roe.x + z*roe.w;
		SOC_float _w = w*roe.w - x*roe.x - y*roe.y - z*roe.z;
		
		return SOC_Quaternion(_x, _y, _z, _w);
	}
	SOC_Quaternion operator * (float roe) const
	{
		return SOC_Quaternion(x * roe, y * roe, z * roe, w * roe);
	}
	SOC_Quaternion operator / (float roe) const
	{
		return SOC_Quaternion(x / roe, y / roe, z / roe, w / roe);
	}
	
	friend SOC_Quaternion operator * (float, const SOC_Quaternion&);
	
	SOC_bool operator == (const SOC_Quaternion& roe) const
	{
		return (x == roe.x && y == roe.y && z == roe.z && w == roe.w);
	}
	SOC_bool operator != (const SOC_Quaternion& roe) const
	{
		return (x != roe.x || y != roe.y || z != roe.z || w != roe.w);
	}
	
	float x, y, z, w;
};
	
SOC_Quaternion operator * (float loe, const SOC_Quaternion& roe)
{
	return SOC_Quaternion(loe * roe.x, loe * roe.y, loe * roe.z, loe * roe.w);
}

SOC_Quaternion* SOCQuaternionRotationAxis(SOC_Quaternion* pOut, const SOC_Vector* axis, SOC_float angle)
{
	SOC_float sinAngle;
	angle *= .5f;
	
	SOC_Vector3 vn;
	SOCVec3Normalize(&vn, axis);
	
	sinAngle = sinf(angle);
	
	pOut->x = (vn.x * sinAngle);
	pOut->y = (vn.y * sinAngle);
	pOut->z = (vn.z * sinAngle);
	pOut->w = cosf(angle);
	
	return pOut;
}
	
struct SOC_MatrixBase
{
	union {
		struct {
			SOC_float _11, _12, _13, _14;
			SOC_float _21, _22, _23, _24;
			SOC_float _31, _32, _33, _34;
			SOC_float _41, _42, _43, _44;
		};
		
		SOC_float m[4][4];
	};
};

//http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/
//	qw= √(1 + m00 + m11 + m22) /2
//	qx = (m21 - m12)/( 4 *qw)
//	qy = (m02 - m20)/( 4 *qw)
//	qz = (m10 - m01)/( 4 *qw)
SOC_Quaternion* SOCQuaternionRotationMatrix(SOC_Quaternion* pOut, const SOC_MatrixBase* mat)
{
	SOC_float w4;
	pOut->w = sqrtf(1.f + mat->m[0][0] + mat->m[1][1] + mat->m[2][2]) / 2;
	w4 = pOut->w * 4.f;
	
	pOut->x = (mat->m[2][1] - mat->m[1][2]) / w4;
	pOut->y = (mat->m[0][2] - mat->m[2][0]) / w4;
	pOut->z = (mat->m[1][0] - mat->m[0][1]) / w4;
	
	return pOut;
}
	
struct SOC_Matrix : public SOC_MatrixBase
{
public:
	SOC_Matrix() {}
	SOC_Matrix(const SOC_float* elements)
	{
		memcpy(m, elements, sizeof(SOC_float) * 16);
	}
	SOC_Matrix(const SOC_MatrixBase& mat)
	{
		*this = mat;
	}
	SOC_Matrix(const SOC_float16* elements)
	{
		for(int i = 0; i < 4; ++i)
			for(int j = 0; j < 4; ++j)
				m[i][j] = (SOC_float)elements[i*4+j];
	}
	SOC_Matrix(SOC_float _11, SOC_float _12, SOC_float _13, SOC_float _14,
			   SOC_float _21, SOC_float _22, SOC_float _23, SOC_float _24,
			   SOC_float _31, SOC_float _32, SOC_float _33, SOC_float _34,
			   SOC_float _41, SOC_float _42, SOC_float _43, SOC_float _44 )
	{
		this->_11 = _11;
		this->_12 = _12;
		this->_13 = _13;
		this->_14 = _14;
		
		this->_21 = _21;
		this->_22 = _22;
		this->_23 = _23;
		this->_24 = _24;
		
		this->_31 = _31;
		this->_32 = _32;
		this->_33 = _33;
		this->_34 = _34;
		
		this->_41 = _41;
		this->_42 = _42;
		this->_43 = _43;
		this->_44 = _44;
	}
	
	
	// access grants
	SOC_float& operator () (SOC_uint Row, SOC_uint Col)
	{
		return m[Row][Col];
	}
	SOC_float operator () (SOC_uint Row, SOC_uint Col) const
	{
		return m[Row][Col];
	}
	
	// casting operators
	operator SOC_float* ()				{ return (SOC_float*)this; }
	operator const SOC_float* () const	{ return (const SOC_float*)this; }
	
	// assignment operators
	SOC_Matrix& operator *= (const SOC_Matrix& roe)
	{
		return *this = *this * roe;
	}
	SOC_Matrix& operator += (const SOC_Matrix& roe)
	{
		SOC_float* linearLoe = *this;
		const SOC_float* linearRoe = roe;
		for(int i = 0; i < 16; ++i)
			linearLoe[i] += linearRoe[i];
		
		return *this;
	}
	SOC_Matrix& operator -= (const SOC_Matrix& roe)
	{
		SOC_float* linearLoe = *this;
		const SOC_float* linearRoe = roe;
		for(int i = 0; i < 16; ++i)
			linearLoe[i] -= linearRoe[i];
		
		return *this;
	}
	SOC_Matrix& operator *= (SOC_float roe)
	{
		SOC_float* linearLoe = *this;
		for(int i = 0; i < 16; ++i)
			linearLoe[i] *= roe;
		
		return *this;
	}
	SOC_Matrix& operator /= (SOC_float roe)
	{
		SOC_float* linearLoe = *this;
		for(int i = 0; i < 16; ++i)
			linearLoe[i] /= roe;
		
		return *this;
	}
	
	// unary operators
	SOC_Matrix operator + () const
	{
		return SOC_Matrix(*this);
	}
	SOC_Matrix operator - () const
	{
		static SOC_float _default[16] = {0, };
		static SOC_Matrix _mat(_default);
		return _mat - *this;
	}
	
	// binary operators
	SOC_Matrix operator * (const SOC_Matrix& roe) const
	{
		SOC_Matrix mat(0, 0, 0, 0,
					   0, 0, 0, 0,
					   0, 0, 0, 0,
					   0, 0, 0, 0);
		for(int i = 0; i < 4; ++i)
			for(int j = 0; j < 4; ++j)
				for(int k = 0; k < 4; ++k)
					mat.m[i][j] += this->m[i][k] * roe.m[k][j];
					
		return mat;
	}
	SOC_Matrix operator + (const SOC_Matrix& roe) const
	{
		SOC_Matrix mat(*this);
		SOC_float* linearLoe = mat;
		const SOC_float* linearRoe = roe;
		for(int i = 0; i < 16; ++i)
			linearLoe[i] += linearRoe[i];
			
		return mat;
	}
	SOC_Matrix operator - (const SOC_Matrix& roe) const
	{
		SOC_Matrix mat(*this);
		SOC_float* linearLoe = mat;
		const SOC_float* linearRoe = roe;
		for(int i = 0; i < 16; ++i)
			linearLoe[i] -= linearRoe[i];
			
		return mat;
	}
	SOC_Matrix operator * (SOC_float roe) const
	{
		SOC_Matrix mat(*this);
		SOC_float* linear = mat;
		for(int i = 0; i < 16; ++i)
			linear[i] *= roe;
			
		return mat;
	}
	SOC_Matrix operator / (SOC_float roe) const
	{
		SOC_Matrix mat(*this);
		SOC_float* linear = mat;
		for(int i = 0; i < 16; ++i)
			linear[i] /= roe;
			
		return mat;
	}
	
	friend SOC_Matrix operator * (SOC_float, const SOC_Matrix&);
	
	SOC_bool operator == (const SOC_Matrix& roe) const
	{
		for(int i = 0; i < 4; ++i)
		{
			for(int j = 0; j < 4; ++j)
			{
				if(this->m[i][j] == roe.m[i][j]) continue;
				return false;
			}
		}
		
		return true;
	}
	SOC_bool operator != (const SOC_Matrix& roe) const
	{
		for(int i = 0; i < 4; ++i)
		{
			for(int j = 0; j < 4; ++j)
			{
				if(this->m[i][j] != roe.m[i][j]) continue;
				return false;
			}
		}
		
		return true;
	}
};
	
SOC_Matrix operator * (SOC_float loe, const SOC_Matrix& roe)
{
	SOC_Matrix mat(roe);
	SOC_float* linearRoe = mat;
	for(int i = 0; i < 16; ++i)
		linearRoe[i] *= loe;
		
	return mat;
}
	
SOC_Vector4 SOC_Vector4::operator * (const SOC_Matrix& mat) const
{
	SOC_Vector4 vec(0, 0, 0, 0);
	const SOC_float* loe = *this;
	SOC_float* linear = vec;
	
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			linear[i] += loe[j] * mat.m[i][j];
	
	return vec;
}
	
SOC_Matrix* SOCMatrixIdentity(SOC_Matrix* pOut)
{
	SOC_float* linear = *pOut;
	memset(linear, 0, sizeof(SOC_float) * 16);
	
	pOut->_11 = 1;
	pOut->_22 = 1;
	pOut->_33 = 1;
	pOut->_44 = 1;
	
	return pOut;
}
	
SOC_float SOCMatrixDeterminant(const SOC_Matrix* pM)
{
	SOC_float* p[4];
	SOC_Vector4 _1(pM->m[0]); p[0] = _1;
	SOC_Vector4 _2(pM->m[1]); p[1] = _2;
	SOC_Vector4 _3(pM->m[2]); p[2] = _3;
	SOC_Vector4 _4(pM->m[3]); p[3] = _4;
	
	SOC_float rate, det = 1;
	for(int i = 0; i < 4; ++i)
	{
		for(int j = i + 1; j < 4; ++j)
		{
			rate = p[j][i] / p[i][i];
			
			for(int k = i; k < 4; ++k)
				p[j][k] = p[i][k] * rate - p[j][k];
		}
		det *= p[i][i];
	}
	
	return det;
}
	
inline SOC_float SOCMatrixMinor(const SOC_Matrix* pOut, SOC_uint row, SOC_uint col)
{
	SOC_float minor = 0, sum;
	for(int i = 0; i < 4; ++i)
	{
		if(i != row)
		{
			sum = 1;
			for(int j = 0; j < 4; ++j)
			{
				if(j != col)
				{
					sum *= pOut->m[i+j][j];
				}
			}
			minor += sum;
		}
	}
	for(int i = 0; i < 4; ++i)
	{
		if(i != row)
		{
			sum = 1;
			for(int j = 3; j >= 0; --j)
			{
				if(j != col)
				{
					sum *= pOut->m[i+j][j];
				}
			}
			minor -= sum;
		}
	}
	
	return minor;
}
	
SOC_Matrix* SOCMatrixInverse(SOC_Matrix* pOut, SOC_float* det, const SOC_Matrix* pM)
{
	SOC_float _det = SOCMatrixDeterminant(pM);
	
	if(det) *det = _det;
	
	if(_det != 0)
	{
		SOC_float sign = 1;
		for(int i = 0; i < 4; ++i)
		{
			sign *= -1;
			for(int j = 0; j < 4; ++j)
			{
				sign *= -1;
				pOut->m[i][j] = sign * SOCMatrixMinor(pM, i, j);
			}
		}
		*pOut /= _det;
	}
	else pOut = NULL;
	
	return pOut;
}
	
SOC_Matrix* SOCMatrixTranspose(SOC_Matrix* pOut, const SOC_Matrix* mat)
{
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			pOut->m[i][j] = mat[j][i];
	
	return pOut;
}
	
SOC_Matrix* SOCMatrixRotationAxis(SOC_Matrix* pOut, const SOC_Vector* axis, SOC_float angle)
{
	SOC_float s = sinf(angle);
	SOC_float c = cosf(angle);
	SOC_float d = 1-c;
	
	pOut->_11 = d*sqr(axis->x) + c;
	pOut->_12 = d*axis->x*axis->y + axis->z*s;
	pOut->_13 = d*axis->x*axis->z - axis->y*s;
	pOut->_14 = 0;
	
	pOut->_21 = d*axis->x*axis->y - axis->z*s;
	pOut->_22 = d*sqr(axis->y) + c;
	pOut->_23 = d*axis->y*axis->z + axis->x*s;
	pOut->_24 = 0;
	
	pOut->_31 = d*axis->x*axis->z + axis->y*s;
	pOut->_32 = d*axis->y*axis->z - axis->x*s;
	pOut->_33 = d*sqr(axis->z) + c;
	pOut->_34 = 0;
	
	pOut->_41 = 0;
	pOut->_42 = 0;
	pOut->_43 = 0;
	pOut->_44 = 1;
	
	return pOut;
}
	
SOC_Matrix* SOCMatrixRotationQuaternion(SOC_Matrix* pOut, const SOC_Quaternion* q)
{
	pOut->_11 = 1 - 2*sqr(q->y) - 2*sqr(q->z);
	pOut->_12 = 2*q->x*q->y + 2*q->z*q->w;
	pOut->_13 = 2*q->x*q->z - 2*q->y*q->w;
	pOut->_14 = 0;
	
	pOut->_21 = 2*q->x*q->y - 2*q->z*q->w;
	pOut->_22 = 1 - 2*sqr(q->x) - 2*sqr(q->z);
	pOut->_23 = 2*q->y*q->z + 2*q->x*q->w;
	pOut->_24 = 0;
	
	pOut->_31 = 2*q->x*q->z + 2*q->y*q->w;
	pOut->_32 = 2*q->y*q->z - 2*q->x*q->w;
	pOut->_33 = 1 - 2*sqr(q->x) - 2*sqr(q->y);
	pOut->_34 = 0;
	
	pOut->_41 = 0;
	pOut->_42 = 0;
	pOut->_43 = 0;
	pOut->_44 = 1;
	
	return pOut;
}
	
SOC_Vector3* SOCVec3TransformCoord(SOC_Vector3* pOut, const SOC_Vector* V, const SOC_Matrix* mat)
{
	SOC_Vector4 a = SOC_Vector4(V->x, V->y, V->z, 1) * *mat;
	pOut->x = a.x;
	pOut->y = a.y;
	pOut->z = a.z;
	*pOut /= a.w;
	
	return pOut;
}

SOC_Vector3* SOCVec3TransformCoordArray(SOC_Vector3* pOut, SOC_uint OutStride, const SOC_Vector3 *pV, SOC_uint VStride, const SOC_Matrix *pM, SOC_uint n)
{
	SOC_Vector4 res;
	SOC_float* linearOut = *pOut;
	const SOC_float* linearIn = *pV;
	for(int i = 0; i < n; ++i)
	{
		res = SOC_Vector4(linearIn[0], linearIn[1], linearIn[2], 1) * *pM;
		linearOut[0] = res.x / res.w;
		linearOut[1] = res.y / res.w;
		linearOut[2] = res.z / res.w;
		
		linearOut += OutStride;
		linearIn += VStride;
	}
	
	return pOut;
}
	
struct SOC_MatrixA16 : public SOC_Matrix {} __attribute__((aligned(16)));
	
struct SOC_Plane
{
public:
	SOC_Plane() {}
	SOC_Plane(const SOC_float* elements)
	{
		this->a = elements[0];
		this->b = elements[1];
		this->c = elements[2];
		this->d = elements[3];
	}
	SOC_Plane(const SOC_float16* elements)
	{
		this->a = (SOC_float)elements[0];
		this->b = (SOC_float)elements[1];
		this->c = (SOC_float)elements[2];
		this->d = (SOC_float)elements[3];
	}
	SOC_Plane(SOC_float a, SOC_float b, SOC_float c, SOC_float d)
	{
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
	}
	
	// casting
	operator SOC_float* ()				{ return (SOC_float*)this; }
	operator const SOC_float* () const	{ return (const SOC_float*)this; }
	
	// assignment operators
	SOC_Plane& operator *= (SOC_float roe)
	{
		this->a *= roe;
		this->b *= roe;
		this->c *= roe;
		this->d *= roe;
		
		return *this;
	}
	SOC_Plane& operator /= (SOC_float roe)
	{
		this->a /= roe;
		this->b /= roe;
		this->c /= roe;
		this->d /= roe;
		
		return *this;
	}
	
	// unary operators
	SOC_Plane operator + () const
	{
		return *this;
	}
	SOC_Plane operator - () const
	{
		return SOC_Plane(-a, -b, -c, -d);
	}
	
	// binary operators
	SOC_Plane operator * (SOC_float roe) const
	{
		return SOC_Plane(a * roe, b * roe, c * roe, d * roe);
	}
	SOC_Plane operator / (SOC_float roe) const
	{
		return SOC_Plane(a / roe, b / roe, c / roe, d / roe);
	}
	
	friend SOC_Plane operator * (SOC_float, const SOC_Plane&);
	
	SOC_bool operator == (const SOC_Plane& roe) const
	{
		return (a == roe.a && b == roe.b && c == roe.c && d == roe.d);
	}
	SOC_bool operator != (const SOC_Plane& roe) const
	{
		return (a != roe.a || b != roe.b || c != roe.c || d != roe.d);
	}
	
	SOC_float a, b, c, d;
};
	
SOC_Plane operator * (SOC_float loe, const SOC_Plane& roe)
{
	return SOC_Plane(loe * roe.a, loe * roe.b, loe * roe.c, loe * roe.d);
}
	
SOC_Plane* SOCPlaneFromPoints(SOC_Plane* pOut, const SOC_Vector3* pV1, const SOC_Vector3* pV2, const SOC_Vector3* pV3)
{
	SOC_Vector3 v, l(*pV2 - *pV1), r(*pV3 - *pV1);
	SOC_Vector3 n;

	SOCVec3Cross(&v, &l, &r);
	SOCVec3Normalize(&n, &v);
	
	pOut->a = n.x;
	pOut->b = n.y;
	pOut->c = n.z;
	pOut->d = -SOCVec3Dot(&n, pV1);
	
	return pOut;
}
	
SOC_float SOCPlaneDotCoord(const SOC_Plane* pP, const SOC_Vector3* pV)
{
	return pP->a * pV->x + pP->b * pV->y + pP->c * pV->z + pP->d;
}
	
#define SOCM_PI M_PI
	
#endif
