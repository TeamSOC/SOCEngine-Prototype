#pragma once

#include "Math.h"

class Vector2
{
public:
	float x;
	float y;

public:
	Vector2(void)
	{
		x = y = 0;
	}

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	~Vector2(void)
	{
	}

public:
	Vector2 operator - (Vector2 &a)
	{
		return Vector2(x - a.x, y - a.y);
	}

	Vector2 operator + (Vector2 &a)
	{
		return Vector2( a.x + x, a.y + y );
	}

	bool operator == (Vector2 rhs)
	{
		const float kEpsilon = 1e-005f;
		bool x = abs(x - rhs.x) < kEpsilon;
		bool y = abs(y - rhs.y) < kEpsilon;

		return x & y;
	}

	bool operator != (Vector2 &rhs)
	{
		return !Vector2::operator==(rhs);
	}

	Vector2 operator * (float d)
	{
		return Vector2(x * d, y * d);
	}

	Vector2 operator * (Vector2 &a)
	{
		return Vector2(a.x * x, a.y * y);
	}

	Vector2 operator / (float d)
	{
		return Vector2(x/d, y/d);
	}

public:
	static Vector2 Zero()
	{
		return Vector2(0, 0);
	}

	static Vector2 One()
	{
		return Vector2(1, 1);
	}

	static float Angle(Vector2 &from, Vector2 &to, bool radian = true)
	{
		float x = to.x - from.x;
		float y = to.y - from.y;

		return radian ? atan2f(y, x) : atan2f(y, x) * Math::Rad2Deg();
	}

	static float Distance(Vector2 &a, Vector2 &b)
	{
		float sx = (b.x - a.x) * (b.x - a.x);
		float sy = (b.y - a.y) * (b.y - a.y);

		return sqrtf(sx+sy);
	}

	static float Dot(Vector2 &lhs, Vector2 &rhs)
	{
		return (lhs.x * rhs.x) + (lhs.y * rhs.y);
	}

	static Vector2 Lerp(Vector2 &from, Vector2 &to, float t)
	{
		Vector2 a = to - from;
		return a * t;
	}

	static Vector2 Min(Vector2 &lhs, Vector2 &rhs)
	{
		float x = lhs.x > rhs.x ? rhs.x : lhs.x;
		float y = lhs.y > rhs.y ? rhs.y : lhs.y;

		return Vector2(x, y);
	}

	static Vector2 Max(Vector2 &lhs, Vector2 &rhs)
	{
		float x = lhs.x > rhs.x ? lhs.x : rhs.x;
		float y = lhs.y > rhs.y ? lhs.y : rhs.y;

		return Vector2(x, y);
	}

	static float Legnth(Vector2 &a)
	{
		return sqrtf((a.x * a.x) + (a.y + a.y));
	}

	static Vector2 Normalize(Vector2 &value)
	{
		float v = Vector2::Legnth(value);
		return value / v;
	}

	static Vector2 Scale(Vector2 &a, Vector2 &b)
	{
		return Vector2(a.x * b.x, a.y * b.y);
	}

	static float SqrLegnth(Vector2 &a)
	{
		return (a.x * a.x) + (a.y + a.y);
	}

public:
	void Normalize()
	{
		float v = Vector2::Legnth(*this);
		*this = *this / v;
	}

	void Scale(Vector2 &scale)
	{
		x *= scale.x;
		y *= scale.y;
	}

	void Set(float newX, float newY)
	{
		x = newX;
		y = newY;
	}
};

