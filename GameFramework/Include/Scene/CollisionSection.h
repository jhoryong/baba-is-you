#pragma once

#include "../Game.h"

class CCollisionSection
{
	friend class CCollisionSectionManager;

private:
	CCollisionSection();
	~CCollisionSection();

private:
	int			m_iIndexX;
	int			m_iIndexY;
	int			m_iIndex;
	Vector2		m_vSize;
	Vector2		m_vPos;
	vector<class CCollider*>	m_vecCollider;

public:
	int GetIndexX()	const
	{
		return m_iIndexX;
	}

	int GetIndexY()	const
	{
		return m_iIndexY;
	}

	int GetIndex()	const
	{
		return m_iIndex;
	}

	Vector2 GetPos()	const
	{
		return m_vPos;
	}

	Vector2 GetSize()	const
	{
		return m_vSize;
	}

public:
	bool Init(int iIndexX, int iIndexY, int iIndex, const Vector2& vPos,
		const Vector2& vSize);
	void AddCollider(class CCollider* pCollider);
	bool CollisionMouse(class CCollider** pMouseCollision, 
		const Vector2& vMousePos, float fTime);
	void Collision(float fTime);
	void Clear();
};

