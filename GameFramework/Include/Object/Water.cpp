#include "Water.h"

#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Input.h"
#include "../TileMap/Tile.h"
#include "../TileMap/TileMap.h"
#include "../GameManager.h"

CWater::CWater() :
	m_iWaterType(0)
{
	m_eCharacterType = CHARACTER_TYPE::WATER;
}

CWater::CWater(const CWater& obj) :
	CCharacter(obj)
{
	m_iWaterType = 0;
	m_eCharacterType = CHARACTER_TYPE::WATER;
}

CWater::~CWater()
{
	GET_SINGLE(CInput)->DeleteBindAction("WaterMoveLeft");
	GET_SINGLE(CInput)->DeleteBindAction("WaterMoveRight");
	GET_SINGLE(CInput)->DeleteBindAction("WaterMoveUp");
	GET_SINGLE(CInput)->DeleteBindAction("WaterMoveDown");
}

bool CWater::Init()
{
	CCharacter::Init();

	CreateAnimation();

	AddAnimationSequence("Water_0");
	AddAnimationSequence("Water_1");
	AddAnimationSequence("Water_2");
	AddAnimationSequence("Water_3");
	AddAnimationSequence("Water_4");
	AddAnimationSequence("Water_5");
	AddAnimationSequence("Water_6");
	AddAnimationSequence("Water_7");
	AddAnimationSequence("Water_8");
	AddAnimationSequence("Water_9");
	AddAnimationSequence("Water_10");
	AddAnimationSequence("Water_11");
	AddAnimationSequence("Water_12");
	AddAnimationSequence("Water_13");
	AddAnimationSequence("Water_14");
	AddAnimationSequence("Water_15");

	return true;
}

