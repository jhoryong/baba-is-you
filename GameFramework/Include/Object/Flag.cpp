#include "Flag.h"

#include "../Input.h"
#include "../Scene/Scene.h"
#include "../GameManager.h"

CFlag::CFlag()
{
	m_eCharacterType = CHARACTER_TYPE::FLAG;
}

CFlag::CFlag(const CFlag& obj) :
	CCharacter(obj)
{
	m_eCharacterType = CHARACTER_TYPE::FLAG;
}

CFlag::~CFlag()
{
	GET_SINGLE(CInput)->DeleteBindAction("FlagMoveLeft");
	GET_SINGLE(CInput)->DeleteBindAction("FlagMoveRight");
	GET_SINGLE(CInput)->DeleteBindAction("FlagMoveUp");
	GET_SINGLE(CInput)->DeleteBindAction("FlagMoveDown");

	m_pScene->SetReRegisterKeyChar(m_eCharacterType);
}

bool CFlag::Init()
{
	CCharacter::Init();

	CreateAnimation();
	AddAnimationSequence("Flag");

	return true;
}

bool CFlag::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CFlag::Start()
{
	CCharacter::Start();

	//m_pName = m_pScene->FindName(m_eCharacterType);

	GET_SINGLE(CInput)->AddActionKey("FlagMoveLeft", VK_LEFT);
	
		GET_SINGLE(CInput)->AddBindAction("FlagMoveLeft", KEY_TYPE::DOWN, this, &CFlag::MoveLeft);
		GET_SINGLE(CInput)->AddBindAction("FlagMoveLeft", KEY_TYPE::ON, this, &CFlag::MoveLeftOn);
		GET_SINGLE(CInput)->AddBindAction("FlagMoveLeft", KEY_TYPE::UP, this, &CFlag::MoveEnd);
	

	GET_SINGLE(CInput)->AddActionKey("FlagMoveRight", VK_RIGHT);
	
		GET_SINGLE(CInput)->AddBindAction("FlagMoveRight", KEY_TYPE::DOWN, this, &CFlag::MoveRight);
		GET_SINGLE(CInput)->AddBindAction("FlagMoveRight", KEY_TYPE::ON, this, &CFlag::MoveRightOn);
		GET_SINGLE(CInput)->AddBindAction("FlagMoveRight", KEY_TYPE::UP, this, &CFlag::MoveEnd);
	

	GET_SINGLE(CInput)->AddActionKey("FlagMoveUp", VK_UP);
	
		GET_SINGLE(CInput)->AddBindAction("FlagMoveUp", KEY_TYPE::DOWN, this, &CFlag::MoveUp);
		GET_SINGLE(CInput)->AddBindAction("FlagMoveUp", KEY_TYPE::ON, this, &CFlag::MoveUpOn);
		GET_SINGLE(CInput)->AddBindAction("FlagMoveUp", KEY_TYPE::UP, this, &CFlag::MoveEnd);
	

		GET_SINGLE(CInput)->AddActionKey("FlagMoveDown", VK_DOWN);
	
		GET_SINGLE(CInput)->AddBindAction("FlagMoveDown", KEY_TYPE::DOWN, this, &CFlag::MoveDown);
		GET_SINGLE(CInput)->AddBindAction("FlagMoveDown", KEY_TYPE::ON, this, &CFlag::MoveDownOn);
		GET_SINGLE(CInput)->AddBindAction("FlagMoveDown", KEY_TYPE::UP, this, &CFlag::MoveEnd);
	
}

void CFlag::Update(float fTime)
{
	CCharacter::Update(fTime);
}

void CFlag::PostUpdate(float fTime)
{
	CCharacter::PostUpdate(fTime);
}

void CFlag::Collision(float fTime)
{
	CCharacter::Collision(fTime);
}

void CFlag::PrevRender(float fTime)
{
	CCharacter::PrevRender(fTime);
}

void CFlag::Render(HDC hDC, float fTime)
{
	CCharacter::Render(hDC, fTime);
	if (GET_SINGLE(CGameManager)->GetPrintInfo())
	{
		TCHAR string[64] = {};

		if (m_bState[(int)STATE_TYPE::WIN] == true)
		{
			_stprintf_s(string, TEXT("Flag State: WIN"));
		}

		else
			_stprintf_s(string, TEXT("Flag State: NOT WIN"));

		TextOut(hDC, 0, 45, string, lstrlen(string));
	}
}

void CFlag::PostRender(float fTime)
{
	CCharacter::PostRender(fTime);
}

CFlag* CFlag::Clone()
{
	return new CFlag(*this);
}

void CFlag::RegisterKey()
{
	GET_SINGLE(CInput)->AddActionKey("FlagMoveLeft", VK_LEFT);

	GET_SINGLE(CInput)->AddBindAction("FlagMoveLeft", KEY_TYPE::DOWN, this, &CFlag::MoveLeft);
	GET_SINGLE(CInput)->AddBindAction("FlagMoveLeft", KEY_TYPE::ON, this, &CFlag::MoveLeftOn);
	GET_SINGLE(CInput)->AddBindAction("FlagMoveLeft", KEY_TYPE::UP, this, &CFlag::MoveEnd);


	GET_SINGLE(CInput)->AddActionKey("FlagMoveRight", VK_RIGHT);

	GET_SINGLE(CInput)->AddBindAction("FlagMoveRight", KEY_TYPE::DOWN, this, &CFlag::MoveRight);
	GET_SINGLE(CInput)->AddBindAction("FlagMoveRight", KEY_TYPE::ON, this, &CFlag::MoveRightOn);
	GET_SINGLE(CInput)->AddBindAction("FlagMoveRight", KEY_TYPE::UP, this, &CFlag::MoveEnd);


	GET_SINGLE(CInput)->AddActionKey("FlagMoveUp", VK_UP);

	GET_SINGLE(CInput)->AddBindAction("FlagMoveUp", KEY_TYPE::DOWN, this, &CFlag::MoveUp);
	GET_SINGLE(CInput)->AddBindAction("FlagMoveUp", KEY_TYPE::ON, this, &CFlag::MoveUpOn);
	GET_SINGLE(CInput)->AddBindAction("FlagMoveUp", KEY_TYPE::UP, this, &CFlag::MoveEnd);


	GET_SINGLE(CInput)->AddActionKey("FlagMoveDown", VK_DOWN);

	GET_SINGLE(CInput)->AddBindAction("FlagMoveDown", KEY_TYPE::DOWN, this, &CFlag::MoveDown);
	GET_SINGLE(CInput)->AddBindAction("FlagMoveDown", KEY_TYPE::ON, this, &CFlag::MoveDownOn);
	GET_SINGLE(CInput)->AddBindAction("FlagMoveDown", KEY_TYPE::UP, this, &CFlag::MoveEnd);
}

void CFlag::MoveLeft(float fTime)
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

void CFlag::MoveRight(float fTime)
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

void CFlag::MoveUp(float fTime)
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

void CFlag::MoveDown(float fTime)
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

void CFlag::MoveLeftOn(float fTime)
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

void CFlag::MoveRightOn(float fTime)
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

void CFlag::MoveUpOn(float fTime)
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

void CFlag::MoveDownOn(float fTime)
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

void CFlag::MoveEnd(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU])
	{
		CCharacter::MoveEnd(fTime);
	}
}

