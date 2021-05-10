#include "CollisionSection.h"
#include "../Collider/Collider.h"

CCollisionSection::CCollisionSection():
	m_iIndexX(0),
	m_iIndexY(0),
	m_iIndex(0)
{
}

CCollisionSection::~CCollisionSection()
{
}

bool CCollisionSection::Init(int iIndexX, int iIndexY, int iIndex, 
	const Vector2& vPos, const Vector2& vSize)
{
	m_iIndexX = iIndexX;
	m_iIndexY = iIndexY;
	m_iIndex = iIndex;
	m_vPos = vPos;
	m_vSize = vSize;

	m_vecCollider.reserve(1024);

	return true;
}

void CCollisionSection::AddCollider(CCollider* pCollider)
{
	pCollider->AddSection(m_iIndex);
	m_vecCollider.push_back(pCollider);
}

bool CCollisionSection::CollisionMouse(class CCollider** pMouseCollision, 
	const Vector2& vMousePos, float fTime)
{
	size_t	iSize = m_vecCollider.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		if (m_vecCollider[i]->CollisionMouse(vMousePos))
		{
			*pMouseCollision = m_vecCollider[i];
			m_vecCollider[i]->SetMouseCollision(true);
			return true;
		}
	}

	return false;
}

void CCollisionSection::Collision(float fTime)
{
	// ��� �浹ü�� �ݺ��ϸ� ���� �����ӿ� �浹�Ǿ��� �浹ü�� ���� ���
	// �ش� �浹ü�� ���ǰ� ���ϴ� �浹ü�� �ҼӵǴ� ������ ����
	// ��ġ�� ������ ���� ��� �浹 �Ǿ��ٰ� �������� ���·� ������ش�.
	size_t	iSize = m_vecCollider.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		if (m_vecCollider[i]->IsCurrentFrameSectionCheck())
			continue;

		m_vecCollider[i]->SetCurrentFrameSectionCheck(true);

		m_vecCollider[i]->CheckPrevColliderSection(fTime);
	}

	if (m_vecCollider.size() < 2)
		return;

	auto	iter = m_vecCollider.begin();
	auto	iter1 = iter + 1;
	auto	iterEnd = m_vecCollider.end();
	auto	iter1End = iterEnd;
	--iterEnd;

	for (; iter != iterEnd; ++iter)
	{
		iter1 = iter + 1;
		for (; iter1 != iter1End; ++iter1)
		{
			// ���� üũ�ϴ� ���Ǻ��� ������ ���ǿ��� ���� ��ġ�� ������ �ִٸ�
			// �浹�� ���Ѵ�.
			const list<int>* pSectionList = (*iter)->GetCheckSectionList(m_iIndex);

			if ((*iter1)->CheckSectionList(pSectionList))
				continue;

			bool	bIgnore1 = (*iter)->CheckIgnoreObj((*iter1)->GetOwner());
			bool	bIgnore2 = (*iter1)->CheckIgnoreObj((*iter)->GetOwner());

			if ((*iter)->Collision(*iter1, fTime))
			{
				// ���� �浹 ������� ���θ� �־��ش�.
				// ��, ���� ó�� �浹�ÿ��� �־��ش�.
				if (!(*iter)->CheckPrevCollision(*iter1))
				{
					(*iter)->AddPrevCollision(*iter1);
					(*iter1)->AddPrevCollision(*iter);

					if (!bIgnore1)
						(*iter)->CallCollisionCallback(COLLISION_STATE::BEGIN, *iter1, fTime);

					if (!bIgnore2)
						(*iter1)->CallCollisionCallback(COLLISION_STATE::BEGIN, *iter, fTime);
				}

				else
				{
					//(*iter)->CallCollisionCallback(COLLISION_STATE::OVERLAP, *iter1, fTime);
					//(*iter1)->CallCollisionCallback(COLLISION_STATE::OVERLAP, *iter, fTime);
				}
			}

			else
			{
				// ������ �浹�Ǵ� �浹ü���� �Ǵ��Ѵ�.
				if ((*iter)->CheckPrevCollision(*iter1))
				{
					(*iter)->DeletePrevCollision(*iter1);
					(*iter1)->DeletePrevCollision(*iter);

					if (!bIgnore1)
						(*iter)->CallCollisionCallback(COLLISION_STATE::END, *iter1, fTime);

					if (!bIgnore2)
						(*iter1)->CallCollisionCallback(COLLISION_STATE::END, *iter, fTime);
				}
			}
		}
	}
}

void CCollisionSection::Clear()
{
	size_t	iSize = m_vecCollider.size();
	for (size_t i = 0; i < iSize; ++i)
	{
		m_vecCollider[i]->ClearCollider();
	}

	m_vecCollider.clear();
}
