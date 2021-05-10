#include "ColliderSphere.h"
#include "../Object/Obj.h"
#include "../GameManager.h"
#include "Collision.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "ColliderRect.h"

CColliderSphere::CColliderSphere()
{
	m_eType = COLLIDER_TYPE::SPHERE2D;
}

CColliderSphere::CColliderSphere(const CColliderSphere& collider) :
	CCollider(collider)
{
	m_tRelativeInfo = collider.m_tRelativeInfo;
	m_tInfo = collider.m_tInfo;
}

CColliderSphere::~CColliderSphere()
{
}

bool CColliderSphere::Init()
{
	return true;
}

void CColliderSphere::Update(float fTime)
{
	CCollider::Update(fTime);

	m_tInfo.vCenter = m_tRelativeInfo.vCenter + m_pOwner->GetPos();

	m_tSectionInfo.fL = m_tInfo.vCenter.x - m_tInfo.fRadius;
	m_tSectionInfo.fT = m_tInfo.vCenter.y - m_tInfo.fRadius;
	m_tSectionInfo.fR = m_tInfo.vCenter.x + m_tInfo.fRadius;
	m_tSectionInfo.fB = m_tInfo.vCenter.y + m_tInfo.fRadius;
}

void CColliderSphere::Render(HDC hDC, float fTime)
{
	CCamera* pCamera = m_pScene->GetMainCamera();

	if (!m_bUI)
	{
		if (m_tInfo.vCenter.x + m_tInfo.fRadius <= pCamera->GetPos().x)
			return;

		else if (m_tInfo.vCenter.x - m_tInfo.fRadius >= pCamera->GetPos().x + pCamera->GetResolution().x)
			return;

		else if (m_tInfo.vCenter.y + m_tInfo.fRadius <= pCamera->GetPos().y)
			return;

		else if (m_tInfo.vCenter.y - m_tInfo.fRadius >= pCamera->GetPos().y + pCamera->GetResolution().y)
			return;
	}

	Vector2	vCameraPos;

	if (!m_bUI)
		vCameraPos = pCamera->GetPos();

	Vector2	vRenderPos = m_tInfo.vCenter - vCameraPos;

	HBRUSH	hBrush = TRANSPARENTBRUSH;
	HPEN		hPen = GREENPEN;

	if (!EmptyPrevCollision() || m_bMouseCollision)
		hPen = REDPEN;

	HPEN	hOldPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Ellipse(hDC, (int)vRenderPos.x - (int)m_tInfo.fRadius, (int)vRenderPos.y - (int)m_tInfo.fRadius,
		(int)vRenderPos.x + (int)m_tInfo.fRadius, (int)vRenderPos.y + (int)m_tInfo.fRadius);

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);
}

bool CColliderSphere::Collision(CCollider* pDest, float fTime)
{
	switch (pDest->GetColliderType())
	{
	case COLLIDER_TYPE::RECT:
		return CCollision::CollisionRectToSphere((CColliderRect*)pDest, this);
	case COLLIDER_TYPE::SPHERE2D:
		return CCollision::CollisionSphereToSphere(this, (CColliderSphere*)pDest);
	}

	return false;
}

bool CColliderSphere::CollisionMouse(const Vector2& vMouse)
{
	Vector2	vIntersect;

	return CCollision::CollisionSphereToPoint(vIntersect, m_tInfo, vMouse);
}

CColliderSphere* CColliderSphere::Clone()
{
	return new CColliderSphere(*this);
}
