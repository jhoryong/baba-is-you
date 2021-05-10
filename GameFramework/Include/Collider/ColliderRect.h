#pragma once

#include "Collider.h"

class CColliderRect :
	public CCollider
{
	friend class CObj;

protected:
	CColliderRect();
	CColliderRect(const CColliderRect& collider);
	virtual ~CColliderRect();

protected:
	RectInfo	m_tRelativeInfo;
	RectInfo	m_tInfo;

public:
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual bool Collision(CCollider* pDest, float fTime);
	virtual bool CollisionMouse(const Vector2& vMouse);
	virtual CColliderRect* Clone();

public:
	void SetRectInfo(float fL, float fT, float fR, float fB)
	{
		m_tRelativeInfo.fL = fL;
		m_tRelativeInfo.fT = fT;
		m_tRelativeInfo.fR = fR;
		m_tRelativeInfo.fB = fB;
	}

public:
	RectInfo GetInfo()	const
	{
		return m_tInfo;
	}
};

