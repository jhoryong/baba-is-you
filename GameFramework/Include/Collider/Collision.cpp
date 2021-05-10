#include "Collision.h"
#include "ColliderRect.h"
#include "ColliderSphere.h"

bool CCollision::CollisionRectToRect(CColliderRect* pSrc,
	CColliderRect* pDest)
{
	Vector2	vIntersect;

	if (CollisionRectToRect(vIntersect, pSrc->GetInfo(), pDest->GetInfo()))
	{
		pSrc->m_vIntersect = vIntersect;
		pDest->m_vIntersect = vIntersect;

		return true;
	}

	return false;
}

bool CCollision::CollisionRectToRect(Vector2& vIntersect, 
	const RectInfo& tSrc, const RectInfo& tDest)
{
	if (tSrc.fL > tDest.fR)
		return false;

	else if (tDest.fL > tSrc.fR)
		return false;

	else if (tSrc.fT > tDest.fB)
		return false;

	else if (tDest.fT > tSrc.fB)
		return false;

	RectInfo	tIntersectRC;

	tIntersectRC.fL = tSrc.fL > tDest.fL ? tSrc.fL : tDest.fL;
	tIntersectRC.fR = tSrc.fR < tDest.fR ? tSrc.fR : tDest.fR;
	tIntersectRC.fT = tSrc.fT > tDest.fT ? tSrc.fT : tDest.fT;
	tIntersectRC.fB = tSrc.fB < tDest.fB ? tSrc.fB : tDest.fB;

	vIntersect.x = (tIntersectRC.fL + tIntersectRC.fR) / 2.f;
	vIntersect.y = (tIntersectRC.fT + tIntersectRC.fB) / 2.f;

	return true;
}

bool CCollision::CollisionSphereToSphere(CColliderSphere* pSrc, 
	CColliderSphere* pDest)
{
	Vector2	vIntersect;

	if (CollisionSphereToSphere(vIntersect, pSrc->GetInfo(), pDest->GetInfo()))
	{
		pSrc->m_vIntersect = vIntersect;
		pDest->m_vIntersect = vIntersect;

		return true;
	}

	return false;
}

bool CCollision::CollisionSphereToSphere(Vector2& vIntersect,
	const SphereInfo& tSrc, const SphereInfo& tDest)
{
	float	fDist = tSrc.vCenter.Distance(tDest.vCenter);

	if (fDist > tSrc.fRadius + tDest.fRadius)
		return false;

	// 두 원사이의 교점을 구한다.
	Vector2	vDir = tSrc.vCenter - tDest.vCenter;
	vDir.Normalize();

	Vector2	vPoint1, vPoint2;

	vPoint1 = tDest.vCenter + vDir * tDest.fRadius;

	vDir *= -1.f;

	vPoint2 = tSrc.vCenter + vDir * tSrc.fRadius;

	vDir = vPoint1 - vPoint2;

	fDist = vDir.Length() / 2.f;
	vDir.Normalize();

	vIntersect = vPoint2 + vDir * fDist;

	return true;
}

bool CCollision::CollisionRectToSphere(CColliderRect* pSrc,
	CColliderSphere* pDest)
{
	Vector2	vIntersect;

	if (CollisionRectToSphere(vIntersect, pSrc->GetInfo(), pDest->GetInfo()))
	{
		pSrc->m_vIntersect = vIntersect;
		pDest->m_vIntersect = vIntersect;

		return true;
	}

	return false;
}

bool CCollision::CollisionRectToSphere(Vector2& vIntersect, 
	const RectInfo& tSrc, const SphereInfo& tDest)
{
	if ((tSrc.fL <= tDest.vCenter.x && tDest.vCenter.x <= tSrc.fR) ||
		(tSrc.fT <= tDest.vCenter.y && tDest.vCenter.y <= tSrc.fB))
	{
		// 사각형을 반지름만큼 확장시켜준다.
		RectInfo	tExtInfo = {};
		tExtInfo.fL = tSrc.fL - tDest.fRadius;
		tExtInfo.fT = tSrc.fT - tDest.fRadius;
		tExtInfo.fR = tSrc.fR + tDest.fRadius;
		tExtInfo.fB = tSrc.fB + tDest.fRadius;

		if (tExtInfo.fL > tDest.vCenter.x)
			return false;

		else if (tExtInfo.fR < tDest.vCenter.x)
			return false;

		else if (tExtInfo.fT > tDest.vCenter.y)
			return false;

		else if (tExtInfo.fB < tDest.vCenter.y)
			return false;

		Vector2	vCenter;
		vCenter.x = (tSrc.fL + tSrc.fR) / 2.f;
		vCenter.y = (tSrc.fT + tSrc.fB) / 2.f;

		Vector2	vDir = vCenter - tDest.vCenter;
		vDir.Normalize();

		vIntersect = tDest.vCenter + vDir * tDest.fRadius;

		return true;
	}

	// 사각형의 4개의 꼭지점중 하나라도 원 안에 들어오면 충돌이다.
	Vector2	vVertex[4] =
	{
		Vector2(tSrc.fL, tSrc.fT),
		Vector2(tSrc.fR, tSrc.fT),
		Vector2(tSrc.fL, tSrc.fB),
		Vector2(tSrc.fR, tSrc.fB)
	};

	for (int i = 0; i < 4; ++i)
	{
		if (CollisionSphereToPoint(vIntersect, tDest, vVertex[i]))
			return true;
	}

	return false;
}

bool CCollision::CollisionRectToPoint(Vector2& vIntersect, 
	const RectInfo& tSrc, const Vector2& vDest)
{
	if (tSrc.fL > vDest.x)
		return false;

	else if (tSrc.fR < vDest.x)
		return false;

	else if (tSrc.fT > vDest.y)
		return false;

	else if (tSrc.fB < vDest.y)
		return false;

	vIntersect = vDest;

	return true;
}

bool CCollision::CollisionSphereToPoint(Vector2& vIntersect,
	const SphereInfo& tSrc, const Vector2& vDest)
{
	float	fDist = tSrc.vCenter.Distance(vDest);

	if (fDist <= tSrc.fRadius)
	{
		vIntersect = vDest;
		return true;
	}

	return false;
}
