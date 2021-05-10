#include "Rock.h"

#include "../Scene/Scene.h"
#include "../Input.h"
#include "../GameManager.h"

CRock::CRock() 
{
	m_eCharacterType = CHARACTER_TYPE::ROCK;
}

CRock::CRock(const CRock& obj) :
	CCharacter(obj)
{
	m_eCharacterType = CHARACTER_TYPE::ROCK;
}

CRock::~CRock()
{
	GET_SINGLE(CInput)->DeleteBindAction("RockMoveLeft");
	GET_SINGLE(CInput)->DeleteBindAction("RockMoveRight");
	GET_SINGLE(CInput)->DeleteBindAction("RockMoveUp");
	GET_SINGLE(CInput)->DeleteBindAction("RockMoveDown");

	m_pScene->SetReRegisterKeyChar(m_eCharacterType);
}

bool CRock::Init()
{
	CCharacter::Init();

	CreateAnimation();
	AddAnimationSequence("Rock");

	return true;
}

bool CRock::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CRock::Start()
{
	CCharacter::Start();

	//m_pName = m_pScene->FindName(m_eCharacterType);

	GET_SINGLE(CInput)->AddActionKey("RockMoveLeft", VK_LEFT);
	GET_SINGLE(CInput)->AddBindAction("RockMoveLeft", KEY_TYPE::DOWN, this, &CRock::MoveLeft);
	GET_SINGLE(CInput)->AddBindAction("RockMoveLeft", KEY_TYPE::ON, this, &CRock::MoveLeftOn);
	GET_SINGLE(CInput)->AddBindAction("RockMoveLeft", KEY_TYPE::UP, this, &CRock::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("RockMoveRight", VK_RIGHT);
	GET_SINGLE(CInput)->AddBindAction("RockMoveRight", KEY_TYPE::DOWN, this, &CRock::MoveRight);
	GET_SINGLE(CInput)->AddBindAction("RockMoveRight", KEY_TYPE::ON, this, &CRock::MoveRightOn);
	GET_SINGLE(CInput)->AddBindAction("RockMoveRight", KEY_TYPE::UP, this, &CRock::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("RockMoveUp", VK_UP);
	GET_SINGLE(CInput)->AddBindAction("RockMoveUp", KEY_TYPE::DOWN, this, &CRock::MoveUp);
	GET_SINGLE(CInput)->AddBindAction("RockMoveUp", KEY_TYPE::ON, this, &CRock::MoveUpOn);
	GET_SINGLE(CInput)->AddBindAction("RockMoveUp", KEY_TYPE::UP, this, &CRock::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("RockMoveDown", VK_DOWN);
	GET_SINGLE(CInput)->AddBindAction("RockMoveDown", KEY_TYPE::DOWN, this, &CRock::MoveDown);
	GET_SINGLE(CInput)->AddBindAction("RockMoveDown", KEY_TYPE::ON, this, &CRock::MoveDownOn);
	GET_SINGLE(CInput)->AddBindAction("RockMoveDown", KEY_TYPE::UP, this, &CRock::MoveEnd);
	
}

void CRock::Update(float fTime)
{
	CCharacter::Update(fTime);
}

void CRock::PostUpdate(float fTime)
{
	CCharacter::PostUpdate(fTime);
}

void CRock::Collision(float fTime)
{
	CCharacter::Collision(fTime);
}

void CRock::PrevRender(float fTime)
{
	CCharacter::PrevRender(fTime);
}

void CRock::Render(HDC hDC, float fTime)
{
	CCharacter::Render(hDC, fTime);
	if (GET_SINGLE(CGameManager)->GetPrintInfo())
	{
		TCHAR   string[64] = { };

		if (m_bState[(int)STATE_TYPE::PUSH] == true)
		{
			_stprintf_s(string, TEXT("Rock State: PUSH"));
		}

		else
			_stprintf_s(string, TEXT("Rock State: NOT PUSH"));

		TextOut(hDC, 0, 30, string, lstrlen(string));

		//memset(string, 0, 64);

		//_stprintf_s(string, TEXT("RockWaitAcc : %0.2f"), m_fWaitAcc);

		//TextOut(hDC, m_vRelPos.x - m_vSize.x, m_vRelPos.y - m_vSize.y, string, lstrlen(string));
	}
}

void CRock::PostRender(float fTime)
{
	CCharacter::PostRender(fTime);
}

CRock* CRock::Clone()
{
	return new CRock(*this);
}

void CRock::RegisterKey()
{
	GET_SINGLE(CInput)->AddActionKey("RockMoveLeft", VK_LEFT);
	GET_SINGLE(CInput)->AddBindAction("RockMoveLeft", KEY_TYPE::DOWN, this, &CRock::MoveLeft);
	GET_SINGLE(CInput)->AddBindAction("RockMoveLeft", KEY_TYPE::ON, this, &CRock::MoveLeftOn);
	GET_SINGLE(CInput)->AddBindAction("RockMoveLeft", KEY_TYPE::UP, this, &CRock::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("RockMoveRight", VK_RIGHT);
	GET_SINGLE(CInput)->AddBindAction("RockMoveRight", KEY_TYPE::DOWN, this, &CRock::MoveRight);
	GET_SINGLE(CInput)->AddBindAction("RockMoveRight", KEY_TYPE::ON, this, &CRock::MoveRightOn);
	GET_SINGLE(CInput)->AddBindAction("RockMoveRight", KEY_TYPE::UP, this, &CRock::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("RockMoveUp", VK_UP);
	GET_SINGLE(CInput)->AddBindAction("RockMoveUp", KEY_TYPE::DOWN, this, &CRock::MoveUp);
	GET_SINGLE(CInput)->AddBindAction("RockMoveUp", KEY_TYPE::ON, this, &CRock::MoveUpOn);
	GET_SINGLE(CInput)->AddBindAction("RockMoveUp", KEY_TYPE::UP, this, &CRock::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("RockMoveDown", VK_DOWN);
	GET_SINGLE(CInput)->AddBindAction("RockMoveDown", KEY_TYPE::DOWN, this, &CRock::MoveDown);
	GET_SINGLE(CInput)->AddBindAction("RockMoveDown", KEY_TYPE::ON, this, &CRock::MoveDownOn);
	GET_SINGLE(CInput)->AddBindAction("RockMoveDown", KEY_TYPE::UP, this, &CRock::MoveEnd);
}

void CRock::MoveLeft(float fTime)
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

void CRock::MoveRight(float fTime)
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

void CRock::MoveUp(float fTime)
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

void CRock::MoveDown(float fTime)
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

void CRock::MoveLeftOn(float fTime)
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

void CRock::MoveRightOn(float fTime)
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

void CRock::MoveUpOn(float fTime)
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

void CRock::MoveDownOn(float fTime)
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

void CRock::MoveEnd(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU])
	{
		CCharacter::MoveEnd(fTime);
	}
}
