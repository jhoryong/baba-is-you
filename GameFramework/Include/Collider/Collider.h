#pragma once

#include "../Game.h"

class CCollider
{
	friend class CObj;
	friend class CCollision;

protected:
	CCollider();
	CCollider(const CCollider& collider);
	virtual ~CCollider() = 0;

protected:
	class CObj*		m_pOwner;
	class CScene*	m_pScene;
	string			m_strName;
	bool			m_bEnable;
	bool			m_bMouseCollision;
	bool			m_bUI;
	bool			m_bCurrentFrameSectionCheck;
	COLLIDER_TYPE	m_eType;
	RectInfo		m_tSectionInfo;
	Vector2			m_vIntersect;

	vector<class CObj*>	m_vecIgnoreObj;
	list<int>			m_SectionList;
	list<int>			m_CheckSectionList;
	list<CCollider*>	m_PrevCollisionList;

	list<function<void(CCollider*, CCollider*, float)>>	
	m_CollisionCallback[(size_t)COLLISION_STATE::MAX];

	list<function<void(CCollider*, const Vector2&, float)>>
	m_MouseCollisionCallback[(size_t)COLLISION_STATE::MAX];
	

public:
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual bool Collision(CCollider* pDest, float fTime) = 0;
	virtual bool CollisionMouse(const Vector2& vMouse) = 0;
	virtual CCollider* Clone() = 0;

public:
	void ClearCollider();
	void AddPrevCollision(CCollider* pCollider);
	bool EmptyPrevCollision();
	bool CheckPrevCollision(CCollider* pCollider);
	void DeletePrevCollision(CCollider* pCollider);
	void CheckPrevColliderSection(float fTime);

public:
	bool CheckSectionList(const list<int>* pList);
	const list<int>* GetCheckSectionList(int iIndex);

// Ignore Object
public:
	void AddIgnoreObj(class CObj* pObj);
	bool CheckIgnoreObj(class CObj* pObj);

// Collision Callback
public:
	void CallCollisionCallback(COLLISION_STATE eState, CCollider* pDest, float fTime);
	void SetCollisionCallback(COLLISION_STATE eState, void(*pFunc)(CCollider*, CCollider*, float));
	template <typename T>
	void SetCollisionCallback(COLLISION_STATE eState,
		T* pObj, void(T::* pFunc)(CCollider*, CCollider*, float))
	{
		m_CollisionCallback[(size_t)eState].push_back(bind(pFunc, pObj, placeholders::_1, placeholders::_2, placeholders::_3));
	}

// Mouse Collision
public:
	void CallMouseCollisionCallback(COLLISION_STATE eState, const Vector2& vMousePos, float fTime);
	void SetMouseCollisionCallback(COLLISION_STATE eState, void(*pFunc)(CCollider*, const Vector2&, float));

	template <typename T>
	void SetMouseCollisionCallback(COLLISION_STATE eState,
		T* pObj, void(T::* pFunc)(CCollider*, const Vector2&, float))
	{
		m_MouseCollisionCallback[(size_t)eState].push_back(bind(pFunc, pObj, placeholders::_1, placeholders::_2, placeholders::_3));
	}

public:
	class CObj* GetOwner()	const
	{
		return m_pOwner;
	}

	bool IsMouseCollision()	const
	{
		return m_bMouseCollision;
	}

	void SetMouseCollision(bool bCollision)
	{
		m_bMouseCollision = bCollision;
	}

	void SetCurrentFrameSectionCheck(bool bCheck)
	{
		m_bCurrentFrameSectionCheck = bCheck;
	}

	bool IsCurrentFrameSectionCheck()	const
	{
		return m_bCurrentFrameSectionCheck;
	}

	bool IsUI()	const
	{
		return m_bUI;
	}

	void EnableUI()
	{
		m_bUI = true;
	}

	COLLIDER_TYPE GetColliderType()	const
	{
		return m_eType;
	}

	string GetName()	const
	{
		return m_strName;
	}

	Vector2 GetIntersect()	const
	{
		return m_vIntersect;
	}

	void SetName(const string& strName)
	{
		m_strName = strName;
	}

	bool IsEnable()	const
	{
		return m_bEnable;
	}

	void Enable(bool bEnable)
	{
		m_bEnable = bEnable;
	}

	RectInfo GetSectionInfo()	const
	{
		return m_tSectionInfo;
	}

	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}

	void AddSection(int iIndex)
	{
		m_SectionList.push_back(iIndex);
	}
};

