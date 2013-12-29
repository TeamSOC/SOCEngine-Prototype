#pragma once

#include "Math.h"

class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;

public:
	Vector4(void)
	{
		x = y = z = w = 0;
	}

	Vector4(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = 0;
	}

	Vector4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	~Vector4(void)
	{

	}

public:
	Vector4 operator - (Vector4 &a)
	{
		return Vector4(x-a.x, y-a.y, z-a.z, w-a.w);
	}

	Vector4 operator + (Vector4 &a)
	{
		return Vector4( a.x + x,
			a.y + y,
			a.z + z,
			a.w + w);
	}

	bool operator == (Vector4 rhs)
	{
		const float kEpsilon = 1e-005f;
		bool x = abs(x - rhs.x) < kEpsilon;
		bool y = abs(y - rhs.y) < kEpsilon;
		bool z = abs(z - rhs.z) < kEpsilon;
		bool w = abs(w - rhs.w) < kEpsilon;

		return x & y & z & w;
	}

	bool operator != (Vector4 &rhs)
	{
		return !Vector4::operator==(rhs);
	}

	Vector4 operator * (float d)
	{
		return Vector4(x * d, y * d, z * d, w * d);
	}

	Vector4 operator * (Vector4 &a)
	{
		return Vector4(a.x * x, a.y * y, a.z * z, a.w * w);
	}

	Vector4 operator / (float d)
	{
		return Vector4(x/d, y/d, z/d, w/d);
	}

public:
	static Vector4 One()
	{
		return Vector4(1, 1, 1, 1);
	}

	static Vector4 Zero()
	{
		return Vector4(0, 0, 0, 0);
	}

public:
	static float Distance(Vector4 &a, Vector4 &b)
	{
		float sx = (b.x - a.x) * (b.x - a.x);
		float sy = (b.y - a.y) * (b.y - a.y);
		float sz = (b.z - a.z) * (b.z - a.z);
		float sw = (b.w - a.w) * (b.w - a.w);

		return sqrtf(sx+sy+sz+sw);
	}

	static float Dot(Vector4 &lhs, Vector4 &rhs)
	{
		return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z) + (lhs.w * rhs.w);
	}

	static Vector4 Lerp(Vector4 &from, Vector4 &to, float t)
	{
		Vector4 a = to - from;
		return a * t;
	}

	static Vector4 Min(Vector4 &lhs, Vector4 &rhs)
	{
		float x = lhs.x > rhs.x ? rhs.x : lhs.x;
		float y = lhs.y > rhs.y ? rhs.y : lhs.y;
		float z = lhs.z > rhs.z ? rhs.z : lhs.z;
		float w = lhs.w > rhs.w ? rhs.w : lhs.w;

		return Vector4(x, y, z, w);
	}

	static Vector4 Max(Vector4 &lhs, Vector4 &rhs)
	{
		float x = lhs.x > rhs.x ? lhs.x : rhs.x;
		float y = lhs.y > rhs.y ? lhs.y : rhs.y;
		float z = lhs.z > rhs.z ? lhs.z : rhs.z;
		float w = lhs.w > rhs.w ? lhs.w : rhs.w;

		return Vector4(x, y, z, w);
	}

	static float Legnth(Vector4 &a)
	{
		return sqrtf((a.x * a.x) + (a.y + a.y) + (a.z * a.z) + (a.w * a.w));
	}

	static Vector4 Normalize(Vector4 &value)
	{
		float v = Vector4::Legnth(value);
		return value / v;
	}

	static Vector4 Scale(Vector4 &a, Vector4 &b)
	{
		return Vector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
	}

	static float SqrLegnth(Vector4 &a)
	{
		return (a.x * a.x) + (a.y + a.y) + (a.z * a.z) + (a.w * a.w);
	}

public:
	void Normalize()
	{
		float v = Vector4::Legnth(*this);
		*this = *this / v;
	}

	void Scale(Vector4 &scale)
	{
		x *= scale.x;
		y *= scale.y;
		z *= scale.z;
		w *= scale.w;
	}

	void Set(float newX, float newY, float newZ, float newW)
	{
		x = newX;
		y = newY;
		z = newZ;
		w = newW;
	}
};