bool CWater::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CWater::Start()
{
	CCharacter::Start();

	//m_pName = m_pScene->FindName(m_eCharacterType);

	GET_SINGLE(CInput)->AddActionKey("WaterMoveLeft", VK_LEFT);
	GET_SINGLE(CInput)->AddBindAction("WaterMoveLeft", KEY_TYPE::DOWN, this, &CWater::MoveLeft);
	GET_SINGLE(CInput)->AddBindAction("WaterMoveLeft", KEY_TYPE::ON, this, &CWater::MoveLeftOn);
	GET_SINGLE(CInput)->AddBindAction("WaterMoveLeft", KEY_TYPE::UP, this, &CWater::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("WaterMoveRight", VK_RIGHT);
	GET_SINGLE(CInput)->AddBindAction("WaterMoveRight", KEY_TYPE::DOWN, this, &CWater::MoveRight);
	GET_SINGLE(CInput)->AddBindAction("WaterMoveRight", KEY_TYPE::ON, this, &CWater::MoveRightOn);
	GET_SINGLE(CInput)->AddBindAction("WaterMoveRight", KEY_TYPE::UP, this, &CWater::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("WaterMoveUp", VK_UP);
	GET_SINGLE(CInput)->AddBindAction("WaterMoveUp", KEY_TYPE::DOWN, this, &CWater::MoveUp);
	GET_SINGLE(CInput)->AddBindAction("WaterMoveUp", KEY_TYPE::ON, this, &CWater::MoveUpOn);
	GET_SINGLE(CInput)->AddBindAction("WaterMoveUp", KEY_TYPE::UP, this, &CWater::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("WaterMoveDown", VK_DOWN);
	GET_SINGLE(CInput)->AddBindAction("WaterMoveDown", KEY_TYPE::DOWN, this, &CWater::MoveDown);
	GET_SINGLE(CInput)->AddBindAction("WaterMoveDown", KEY_TYPE::ON, this, &CWater::MoveDownOn);
	GET_SINGLE(CInput)->AddBindAction("WaterMoveDown", KEY_TYPE::UP, this, &CWater::MoveEnd);
}

void CWater::Update(float fTime)
{
	CCharacter::Update(fTime);
}

void CWater::PostUpdate(float fTime)
{
	CCharacter::PostUpdate(fTime);

	CheckWater();

	SetWaterType();

	ChangeWaterAnimation();
}

void CWater::Collision(float fTime)
{
	CCharacter::Collision(fTime);
}

void CWater::PrevRender(float fTime)
{
	CCharacter::PrevRender(fTime);
}

void CWater::Render(HDC hDC, float fTime)
{
	CCharacter::Render(hDC, fTime);
	if (GET_SINGLE(CGameManager)->GetPrintInfo())
	{
		TCHAR   string[64] = { };

		if (m_bState[(int)STATE_TYPE::SINK] == true)
		{
			_stprintf_s(string, TEXT("Water State: SINK"));
		}

		else
			_stprintf_s(string, TEXT("Water State: NOT SINK"));

		TextOut(hDC, 0, 200, string, lstrlen(string));
	}
}

void CWater::PostRender(float fTime)
{
	CCharacter::PostRender(fTime);
}

CWater* CWater::Clone()
{
	return new CWater(*this);
}

void CWater::PlaySinkSound()
{
	int iNumber = rand() % 4;

	switch (iNumber)
	{
	case 0:
		m_pScene->GetSceneResource()->SoundPlay("Sink_0");
		break;
	case 1:
		m_pScene->GetSceneResource()->SoundPlay("Sink_1");
		break;
	case 2:
		m_pScene->GetSceneResource()->SoundPlay("Sink_2");
		break;
	case 3:
		m_pScene->GetSceneResource()->SoundPlay("Sink_3");
		break;
	}
}


void CWater::MoveLeft(float fTime)
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

void CWater::MoveRight(float fTime)
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

void CWater::MoveUp(float fTime)
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

void CWater::MoveDown(float fTime)
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

void CWater::MoveLeftOn(float fTime)
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

void CWater::MoveRightOn(float fTime)
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

void CWater::MoveUpOn(float fTime)
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

void CWater::MoveDownOn(float fTime)
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

void CWater::MoveEnd(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU])
	{
		CCharacter::MoveEnd(fTime);
	}
}


void CWater::CheckWater()
{
	CTile* pTile = nullptr;
	/*if (m_iTileIndexX <= 0
		|| m_iTileIndexY <= 0
		|| m_iTileIndexX >= m_iTileCountX - 1
		|| m_iTileIndexY >= m_iTileCountY - 1)*/
		// Top check
	pTile = m_pTileMap->FindTile(m_iTileIndex - m_iTileCountX);

	if (pTile)
	{
		CWater* pUp = pTile->FindWater();

		if (pUp)
		{
			m_bUp = true;
			SAFE_RELEASE(pUp);
		}

		else
			m_bUp = false;
	}

	else if (m_iTileIndexY <= 0)
		m_bUp = true;

	else
		m_bUp = false;

	// Down check
	pTile = m_pTileMap->FindTile(m_iTileIndex + m_iTileCountX);

	if (pTile)
	{
		CWater* pDown = pTile->FindWater();

		if (pDown || m_iTileIndexY >= m_iTileCountY - 1)
		{
			m_bDown = true;
			SAFE_RELEASE(pDown);
		}

		else
			m_bDown = false;
	}
	else if (m_iTileIndexY >= m_iTileCountY - 1)
		m_bDown = true;
	else
		m_bDown = false;

	// Left check
	pTile = m_pTileMap->FindTile(m_iTileIndex - 1);

	if (pTile)
	{
		CWater* pLeft = pTile->FindWater();

		if (pLeft || m_iTileIndexX <= 0)
		{
			m_bLeft = true;
			SAFE_RELEASE(pLeft);
		}

		else
			m_bLeft = false;
	}
	else if (m_iTileIndexX <= 0)
		m_bLeft = true;
	else
		m_bLeft = false;

	// Right check
	pTile = m_pTileMap->FindTile(m_iTileIndex + 1);

	if (pTile)
	{
		CWater* pRight = pTile->FindWater();

		if (pRight || m_iTileIndexX >= m_iTileCountX - 1)
		{
			m_bRight = true;
			SAFE_RELEASE(pRight);
		}

		else
			m_bRight = false;
	}
	else if (m_iTileIndexX >= m_iTileCountX - 1)
		m_bRight = true;
	else
		m_bRight = false;
}

void CWater::SetWaterType()
{
	if (m_bLeft && m_bRight && m_bUp && m_bDown)
		m_iWaterType = 15;

	else if (m_bLeft && m_bUp && m_bDown)
		m_iWaterType = 14;

	else if (m_bRight && m_bUp && m_bDown)
		m_iWaterType = 11;

	else if (m_bUp && m_bLeft && m_bRight)
		m_iWaterType = 7;

	else if (m_bDown && m_bLeft && m_bRight)
		m_iWaterType = 13;

	else if (m_bUp && m_bLeft)
		m_iWaterType = 6;

	else if (m_bUp && m_bRight)
		m_iWaterType = 3;

	else if (m_bDown && m_bLeft)
		m_iWaterType = 12;

	else if (m_bDown && m_bRight)
		m_iWaterType = 9;

	else if (m_bLeft && m_bRight)
		m_iWaterType = 5;

	else if (m_bUp && m_bDown)
		m_iWaterType = 10;

	else if (m_bUp)
		m_iWaterType = 2;

	else if (m_bDown)
		m_iWaterType = 8;

	else if (m_bLeft)
		m_iWaterType = 4;

	else if (m_bRight)
		m_iWaterType = 1;

	else
		m_iWaterType = 0;

	// None]
	// Up]
	// Down]
	// Left]
	// Right]
	// Up, Right]
	// Up, Left]
	// Down, Left,]
	// Down, Right]
	// Up, Left, Right]
	// Down, Left, Right]
	// Left, Up, Down]
	// Right, Up, Down]
	// Left, Right, Up, Down]
	// In Between Left, Right]
	// In Between Up, Down]
}


void CWater::ChangeWaterAnimation()
{
	switch (m_iWaterType)
	{
	case 0:	ChangeAnimation("Water_0");
		break;
	case 1:ChangeAnimation("Water_1");
		break;
	case 2:ChangeAnimation("Water_2");
		break;
	case 3:ChangeAnimation("Water_3");
		break;
	case 4:ChangeAnimation("Water_4");
		break;
	case 5:ChangeAnimation("Water_5");
		break;
	case 6:ChangeAnimation("Water_6");
		break;
	case 7:ChangeAnimation("Water_7");
		break;
	case 8:ChangeAnimation("Water_8");
		break;
	case 9:ChangeAnimation("Water_9");
		break;
	case 10:ChangeAnimation("Water_10");
		break;
	case 11:ChangeAnimation("Water_11");
		break;
	case 12:ChangeAnimation("Water_12");
		break;
	case 13:ChangeAnimation("Water_13");
		break;
	case 14:ChangeAnimation("Water_14");
		break;
	case 15:ChangeAnimation("Water_15");
		break;
	}
}