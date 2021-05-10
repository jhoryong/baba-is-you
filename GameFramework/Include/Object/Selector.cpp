#include "Selector.h"

#include "../Input.h"
#include "../Scene/Scene.h"
#include "../TileMap/Tile.h"
#include "Number.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneStage.h"
#include "../Scene/SceneMainMap.h"
#include "../Scene/SceneResource.h"
#include "../GameManager.h"

CSelector::CSelector()
{
	m_eCharacterType = CHARACTER_TYPE::SELECTOR;
	m_bState[(int)STATE_TYPE::YOU] = true;
}

CSelector::CSelector(const CSelector& obj) :
	CCharacter(obj)
{
	m_eCharacterType = CHARACTER_TYPE::SELECTOR;
	m_bState[(int)STATE_TYPE::YOU] = true;
}

CSelector::~CSelector()
{
	GET_SINGLE(CInput)->DeleteBindAction("SelectEnterStage");
	GET_SINGLE(CInput)->DeleteBindAction("SelectMoveLeft");
	GET_SINGLE(CInput)->DeleteBindAction("SelectMoveRight");
	GET_SINGLE(CInput)->DeleteBindAction("SelectMoveUp");
	GET_SINGLE(CInput)->DeleteBindAction("SelectMoveDown");
}

bool CSelector::Init()
{
	CCharacter::Init();

	CreateAnimation();
	AddAnimationSequence("Selector");

	return true;
}

bool CSelector::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CSelector::Start()
{
	CCharacter::Start();

	GET_SINGLE(CInput)->AddActionKey("SelectEnterStage", VK_RETURN);
	GET_SINGLE(CInput)->AddBindAction("SelectEnterStage", KEY_TYPE::DOWN, this, &CSelector::EnterStage);

	GET_SINGLE(CInput)->AddActionKey("SelectMoveLeft", VK_LEFT);

	GET_SINGLE(CInput)->AddBindAction("SelectMoveLeft", KEY_TYPE::DOWN, this, &CSelector::MoveLeft);
	GET_SINGLE(CInput)->AddBindAction("SelectMoveLeft", KEY_TYPE::ON, this, &CSelector::MoveLeftOn);
	GET_SINGLE(CInput)->AddBindAction("SelectMoveLeft", KEY_TYPE::UP, this, &CSelector::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("SelectMoveRight", VK_RIGHT);
	GET_SINGLE(CInput)->AddBindAction("SelectMoveRight", KEY_TYPE::DOWN, this, &CSelector::MoveRight);
	GET_SINGLE(CInput)->AddBindAction("SelectMoveRight", KEY_TYPE::ON, this, &CSelector::MoveRightOn);
	GET_SINGLE(CInput)->AddBindAction("SelectMoveRight", KEY_TYPE::UP, this, &CSelector::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("SelectMoveUp", VK_UP);
	GET_SINGLE(CInput)->AddBindAction("SelectMoveUp", KEY_TYPE::DOWN, this, &CSelector::MoveUp);
	GET_SINGLE(CInput)->AddBindAction("SelectMoveUp", KEY_TYPE::ON, this, &CSelector::MoveUpOn);
	GET_SINGLE(CInput)->AddBindAction("SelectMoveUp", KEY_TYPE::UP, this, &CSelector::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("SelectMoveDown", VK_DOWN);
	GET_SINGLE(CInput)->AddBindAction("SelectMoveDown", KEY_TYPE::DOWN, this, &CSelector::MoveDown);
	GET_SINGLE(CInput)->AddBindAction("SelectMoveDown", KEY_TYPE::ON, this, &CSelector::MoveDownOn);
	GET_SINGLE(CInput)->AddBindAction("SelectMoveDown", KEY_TYPE::UP, this, &CSelector::MoveEnd);

}

void CSelector::Update(float fTime)
{
	m_vSize = Vector2(24.f, 24.f);
	//m_vPivot;
	CCharacter::Update(fTime);
}

void CSelector::PostUpdate(float fTime)
{
	CCharacter::PostUpdate(fTime);
}

void CSelector::Collision(float fTime)
{
	CCharacter::Collision(fTime);
}

void CSelector::PrevRender(float fTime)
{
	CCharacter::PrevRender(fTime);
}

void CSelector::Render(HDC hDC, float fTime)
{
	m_vSize = Vector2(32.f, 32.f);

	CCharacter::Render(hDC, fTime);
	if (GET_SINGLE(CGameManager)->GetPrintInfo())
	{
		// 타일인덱스 출력
		TCHAR   string[64] = { };

		if (m_bMoving)
			_stprintf_s(string, TEXT("m_vMoving: TRUE"));

		else
			_stprintf_s(string, TEXT("m_vMoving: FALSE"));

		TextOut(hDC, 0, 15, string, lstrlen(string));

		// 
		memset(&string, 0, sizeof(TCHAR) * 64);

		_stprintf_s(string, TEXT("StopDir: %0.f, %0.f"), m_vStopDir.x, m_vStopDir.y);

		TextOut(hDC, 0, 30, string, lstrlen(string));
	}
}

void CSelector::PostRender(float fTime)
{
	CCharacter::PostRender(fTime);
}

CSelector* CSelector::Clone()
{
	return new CSelector(*this);
}

void CSelector::SetSelectorPos(int iLevel)
{
	switch (iLevel)
	{
	case 0:
		SetTileIndex(9, 15);
		break;
	case 1:
		SetTileIndex(10, 13);
		break;
	case 2:
		SetTileIndex(10, 12);
		break;
	case 3:
		SetTileIndex(11, 13);
		break;
	case 4:
		SetTileIndex(11, 12);
		break;
	case 5:
		SetTileIndex(10, 11);
		break;
	case 6:
		SetTileIndex(12, 12);
		break;
	case 7:
		SetTileIndex(11, 11);
		break;
	default:
		SetTileIndex(9, 15); // 0
		break;
	}
}

void CSelector::MoveLeft(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] && !m_bMoving && m_iTileIndexX > 0)
	{
		m_bMoveStart = true;
		CCharacter::MoveLeft(fTime);

		if (m_vMoveDir != m_vStopDir)
		{
			SoundPlay();
		}
	}
}

void CSelector::MoveRight(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] && !m_bMoving && m_iTileIndexX < m_iTileCountX - 1)
	{
		m_bMoveStart = true;
		CCharacter::MoveRight(fTime);

		if (m_vMoveDir != m_vStopDir)
		{
			SoundPlay();
		}
	}
}

