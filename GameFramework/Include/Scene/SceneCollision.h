#pragma once

#include "../Game.h"

class CSceneCollision
{
	friend class CScene;

private:
	CSceneCollision();
	~CSceneCollision();

private:
	class CCollisionSectionManager* m_pWorldSection;
	class CCollisionSectionManager* m_pUISection;
	class CCollider*				m_pMouseCollision;

public:
	bool Init();
	void AddCollider(class CCollider* pCollider);
	void Collision(float fTime);

private:
	void CollisionMouse(float fTime);

public:
	void ReleaseMouseCollision(class CCollider* pCollider);
};

