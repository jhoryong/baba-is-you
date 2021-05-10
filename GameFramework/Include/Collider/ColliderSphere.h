#pragma once
#include "Collider.h"
class CColliderSphere :
	public CCollider
{
	friend class CObj;

protected:
	CColliderSphere();
	CColliderSphere(const CColliderSphere& collider);
	virtual ~CColliderSphere();

protected:
	SphereInfo	m_tRelativeInfo;
	SphereInfo	m_tInfo;

public:
	void SetSphereInfo(const Vector2& vCenter, float fRadius)
	{
		m_tRelativeInfo.vCenter = vCenter;
		m_tRelativeInfo.fRadius = fRadius;

		m_tInfo.fRadius = fRadius;
	}

	void SetSphereInfo(float x, float y, float fRadius)
	{
		m_tRelativeInfo.vCenter = Vector2(x, y);
		m_tRelativeInfo.fRadius = fRadius;

		m_tInfo.fRadius = fRadius;
	}

public:
	SphereInfo GetInfo()	const
	{
		return m_tInfo;
	}

public:
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual bool Collision(CCollider* pDest, float fTime);
	virtual bool CollisionMouse(const Vector2& vMouse);
	virtual CColliderSphere* Clone();
};

