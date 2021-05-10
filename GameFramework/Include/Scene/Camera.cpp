#include "Camera.h"
#include "../Object/Obj.h"

CCamera::CCamera()	:
	m_pTarget(nullptr),
	m_pReturnCamera(nullptr)
{
}

CCamera::~CCamera()
{
	SAFE_RELEASE(m_pTarget);
}

void CCamera::SetTarget(CObj* pTarget)
{
	SAFE_RELEASE(m_pTarget);
	if (pTarget)
		pTarget->AddRef();

	m_pTarget = pTarget;
}

bool CCamera::Init()
{
	return true;
}

void CCamera::Update(float fTime)
{
	if (m_pTarget)
	{
		Vector2	vTargetPos = m_pTarget->GetPos();

		m_vPos = vTargetPos - m_vTargetPivot * m_vResolution +
			m_vTargetOffset;
	}

	// 카메라의 위치가 월드 사이즈를 벗어날 경우 제한한다.
	if (m_vPos.x < 0.f)
		m_vPos.x = 0.f;

	else if (m_vPos.x + m_vResolution.x > m_vWorldSize.x)
		m_vPos.x = m_vWorldSize.x - m_vResolution.x;

	if (m_vPos.y < 0.f)
		m_vPos.y = 0.f;

	else if (m_vPos.y + m_vResolution.y > m_vWorldSize.y)
		m_vPos.y = m_vWorldSize.y - m_vResolution.y;
}