void CSelector::MoveUp(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] && !m_bMoving && m_iTileIndexY > 0)
	{
		m_bMoveStart = true;
		CCharacter::MoveUp(fTime);

		if (m_vMoveDir != m_vStopDir)
		{
			SoundPlay();
		}
	}
}

void CSelector::MoveDown(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] && !m_bMoving && m_iTileIndexY < m_iTileCountY - 1)
	{
		m_bMoveStart = true;
		CCharacter::MoveDown(fTime);

		if (m_vMoveDir != m_vStopDir)
		{
			SoundPlay();
		}
	}
}

void CSelector::MoveLeftOn(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] && !m_bMoving && m_iTileIndexX > 0)
	{
		m_fWaitAcc += fTime;

		if (m_fWaitAcc >= m_fWait)
		{
			m_fWaitAcc -= m_fWait;
			m_bMoveStart = true;
			CCharacter::MoveLeftOn(fTime);

			if (m_vMoveDir != m_vStopDir)
			{
				SoundPlay();
			}
		}
	}
}

void CSelector::MoveRightOn(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] && !m_bMoving && m_iTileIndexX < m_iTileCountX - 1)
	{
		m_fWaitAcc += fTime;

		if (m_fWaitAcc >= m_fWait)
		{
			m_fWaitAcc -= m_fWait;
			m_bMoveStart = true;
			CCharacter::MoveRightOn(fTime);

			if (m_vMoveDir != m_vStopDir)
			{
				SoundPlay();
			}
		}
	}
}

void CSelector::MoveUpOn(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] && !m_bMoving && m_iTileIndexY > 0)
	{
		m_fWaitAcc += fTime;

		if (m_fWaitAcc >= m_fWait)
		{
			m_fWaitAcc -= m_fWait;
			m_bMoveStart = true;
			CCharacter::MoveUpOn(fTime);

			if (m_vMoveDir != m_vStopDir)
			{
				SoundPlay();
			}
		}
	}
}

void CSelector::MoveDownOn(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] && !m_bMoving && m_iTileIndexY < m_iTileCountY - 1)
	{
		m_fWaitAcc += fTime;

		if (m_fWaitAcc >= m_fWait)
		{
			m_fWaitAcc -= m_fWait;
			m_bMoveStart = true;
			CCharacter::MoveDownOn(fTime);

			if (m_vMoveDir != m_vStopDir)
			{
				SoundPlay();
			}
		}
	}
}

void CSelector::MoveEnd(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU])
	{
		m_bMoveStart = false;
		CCharacter::MoveEnd(fTime);
	}
}

void CSelector::EnterStage(float fTime)
{
	// 현재 위치의 오브젝트를 얻어온다.
	CNumber* pNumber = m_pTile->FindNumber();

	if (pNumber)
	{
		int iLevel = pNumber->GetNumber();

		((CSceneMainMap*)m_pScene)->SetLevel(iLevel);
		((CSceneMainMap*)m_pScene)->SetSelect(true);

		SAFE_RELEASE(pNumber)
	}
}

