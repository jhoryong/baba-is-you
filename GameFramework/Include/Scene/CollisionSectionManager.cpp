#include "CollisionSectionManager.h"
#include "CollisionSection.h"
#include "../Collider/Collider.h"

CCollisionSectionManager::CCollisionSectionManager():
	m_iCountX(0),
	m_iCountY(0)
{
}

CCollisionSectionManager::~CCollisionSectionManager()
{
	SAFE_DELETE_VECLIST(m_vecSection);
}

bool CCollisionSectionManager::CreateSection(int iCountX, int iCountY,
	const Vector2& vStartPos, const Vector2& vSectionSize)
{
	SAFE_DELETE_VECLIST(m_vecSection);
	m_iCountX = iCountX;
	m_iCountY = iCountY;
	m_vSectionSize = vSectionSize;
	m_vStartPos = vStartPos;
	m_vWorldSize = vSectionSize * Vector2((float)iCountX, (float)iCountY);

	m_vecSection.resize((size_t)m_iCountX * (size_t)m_iCountY);

	for (int i = 0; i < m_iCountY; ++i)
	{
		for (int j = 0; j < m_iCountX; ++j)
		{
			CCollisionSection* pSection = new CCollisionSection;

			Vector2	vPos = m_vStartPos + Vector2((float)j, (float)i) * m_vSectionSize;

			pSection->Init(j, i, i * m_iCountX + j, vPos, m_vSectionSize);

			m_vecSection[(size_t)i * (size_t)m_iCountX + (size_t)j] = pSection;
		}
	}

	return true;
}

void CCollisionSectionManager::AddCollider(CCollider* pCollider)
{
	//  섹션 정보를 이용하여 어떤 섹션에 포함되어야 하는지 판단한다.
	RectInfo	tSectionInfo = pCollider->GetSectionInfo();

	// 섹션의 시작정보를 빼준다.
	tSectionInfo.fL -= m_vStartPos.x;
	tSectionInfo.fR -= m_vStartPos.x;
	tSectionInfo.fT -= m_vStartPos.y;
	tSectionInfo.fB -= m_vStartPos.y;

	// 섹션 1개의 가로, 세로 크기로 나누어준다.
	// 이렇게 할 경우 섹션의 크기를 1x1 로해서 계산하는 효과를 줄 수 있다.
	tSectionInfo.fL /= m_vSectionSize.x;
	tSectionInfo.fR /= m_vSectionSize.x;
	tSectionInfo.fT /= m_vSectionSize.y;
	tSectionInfo.fB /= m_vSectionSize.y;

	int	iStartX = (int)tSectionInfo.fL;
	int	iStartY = (int)tSectionInfo.fT;

	int	iEndX = (int)tSectionInfo.fR;
	int	iEndY = (int)tSectionInfo.fB;

	for (int i = iStartY; i <= iEndY; ++i)
	{
		for (int j = iStartX; j <= iEndX; ++j)
		{
			int	iIndex = i * m_iCountX + j;

			m_vecSection[iIndex]->AddCollider(pCollider);
		}
	}
}

bool CCollisionSectionManager::CollisionMouse(class CCollider** pMouseCollision, 
	const Vector2& vMousePos, float fTime)
{
	size_t	iSize = m_vecSection.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		if (m_vecSection[i]->CollisionMouse(pMouseCollision, vMousePos, fTime))
			return true;
	}

	return false;
}

void CCollisionSectionManager::Collision(float fTime)
{
	size_t	iSize = m_vecSection.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		m_vecSection[i]->Collision(fTime);
	}
}

void CCollisionSectionManager::Clear()
{
	size_t	iSize = m_vecSection.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		m_vecSection[i]->Clear();
	}
}
