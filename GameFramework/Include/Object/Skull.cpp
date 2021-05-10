#include "Skull.h"

#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Input.h"

CSkull::CSkull()
{
	m_eCharacterType = CHARACTER_TYPE::SKULL;
	memset(m_bState, false, sizeof(bool) * (int)STATE_TYPE::END);
	m_bNone = true;
}

CSkull::CSkull(const CSkull& obj) :
	CCharacter(obj)
{
	m_eCharacterType = CHARACTER_TYPE::SKULL;
	memset(m_bState, false, sizeof(bool) * (int)STATE_TYPE::END);
	m_bNone = true;
}

CSkull::~CSkull()
{
	GET_SINGLE(CInput)->DeleteBindAction("SkullMoveLeft");
	GET_SINGLE(CInput)->DeleteBindAction("SkullMoveRight");
	GET_SINGLE(CInput)->DeleteBindAction("SkullMoveUp");
	GET_SINGLE(CInput)->DeleteBindAction("SkullMoveDown");
}

bool CSkull::Init()
{
	CCharacter::Init();

	CreateAnimation();
	AddAnimationSequence("Skull");

	return true;
}

bool CSkull::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CSkull::Start()
{
	CCharacter::Start();

	//m_pName = m_pScene->FindName(m_eCharacterType);

	GET_SINGLE(CInput)->AddActionKey("SkullMoveLeft", VK_LEFT);
	GET_SINGLE(CInput)->AddBindAction("SkullMoveLeft", KEY_TYPE::DOWN, this, &CSkull::MoveLeft);
	GET_SINGLE(CInput)->AddBindAction("SkullMoveLeft", KEY_TYPE::ON, this, &CSkull::MoveLeftOn);
	GET_SINGLE(CInput)->AddBindAction("SkullMoveLeft", KEY_TYPE::UP, this, &CSkull::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("SkullMoveRight", VK_RIGHT);
	GET_SINGLE(CInput)->AddBindAction("SkullMoveRight", KEY_TYPE::DOWN, this, &CSkull::MoveRight);
	GET_SINGLE(CInput)->AddBindAction("SkullMoveRight", KEY_TYPE::ON, this, &CSkull::MoveRightOn);
	GET_SINGLE(CInput)->AddBindAction("SkullMoveRight", KEY_TYPE::UP, this, &CSkull::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("SkullMoveUp", VK_UP);
	GET_SINGLE(CInput)->AddBindAction("SkullMoveUp", KEY_TYPE::DOWN, this, &CSkull::MoveUp);
	GET_SINGLE(CInput)->AddBindAction("SkullMoveUp", KEY_TYPE::ON, this, &CSkull::MoveUpOn);
	GET_SINGLE(CInput)->AddBindAction("SkullMoveUp", KEY_TYPE::UP, this, &CSkull::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("SkullMoveDown", VK_DOWN);
	GET_SINGLE(CInput)->AddBindAction("SkullMoveDown", KEY_TYPE::DOWN, this, &CSkull::MoveDown);
	GET_SINGLE(CInput)->AddBindAction("SkullMoveDown", KEY_TYPE::ON, this, &CSkull::MoveDownOn);
	GET_SINGLE(CInput)->AddBindAction("SkullMoveDown", KEY_TYPE::UP, this, &CSkull::MoveEnd);
}

void CSkull::Update(float fTime)
{
	CCharacter::Update(fTime);
}

void CSkull::PostUpdate(float fTime)
{
	CCharacter::PostUpdate(fTime);
}

void CSkull::Collision(float fTime)
{
	CCharacter::Collision(fTime);
}

void CSkull::PrevRender(float fTime)
{
	CCharacter::PrevRender(fTime);
}

void CSkull::Render(HDC hDC, float fTime)
{
	CCharacter::Render(hDC, fTime);
}

void CSkull::PostRender(float fTime)
{
	CCharacter::PostRender(fTime);
}

CSkull* CSkull::Clone()
{
	return new CSkull(*this);
}

void CSkull::PlayDefeatSound()
{
	int iNumber = rand() % 4;

	switch (iNumber)
	{
	case 0:
		m_pScene->GetSceneResource()->SoundPlay("Defeat_0");
		break;
	case 1:
		m_pScene->GetSceneResource()->SoundPlay("Defeat_1");
		break;
	case 2:
		m_pScene->GetSceneResource()->SoundPlay("Defeat_2");
		break;
	case 3:
		m_pScene->GetSceneResource()->SoundPlay("Defeat_3");
		break;
	}
}



void CSkull::MoveLeft(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] && !m_bMoving && m_iTileIndexX > 0)
	{
		CCharacter::MoveLeft(fTime);

		if (m_vMoveDir != m_vStopDir)
		{
			SoundPlay();
		}
	}
}

void CSkull::MoveRight(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] && !m_bMoving && m_iTileIndexX < m_iTileCountX - 1)
	{
		CCharacter::MoveRight(fTime);

		if (m_vMoveDir != m_vStopDir)
		{
			SoundPlay();
		}
	}
}

void CSkull::MoveUp(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] && !m_bMoving && m_iTileIndexY > 0)
	{
		CCharacter::MoveUp(fTime);

		if (m_vMoveDir != m_vStopDir)
		{
			SoundPlay();
		}
	}
}

void CSkull::MoveDown(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] && !m_bMoving && m_iTileIndexY < m_iTileCountY - 1)
	{
		CCharacter::MoveDown(fTime);

		if (m_vMoveDir != m_vStopDir)
		{
			SoundPlay();
		}
	}
}

void CSkull::MoveLeftOn(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] && !m_bMoving && m_iTileIndexX > 0)
	{
		m_fWaitAcc += fTime;

		if (m_fWaitAcc >= m_fWait)
		{
			m_fWaitAcc -= m_fWait;

			CCharacter::MoveLeftOn(fTime);

			if (m_vMoveDir != m_vStopDir)
			{
				SoundPlay();
			}
		}
	}
}

void CSkull::MoveRightOn(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] && !m_bMoving && m_iTileIndexX < m_iTileCountX - 1)
	{
		m_fWaitAcc += fTime;

		if (m_fWaitAcc >= m_fWait)
		{
			m_fWaitAcc -= m_fWait;

			CCharacter::MoveRightOn(fTime);

			if (m_vMoveDir != m_vStopDir)
			{
				SoundPlay();
			}
		}
	}
}

void CSkull::MoveUpOn(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] && !m_bMoving && m_iTileIndexY > 0)
	{
		m_fWaitAcc += fTime;

		if (m_fWaitAcc >= m_fWait)
		{
			m_fWaitAcc -= m_fWait;

			CCharacter::MoveUpOn(fTime);

			if (m_vMoveDir != m_vStopDir)
			{
				SoundPlay();
			}
		}
	}
}

void CSkull::MoveDownOn(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] && !m_bMoving && m_iTileIndexY < m_iTileCountY - 1)
	{
		m_fWaitAcc += fTime;

		if (m_fWaitAcc >= m_fWait)
		{
			m_fWaitAcc -= m_fWait;

			CCharacter::MoveDownOn(fTime);

			if (m_vMoveDir != m_vStopDir)
			{
				SoundPlay();
			}
		}
	}
}

void CSkull::MoveEnd(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU])
	{
		CCharacter::MoveEnd(fTime);
	}
}

