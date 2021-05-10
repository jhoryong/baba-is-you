#include "Collider.h"

#include "../Scene/Scene.h"
#include "../Scene/SceneCollision.h"

CCollider::CCollider()	:
	m_bEnable(true),
	m_bUI(false),
	m_bCurrentFrameSectionCheck(false),
	m_bMouseCollision(false),
	m_tSectionInfo{},
	m_pScene(nullptr),
	m_pOwner(nullptr)
{
}

CCollider::CCollider(const CCollider& collider)
{
	*this = collider;
}

CCollider::~CCollider()
{
	auto	iter = m_PrevCollisionList.begin();
	auto	iterEnd = m_PrevCollisionList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->DeletePrevCollision(this);
		(*iter)->CallCollisionCallback(COLLISION_STATE::END, this, 0.f);
		CallCollisionCallback(COLLISION_STATE::END, *iter, 0.f);
	}

	m_pScene->GetSceneCollision()->ReleaseMouseCollision(this);
}

void CCollider::ClearCollider()
{
	m_SectionList.clear();
	m_bCurrentFrameSectionCheck = false;
}

void CCollider::AddPrevCollision(CCollider* pCollider)
{
	m_PrevCollisionList.push_back(pCollider);
}

bool CCollider::EmptyPrevCollision()
{
	return m_PrevCollisionList.empty();
}

bool CCollider::CheckPrevCollision(CCollider* pCollider)
{
	auto	iter = m_PrevCollisionList.begin();
	auto	iterEnd = m_PrevCollisionList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (*iter == pCollider)
			return true;
	}

	return false;
}

void CCollider::DeletePrevCollision(CCollider* pCollider)
{
	auto	iter = m_PrevCollisionList.begin();
	auto	iterEnd = m_PrevCollisionList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (*iter == pCollider)
		{
			m_PrevCollisionList.erase(iter);
			return;
		}
	}
}

void CCollider::CheckPrevColliderSection(float fTime)
{
	auto	iter = m_PrevCollisionList.begin();
	auto	iterEnd = m_PrevCollisionList.end();

	for (; iter != iterEnd;)
	{
		auto	iterIdx = m_SectionList.begin();
		auto	iterIdxEnd = m_SectionList.end();

		bool	bCheck = false;

		for (; iterIdx != iterIdxEnd; ++iterIdx)
		{
			auto	iterIdx1 = (*iter)->m_SectionList.begin();
			auto	iterIdx1End = (*iter)->m_SectionList.end();

			for (; iterIdx1 != iterIdx1End; ++iterIdx1)
			{
				// 같은 섹션에 들어가있을 경우 이전에 충돌했던 충돌체와
				// 다시 충돌할 가능성이 있으므로 처리를 안한다.
				if (*iterIdx == *iterIdx1)
				{
					bCheck = true;
					break;
				}
			}

			if (bCheck)
				break;
		}

		// 충돌영역끼리 비교가 끝난 후에 서로 겹치는 영역이 없다면
		// 이전 충돌에서 제거한다.
		if (!bCheck)
		{
			CallCollisionCallback(COLLISION_STATE::END, *iter, fTime);
			(*iter)->CallCollisionCallback(COLLISION_STATE::END, this, fTime);

			(*iter)->DeletePrevCollision(this);
			iter = m_PrevCollisionList.erase(iter);
			iterEnd = m_PrevCollisionList.end();

			continue;
		}

		++iter;
	}
}

const list<int>* CCollider::GetCheckSectionList(int iIndex)
{
	m_CheckSectionList.clear();

	auto	iter = m_SectionList.begin();
	auto	iterEnd = m_SectionList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (*iter >= iIndex)
			break;

		m_CheckSectionList.push_back(*iter);
	}

	return &m_CheckSectionList;
}

bool CCollider::CheckSectionList(const list<int>* pList)
{
	list<int>::const_iterator	iter1 = pList->begin();
	list<int>::const_iterator	iter1End = pList->end();

	for (; iter1 != iter1End; ++iter1)
	{
		auto	iter = m_SectionList.begin();
		auto	iterEnd = m_SectionList.end();

		for (; iter != iterEnd; ++iter)
		{
			if (*iter > * iter1)
				break;

			if (*iter == *iter1)
				return true;
		}
	}

	return false;
}

void CCollider::AddIgnoreObj(class CObj* pObj)
{
	m_vecIgnoreObj.push_back(pObj);
}

bool CCollider::CheckIgnoreObj(class CObj* pObj)
{
	size_t	iSize = m_vecIgnoreObj.size();
	for (size_t i = 0; i < iSize; ++i)
	{
		if (m_vecIgnoreObj[i] == pObj)
			return true;
	}

	return false;
}


bool CCollider::Init()
{
	return true;
}

void CCollider::Update(float fTime)
{
}

void CCollider::Render(HDC hDC, float fTime)
{
}

void CCollider::CallCollisionCallback(COLLISION_STATE eState,
	CCollider* pDest, float fTime)
{
	auto	iter = m_CollisionCallback[(size_t)eState].begin();
	auto	iterEnd = m_CollisionCallback[(size_t)eState].end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)(this, pDest, fTime);
	}
}

void CCollider::SetCollisionCallback(COLLISION_STATE eState, void(*pFunc)(CCollider*, CCollider*, float))
{
	m_CollisionCallback[(size_t)eState].push_back(bind(pFunc, placeholders::_1, placeholders::_2, placeholders::_3));
}

void CCollider::CallMouseCollisionCallback(COLLISION_STATE eState,
	const Vector2& vMousePos, float fTime)
{
	auto	iter = m_MouseCollisionCallback[(size_t)eState].begin();
	auto	iterEnd = m_MouseCollisionCallback[(size_t)eState].end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)(this, vMousePos, fTime);
	}
}

void CCollider::SetMouseCollisionCallback(COLLISION_STATE eState, void(*pFunc)(CCollider*, const Vector2&, float))
{
	m_MouseCollisionCallback[(size_t)eState].push_back(bind(pFunc, placeholders::_1, placeholders::_2, placeholders::_3));
}
