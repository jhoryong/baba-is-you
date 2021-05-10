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

	// ��� ó���� ������ �ʱ�ȭ�Ѵ�.
	m_pWorldSection->Clear();
	m_pUISection->Clear();
}

void CSceneCollision::CollisionMouse(float fTime)
{
	// ���� ���콺�� UI�� �浹�� �غ���.
	// ���н� ���콺�� ������� ��ü�� ó���Ѵ�.
	CCollider* pMouseCollision = nullptr;
	Vector2	vMousePos = GET_SINGLE(CInput)->GetMousePos();
	Vector2	vWorldMousePos = GET_SINGLE(CInput)->GetMouseWorldPos();
	if (!m_pUISection->CollisionMouse(&pMouseCollision, vMousePos, fTime))
	{
		if (!m_pWorldSection->CollisionMouse(&pMouseCollision,
			vWorldMousePos, fTime))
		{
			// ���� �����ӿ� ���콺�� �浹�Ǵ� ��ü�� ���ٴ� ���̴�.
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

	// ���� �����ӿ� ���콺�� �浹�Ǵ� ��ü�� ���� ��� ������ �浹�Ǵ�
	// ��ü�� ���Ͽ� ���� ��ü������ �Ǵ��Ѵ�.
	if (pMouseCollision)
	{
		// ���� �ε����� ��ü�� ó�� �浹�Ǳ� �����Ѵٴ� ���̴�.
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

			// ������ �浹�Ǵ� ��ü�� �浹�Ǵٰ� �������� �����̴�.
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

		// ���� ��� ���������ӿ� �̹� �浹�� �Ǿ��ٴ� ���̴�.
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
