#pragma once

#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <crtdbg.h>
#include <tchar.h>
#include <functional>
#include <string>
#include <math.h>
#include <time.h>

using namespace std;

#define	PI		3.141592f

static float RadianToAngle(float fRadian)
{
	return fRadian * 180.f / PI;
}

static float AngleToRadian(float fAngle)
{
	return fAngle * PI / 180.f;
}

typedef struct _tagVector2
{
	float		x, y;

	_tagVector2() :
		x(0.f),
		y(0.f)
	{
	}

	_tagVector2(float _x, float _y) :
		x(_x),
		y(_y)
	{
	}

	_tagVector2(const _tagVector2& pos)
	{
		x = pos.x;
		y = pos.y;
	}

	_tagVector2(const POINT& pt)
	{
		x = (float)pt.x;
		y = (float)pt.y;
	}


	// =
	void operator = (const _tagVector2& pos)
	{
		x = pos.x;
		y = pos.y;
	}

	void operator = (const POINT& pt)
	{
		x = (float)pt.x;
		y = (float)pt.y;
	}

	bool operator == (const _tagVector2& pos)		const
	{
		return x == pos.x && y == pos.y;
	}

	bool operator == (const POINT& pt)		const
	{
		return (LONG)x == pt.x && (LONG)y == pt.y;
	}

	bool operator != (const _tagVector2& pos)		const
	{
		return x != pos.x || y != pos.y;
	}

	bool operator != (const POINT& pt)		const
	{
		return (LONG)x != pt.x || (LONG)y != pt.y;
	}

	// +
	_tagVector2 operator + (const _tagVector2& pos)		const
	{
		_tagVector2	_pos;
		_pos.x = x + pos.x;
		_pos.y = y + pos.y;
		return _pos;
	}

	_tagVector2 operator + (const POINT& pos)		const
	{
		_tagVector2	_pos;
		_pos.x = x + (float)pos.x;
		_pos.y = y + (float)pos.y;
		return _pos;
	}

	_tagVector2 operator + (float fValue)		const
	{
		_tagVector2	_pos;
		_pos.x = x + fValue;
		_pos.y = y + fValue;
		return _pos;
	}

	// 전역함수 오버로딩
	friend _tagVector2 operator + (float f, _tagVector2 v)
	{
		v.x += f;
		v.y += f;
		return v;
	}

	// +=
	void operator += (const _tagVector2& pos)
	{
		x += pos.x;
		y += pos.y;
	}

	void operator += (const POINT& pos)
	{
		x += (float)pos.x;
		y += (float)pos.y;
	}

	void operator += (float fValue)
	{
		x += fValue;
		y += fValue;
	}

	// -
	_tagVector2 operator - (const _tagVector2& pos)		const
	{
		_tagVector2	_pos;
		_pos.x = x - pos.x;
		_pos.y = y - pos.y;
		return _pos;
	}

	_tagVector2 operator - (const POINT& pos)		const
	{
		_tagVector2	_pos;
		_pos.x = x - (float)pos.x;
		_pos.y = y - (float)pos.y;
		return _pos;
	}

	_tagVector2 operator - (float fValue)		const
	{
		_tagVector2	_pos;
		_pos.x = x - fValue;
		_pos.y = y - fValue;
		return _pos;
	}

	// -=
	void operator -= (const _tagVector2& pos)
	{
		x -= pos.x;
		y -= pos.y;
	}

	void operator -= (const POINT& pos)
	{
		x -= (float)pos.x;
		y -= (float)pos.y;
	}

	void operator -= (float fValue)
	{
		x -= fValue;
		y -= fValue;
	}

	// *
	_tagVector2 operator * (const _tagVector2& pos)		const
	{
		_tagVector2	_pos;
		_pos.x = x * pos.x;
		_pos.y = y * pos.y;
		return _pos;
	}

	_tagVector2 operator * (const POINT& pos)		const
	{
		_tagVector2	_pos;
		_pos.x = x * (float)pos.x;
		_pos.y = y * (float)pos.y;
		return _pos;
	}

	_tagVector2 operator * (float fValue)		const
	{
		_tagVector2	_pos;
		_pos.x = x * fValue;
		_pos.y = y * fValue;
		return _pos;
	}

	// *=
	void operator *= (const _tagVector2& pos)
	{
		x *= pos.x;
		y *= pos.y;
	}

	void operator *= (const POINT& pos)
	{
		x *= (float)pos.x;
		y *= (float)pos.y;
	}

	void operator *= (float fValue)
	{
		x *= fValue;
		y *= fValue;
	}

	// /
	_tagVector2 operator / (const _tagVector2& pos)		const
	{
		_tagVector2	_pos;
		_pos.x = x / pos.x;
		_pos.y = y / pos.y;
		return _pos;
	}

	_tagVector2 operator / (const POINT& pos)		const
	{
		_tagVector2	_pos;
		_pos.x = x / (float)pos.x;
		_pos.y = y / (float)pos.y;
		return _pos;
	}

	_tagVector2 operator / (float fValue)		const
	{
		_tagVector2	_pos;
		_pos.x = x / fValue;
		_pos.y = y / fValue;
		return _pos;
	}

	// /=
	void operator /= (const _tagVector2& pos)
	{
		x /= pos.x;
		y /= pos.y;
	}

	void operator /= (const POINT& pos)
	{
		x /= (float)pos.x;
		y /= (float)pos.y;
	}

	void operator /= (float fValue)
	{
		x /= fValue;
		y /= fValue;
	}

	float Length()	const
	{
		if (x == 0.f && y == 0.f)
			return 0.f;

		return sqrtf(x * x + y * y);
	}

	void Normalize()
	{
		float	fLength = Length();
		x /= fLength;
		y /= fLength;
	}

	static _tagVector2 Normalize(const _tagVector2& v)
	{
		_tagVector2	vResult = v;
		vResult.Normalize();
		return vResult;
	}

	float Dot(const _tagVector2& v)	const
	{
		return x * v.x + y * v.y;
	}

	float Angle(const _tagVector2& v)	const
	{
		_tagVector2	v1 = *this;
		_tagVector2	v2 = v;
		v2.Normalize();
		v1.Normalize();

		// 두 단위벡터를 내적하면 코사인 세타가 나온다.
		float	fDot = v2.Dot(v1);

		// 역함수를 이용해서 각도를 구한다.
		float	fAngle = acosf(fDot);

		// 라디안값을 일반 각도로 바꿔준다.
		return RadianToAngle(fAngle);
	}

	float AngleAxis()	const
	{
		_tagVector2	v1(1.f, 0.f);
		_tagVector2	v2 = *this;

		return v1.Angle(v2);
	}

	float Distance(const _tagVector2& v)	const
	{
		_tagVector2	v1 = *this - v;
		return v1.Length();
	}

	static _tagVector2	Zero;
	static _tagVector2	One;
}Vector2, * PVector2;
