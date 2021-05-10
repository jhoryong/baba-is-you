#pragma once

#include "../Game.h"

class CCollisionSectionManager
{
	friend class CSceneCollision;

private:
	CCollisionSectionManager();
	~CCollisionSectionManager();

private:
	vector<class CCollisionSection*>	m_vecSection;
	int		m_iCountX;
	int		m_iCountY;
	Vector2	m_vSectionSize;
	Vector2	m_vWorldSize;
	Vector2	m_vStartPos;

public:
	bool CreateSection(int iCountX, int iCountY, 
		const Vector2& vStartPos, const Vector2& vSectionSize);
	void AddCollider(class CCollider* pCollider);
	bool CollisionMouse(class CCollider** pMouseCollision, 
		const Vector2& vMousePos, float fTime);
	void Collision(float fTime);
	void Clear();
};

