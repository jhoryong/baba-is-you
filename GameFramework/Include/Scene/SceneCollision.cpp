#include "SceneCollision.h"
#include "CollisionSectionManager.h"
#include "../GameManager.h"
#include "../Collider/Collider.h"
#include "../Input.h"

CSceneCollision::CSceneCollision()	:
	m_pWorldSection(nullptr),
	m_pUISection(nullptr),
	m_pMouseCollision(nullptr)
{
}

CSceneCollision::~CSceneCollision()
{
	SAFE_DELETE(m_pWorldSection);
	SAFE_DELETE(m_pUISection);
}

bool CSceneCollision::Init()
{
	m_pWorldSection = new CCollisionSectionManager;
	m_pUISection = new CCollisionSectionManager;
	
	//m_pWorldSection->CreateSection(5, 5, Vector2::Zero, Vector2(1000.f, 1000.f));
	m_pWorldSection->CreateSection(1, 1, Vector2::Zero, RESOLUTION);

	Vector2	vRS = GET_SINGLE(CGameManager)->GetResolution();
	m_pUISection->CreateSection(1, 1, Vector2::Zero, vRS);

	return true;
}

void CSceneCollision::AddCollider(CCollider* pCollider)
{
	if (pCollider->IsUI())
		m_pUISection->AddCollider(pCollider);

	else
		m_pWorldSection->AddCollider(pCollider);
}

void CSceneCollision::Collision(float fTime)
{
	CollisionMouse(fTime);

	m_pWorldSection->Collision(fTime);
	m_pUISection->Collision(fTime);

	// 모든 처리가 끝나면 초기화한다.
	m_pWorldSection->Clear();
	m_pUISection->Clear();
}

void CSceneCollision::CollisionMouse(float fTime)
{
	// 먼저 마우스와 UI의 충돌을 해본다.
	// 실패시 마우스와 월드상의 물체를 처리한다.
	CCollider* pMouseCollision = nullptr;
	Vector2	vMousePos = GET_SINGLE(CInput)->GetMousePos();
	Vector2	vWorldMousePos = GET_SINGLE(CInput)->GetMouseWorldPos();
	if (!m_pUISection->CollisionMouse(&pMouseCollision, vMousePos, fTime))
	{
		if (!m_pWorldSection->CollisionMouse(&pMouseCollision,
			vWorldMousePos, fTime))
		{
			// 현재 프레임에 마우스와 충돌되는 물체가 없다는 것이다.
			if (m_pMouseCollision)
			{
				m_pMouseCollision->SetMouseCollision(false);

				if (m_pMouseCollision->IsUI())
				{
					m_pMouseCollision->CallMouseCollisionCallback(COLLISION_STATE::END,
						vMousePos, fTime);
				}

				else
				{
					m_pMouseCollision->CallMouseCollisionCallback(COLLISION_STATE::END,
						vWorldMousePos, fTime);
				}

				m_pMouseCollision = nullptr;
			}
		}
	}

	// 현재 프레임에 마우스와 충돌되는 물체가 있을 경우 이전에 충돌되는
	// 물체와 비교하여 같은 물체인지를 판단한다.
	if (pMouseCollision)
	{
		// 현재 부딪히는 물체는 처음 충돌되기 시작한다는 것이다.
		if (pMouseCollision != m_pMouseCollision)
		{
			if (pMouseCollision->IsUI())
			{
				pMouseCollision->CallMouseCollisionCallback(COLLISION_STATE::BEGIN,
					vMousePos, fTime);
			}

			else
			{
				pMouseCollision->CallMouseCollisionCallback(COLLISION_STATE::BEGIN,
					vWorldMousePos, fTime);
			}

			// 이전에 충돌되던 물체는 충돌되다가 떨어지는 상태이다.
			if (m_pMouseCollision)
			{
				if (m_pMouseCollision->IsUI())
				{
					m_pMouseCollision->CallMouseCollisionCallback(COLLISION_STATE::END,
						vMousePos, fTime);
				}

				else
				{
					m_pMouseCollision->CallMouseCollisionCallback(COLLISION_STATE::END,
						vWorldMousePos, fTime);
				}

				m_pMouseCollision->SetMouseCollision(false);
			}

			m_pMouseCollision = pMouseCollision;
		}

		// 같을 경우 이전프레임에 이미 충돌이 되었다는 것이다.
		else
		{
			if (m_pMouseCollision->IsUI())
			{
				m_pMouseCollision->CallMouseCollisionCallback(COLLISION_STATE::OVERLAP,
					vMousePos, fTime);
			}

			else
			{
				m_pMouseCollision->CallMouseCollisionCallback(COLLISION_STATE::OVERLAP,
					vWorldMousePos, fTime);
			}
		}
	}
}

void CSceneCollision::ReleaseMouseCollision(CCollider* pCollider)
{
	if (m_pMouseCollision == pCollider)
	{
		m_pMouseCollision = nullptr;
	}
}
