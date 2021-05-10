#include "UI.h"
#include "../Collider/ColliderRect.h"
#include "../Collider/ColliderSphere.h"

CUI::CUI()	:
	m_iZOrder(0),
	m_pBody(nullptr)
{
	m_bUI = true;
}

CUI::~CUI()
{
}

bool CUI::Init()
{
	m_pBody = AddCollider<CColliderRect>("Body");

	m_pBody->EnableUI();

	((CColliderRect*)m_pBody)->SetRectInfo(0.f, 0.f, 100.f, 100.f);


	return true;
}

bool CUI::Init(const char* pFileName, const string& strPathName)
{
	if (!CObj::Init(pFileName, strPathName))
		return false;

	return true;
}

void CUI::Start()
{
	CObj::Start();
}

void CUI::Update(float fTime)
{
	CObj::Update(fTime); // 애니메이션 및 Collider Update 를 해준다.

	if (m_pBody)
	{
		switch (m_pBody->GetColliderType())
		{
		case COLLIDER_TYPE::RECT:
			((CColliderRect*)m_pBody)->SetRectInfo(0.f, 0.f, m_vSize.x, m_vSize.y);
			break;
		case COLLIDER_TYPE::SPHERE2D:
			float	fRadius = sqrtf(m_vSize.x * m_vSize.x + m_vSize.y * m_vSize.y) / 2.f;
			((CColliderSphere*)m_pBody)->SetSphereInfo(m_vSize / 2.f, fRadius);
			break;
		}
	}
	

	//CObj::Update(fTime);
}

void CUI::PostUpdate(float fTime)
{
	CObj::PostUpdate(fTime);
}

void CUI::Collision(float fTime)
{
	CObj::Collision(fTime);
}

void CUI::PrevRender(float fTime)
{
	CObj::PrevRender(fTime);
}

void CUI::Render(HDC hDC, float fTime)
{
	CObj::Render(hDC, fTime);
}

void CUI::PostRender(float fTime)
{
	CObj::PostRender(fTime);
}

CUI* CUI::Clone()
{
	return new CUI(*this);
}

void CUI::ChangeCollider(COLLIDER_TYPE eType)
{
	DeleteCollider("Body");

	m_pBody = nullptr;

	switch (eType)
	{
	case COLLIDER_TYPE::RECT:
		m_pBody = AddCollider<CColliderRect>("Body");
		((CColliderRect*)m_pBody)->SetRectInfo(0.f, 0.f, m_vSize.x, m_vSize.y);

		break;
	case COLLIDER_TYPE::SPHERE2D:
	{
		m_pBody = AddCollider<CColliderSphere>("Body");

		/*Vector2	vCenter;
		vCenter.x = m_vPos.x + m_vSize.x * 0.5f;
		vCenter.y = m_vPos.y + m_vSize.y * 0.5f;*/

		float	fRadius = sqrtf(m_vSize.x * m_vSize.x + m_vSize.y * m_vSize.y) / 2.f;
		((CColliderSphere*)m_pBody)->SetSphereInfo(m_vSize / 2.f, fRadius);
	}
	break;
	}

	if (m_pBody)
		m_pBody->EnableUI();
}
