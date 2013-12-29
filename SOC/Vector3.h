#pragma once

#include "Math.h"

class Vector3
{
public:
	float x;
	float y;
	float z;

public:
	Vector3()
	{
		x = y = z = 0;
	}

	Vector3(float x, float y)
	{
		this->x = x;
		this->y = y;
		
		z = 0;
	}

	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	~Vector3(void)
	{
	}

public:
	Vector3 operator - (Vector3 &a)
	{
		return Vector3(x-a.x, y-a.y, z-a.z);
	}

	Vector3 operator + (Vector3 &a)
	{
		return Vector3( a.x + x,
			a.y + y,
			a.z + z);
	}

	bool operator == (Vector3 rhs)
	{
		const float kEpsilon = 1e-005f;
		bool x = abs(x - rhs.x) < kEpsilon;
		bool y = abs(y - rhs.y) < kEpsilon;
		bool z = abs(z - rhs.z) < kEpsilon;

		return x & y & z;
	}

	bool operator != (Vector3 &rhs)
	{
		return !Vector3::operator==(rhs);
	}

	Vector3 operator * (float d)
	{
		return Vector3(x * d, y * d, z * d);
	}

	Vector3 operator * (Vector3 &a)
	{
		return Vector3(a.x * x, a.y * y, a.z * z);
	}

	Vector3 operator / (float d)
	{
		return Vector3(x/d, y/d, z/d);
	}

public:
	static Vector3 Forward()
	{
		return Vector3(0, 0, 1);
	}

	static Vector3 Right()
	{
		return Vector3(1, 0, 0);
	}

	static Vector3 One()
	{
		return Vector3(1, 1, 1);
	}

	static Vector3 Up()
	{
		return Vector3(0, 1, 0);
	}

	static Vector3 Zero()
	{
		return Vector3(0, 0, 0);
	}

	static float AngleDir(Vector3 &from, Vector3 &to, bool radian = true)
	{
		float dot = Vector3::Dot(from, to);
		return radian ? dot : dot * Math::Rad2Deg();
	}

	static Vector3 Cross(Vector3 &lhs, Vector3 &rhs)
	{
		return Vector3( lhs.y * rhs.z - rhs.y * lhs.z, lhs.z * rhs.x - rhs.z * lhs.x, lhs.x * rhs.y - rhs.x * lhs.y );
	}

	static float Distance(Vector3 &a, Vector3 &b)
	{
		float sx = (b.x - a.x) * (b.x - a.x);
		float sy = (b.y - a.y) * (b.y - a.y);
		float sz = (b.z - a.z) * (b.z - a.z);

		return sqrtf(sx+sy+sz);
	}

	static float Dot(Vector3 &lhs, Vector3 &rhs)
	{
		return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
	}

	static Vector3 Lerp(Vector3 &from, Vector3 &to, float t)
	{
		Vector3 a = to - from;
		return a * t;
	}

	static Vector3 Min(Vector3 &lhs, Vector3 &rhs)
	{
		float x = lhs.x > rhs.x ? rhs.x : lhs.x;
		float y = lhs.y > rhs.y ? rhs.y : lhs.y;
		float z = lhs.z > rhs.z ? rhs.z : lhs.z;

		return Vector3(x, y, z);
	}

	static Vector3 Max(Vector3 &lhs, Vector3 &rhs)
	{
		float x = lhs.x > rhs.x ? lhs.x : rhs.x;
		float y = lhs.y > rhs.y ? lhs.y : rhs.y;
		float z = lhs.z > rhs.z ? lhs.z : rhs.z;

		return Vector3(x, y, z);
	}

	static float Legnth(Vector3 &a)
	{
		return sqrtf((a.x * a.x) + (a.y + a.y) + (a.z * a.z));
	}

	static Vector3 Normalize(Vector3 &value)
	{
		float v = Vector3::Legnth(value);
		return value / v;
	}

	static Vector3 Project(Vector3 &vector, Vector3 &onNormal)
	{
		float dot = Vector3::Dot(vector, onNormal);
		float t = dot / Vector3::SqrLegnth(onNormal);
		return vector * t;
	}

	static Vector3 Reflect(Vector3 &inDirection, Vector3 &inNormal)
	{
		float dot = Vector3::Dot(inDirection, inNormal);

		float x = -2.0f * dot * inNormal.x;
		float y = -2.0f * dot * inNormal.y;
		float z = -2.0f * dot * inNormal.z;

		return inDirection - Vector3(x, y, z);
	}

	static Vector3 Scale(Vector3 &a, Vector3 &b)
	{
		return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
	}

	static float SqrLegnth(Vector3 &a)
	{
		return (a.x * a.x) + (a.y + a.y) + (a.z * a.z);
	}

public:
	void Normalize()
	{
		float v = Vector3::Legnth(*this);
		*this = *this / v;
	}

	void Scale(Vector3 scale)
	{
		x *= scale.x;
		y *= scale.y;
		z *= scale.z;
	}

	void Set(float newX, float newY, float newZ)
	{
		x = newX;
		y = newY;
		z = newZ;
	}
};
