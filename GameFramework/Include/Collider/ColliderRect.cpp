#include "ColliderRect.h"
#include "../Object/Obj.h"
#include "../GameManager.h"
#include "Collision.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "ColliderSphere.h"
#include "../Scene/SceneManager.h"

CColliderRect::CColliderRect():
	m_tRelativeInfo{},
	m_tInfo{}
{
	m_eType = COLLIDER_TYPE::RECT;
}

CColliderRect::CColliderRect(const CColliderRect& collider)	:
	CCollider(collider)
{
	m_tRelativeInfo = collider.m_tRelativeInfo;
	m_tInfo = collider.m_tInfo;
}

CColliderRect::~CColliderRect()
{
	//GET_SINGLE(CInput)->DeleteBindAction("Collider");
}

bool CColliderRect::Init()
{
	//GET_SINGLE(CInput)->AddActionKey("Collider", VK_F2);
	//GET_SINGLE(CInput)->AddBindAction("Collider", KEY_TYPE::DOWN, this, &CColliderRect::RenderSwitch);

	return true;
}

void CColliderRect::Update(float fTime)
{
	CCollider::Update(fTime);

	m_tInfo.fL = m_tRelativeInfo.fL + m_pOwner->GetPos().x;
	m_tInfo.fR = m_tRelativeInfo.fR + m_pOwner->GetPos().x;
	m_tInfo.fT = m_tRelativeInfo.fT + m_pOwner->GetPos().y;
	m_tInfo.fB = m_tRelativeInfo.fB + m_pOwner->GetPos().y;

	m_tSectionInfo = m_tInfo;
}

void CColliderRect::Render(HDC hDC, float fTime)
{
	if (GET_SINGLE(CSceneManager)->GetScene()->GetSceneType() == SCENE_TYPE::ANIMEDIT)
		return;

	CCamera* pCamera = m_pScene->GetMainCamera();

	if (!m_bUI)
	{
		if (m_tInfo.fR <= pCamera->GetPos().x)
			return;

		else if (m_tInfo.fL >= pCamera->GetPos().x + pCamera->GetResolution().x)
			return;

		else if (m_tInfo.fB <= pCamera->GetPos().y)
			return;

		else if (m_tInfo.fT >= pCamera->GetPos().y + pCamera->GetResolution().y)
			return;
	}

	RECT	tRC;

	Vector2	vCameraPos;

	if (!m_bUI)
		vCameraPos = pCamera->GetPos();

	HBRUSH	hBrush = GREENBRUSH;

	if (!EmptyPrevCollision() || m_bMouseCollision)
		hBrush = REDBRUSH;

	tRC.left = (LONG)m_tInfo.fL - (LONG)vCameraPos.x;
	tRC.top = (LONG)m_tInfo.fT - (LONG)vCameraPos.y;
	tRC.right = (LONG)m_tInfo.fR - (LONG)vCameraPos.x;
	tRC.bottom = (LONG)m_tInfo.fB - (LONG)vCameraPos.y;
	FrameRect(hDC, &tRC, hBrush);
}

bool CColliderRect::Collision(CCollider* pDest, float fTime)
{
	switch (pDest->GetColliderType())
	{
	case COLLIDER_TYPE::RECT:
		return CCollision::CollisionRectToRect(this, (CColliderRect*)pDest);
	case COLLIDER_TYPE::SPHERE2D:
		return CCollision::CollisionRectToSphere(this, (CColliderSphere*)pDest);
	}

	return false;
}

bool CColliderRect::CollisionMouse(const Vector2& vMouse)
{
	Vector2	vIntersect;

	return CCollision::CollisionRectToPoint(vIntersect, m_tInfo, vMouse);
}

CColliderRect* CColliderRect::Clone()
{
	return new CColliderRect(*this);
}
