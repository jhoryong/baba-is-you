#include "Wall.h"

#include "../Scene/Scene.h"
#include "../Input.h"
#include "../TileMap/Tile.h"
#include "../TileMap/TileMap.h"
#include "../GameManager.h"

CWall::CWall():
	m_iWallType(0)
{
	m_eCharacterType = CHARACTER_TYPE::WALL;
}

CWall::CWall(const CWall& obj) :
	CCharacter(obj)
{
	m_iWallType = 0;
	m_eCharacterType = CHARACTER_TYPE::WALL;
}

CWall::~CWall()
{
	GET_SINGLE(CInput)->DeleteBindAction("WallMoveLeft");
	GET_SINGLE(CInput)->DeleteBindAction("WallMoveRight");
	GET_SINGLE(CInput)->DeleteBindAction("WallMoveUp");
	GET_SINGLE(CInput)->DeleteBindAction("WallMoveDown");

	m_pScene->SetReRegisterKeyChar(m_eCharacterType);
}

bool CWall::Init()
{
	CCharacter::Init();

	CreateAnimation();

	AddAnimationSequence("Wall_0");
	AddAnimationSequence("Wall_1");
	AddAnimationSequence("Wall_2");
	AddAnimationSequence("Wall_3");
	AddAnimationSequence("Wall_4");
	AddAnimationSequence("Wall_5");
	AddAnimationSequence("Wall_6");
	AddAnimationSequence("Wall_7");
	AddAnimationSequence("Wall_8");
	AddAnimationSequence("Wall_9");
	AddAnimationSequence("Wall_10");
	AddAnimationSequence("Wall_11");
	AddAnimationSequence("Wall_12");
	AddAnimationSequence("Wall_13");
	AddAnimationSequence("Wall_14");
	AddAnimationSequence("Wall_15");

	return true;
}

bool CWall::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CWall::Start()
{
	CCharacter::Start();

	//m_pName = m_pScene->FindName(m_eCharacterType);

	GET_SINGLE(CInput)->AddActionKey("WallMoveLeft", VK_LEFT);
	
		GET_SINGLE(CInput)->AddBindAction("WallMoveLeft", KEY_TYPE::DOWN, this, &CWall::MoveLeft);
		GET_SINGLE(CInput)->AddBindAction("WallMoveLeft", KEY_TYPE::ON, this, &CWall::MoveLeftOn);
		GET_SINGLE(CInput)->AddBindAction("WallMoveLeft", KEY_TYPE::UP, this, &CWall::MoveEnd);
	

	GET_SINGLE(CInput)->AddActionKey("WallMoveRight", VK_RIGHT);
	
		GET_SINGLE(CInput)->AddBindAction("WallMoveRight", KEY_TYPE::DOWN, this, &CWall::MoveRight);
		GET_SINGLE(CInput)->AddBindAction("WallMoveRight", KEY_TYPE::ON, this, &CWall::MoveRightOn);
		GET_SINGLE(CInput)->AddBindAction("WallMoveRight", KEY_TYPE::UP, this, &CWall::MoveEnd);
	

	GET_SINGLE(CInput)->AddActionKey("WallMoveUp", VK_UP);
	
		GET_SINGLE(CInput)->AddBindAction("WallMoveUp", KEY_TYPE::DOWN, this, &CWall::MoveUp);
		GET_SINGLE(CInput)->AddBindAction("WallMoveUp", KEY_TYPE::ON, this, &CWall::MoveUpOn);
		GET_SINGLE(CInput)->AddBindAction("WallMoveUp", KEY_TYPE::UP, this, &CWall::MoveEnd);
	

		GET_SINGLE(CInput)->AddActionKey("WallMoveDown", VK_DOWN);
	
		GET_SINGLE(CInput)->AddBindAction("WallMoveDown", KEY_TYPE::DOWN, this, &CWall::MoveDown);
		GET_SINGLE(CInput)->AddBindAction("WallMoveDown", KEY_TYPE::ON, this, &CWall::MoveDownOn);
		GET_SINGLE(CInput)->AddBindAction("WallMoveDown", KEY_TYPE::UP, this, &CWall::MoveEnd);
	
}

void CWall::Update(float fTime)
{
	CCharacter::Update(fTime);
}

void CWall::PostUpdate(float fTime)
{
	CCharacter::PostUpdate(fTime);

	CheckWall();

	SetWallType();

	ChangeWallAnimation();
}

void CWall::Collision(float fTime)
{
	CCharacter::Collision(fTime);
}

void CWall::PrevRender(float fTime)
{
	CCharacter::PrevRender(fTime);
}

void CWall::Render(HDC hDC, float fTime)
{
	CCharacter::Render(hDC, fTime);
	if (GET_SINGLE(CGameManager)->GetPrintInfo())
	{
		TCHAR   string[64] = { };

		if (m_bState[(int)STATE_TYPE::STOP] == true)
		{
			_stprintf_s(string, TEXT("Wall State: STOP"));
		}

		else if (m_bState[(int)STATE_TYPE::YOU] == true)
		{
			_stprintf_s(string, TEXT("Wall State: YOU"));

		}

		else
			_stprintf_s(string, TEXT("Wall State: NOT STOP"));

		TextOut(hDC, 0, 60, string, lstrlen(string));
	}
}

void CWall::PostRender(float fTime)
{
	CCharacter::PostRender(fTime);
}

CWall* CWall::Clone()
{
	return new CWall(*this);
}

void CWall::RegisterKey()
{
	GET_SINGLE(CInput)->AddActionKey("WallMoveLeft", VK_LEFT);

	GET_SINGLE(CInput)->AddBindAction("WallMoveLeft", KEY_TYPE::DOWN, this, &CWall::MoveLeft);
	GET_SINGLE(CInput)->AddBindAction("WallMoveLeft", KEY_TYPE::ON, this, &CWall::MoveLeftOn);
	GET_SINGLE(CInput)->AddBindAction("WallMoveLeft", KEY_TYPE::UP, this, &CWall::MoveEnd);


	GET_SINGLE(CInput)->AddActionKey("WallMoveRight", VK_RIGHT);

	GET_SINGLE(CInput)->AddBindAction("WallMoveRight", KEY_TYPE::DOWN, this, &CWall::MoveRight);
	GET_SINGLE(CInput)->AddBindAction("WallMoveRight", KEY_TYPE::ON, this, &CWall::MoveRightOn);
	GET_SINGLE(CInput)->AddBindAction("WallMoveRight", KEY_TYPE::UP, this, &CWall::MoveEnd);


	GET_SINGLE(CInput)->AddActionKey("WallMoveUp", VK_UP);

	GET_SINGLE(CInput)->AddBindAction("WallMoveUp", KEY_TYPE::DOWN, this, &CWall::MoveUp);
	GET_SINGLE(CInput)->AddBindAction("WallMoveUp", KEY_TYPE::ON, this, &CWall::MoveUpOn);
	GET_SINGLE(CInput)->AddBindAction("WallMoveUp", KEY_TYPE::UP, this, &CWall::MoveEnd);


	GET_SINGLE(CInput)->AddActionKey("WallMoveDown", VK_DOWN);

	GET_SINGLE(CInput)->AddBindAction("WallMoveDown", KEY_TYPE::DOWN, this, &CWall::MoveDown);
	GET_SINGLE(CInput)->AddBindAction("WallMoveDown", KEY_TYPE::ON, this, &CWall::MoveDownOn);
	GET_SINGLE(CInput)->AddBindAction("WallMoveDown", KEY_TYPE::UP, this, &CWall::MoveEnd);

}


void CWall::MoveLeft(float fTime)
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

void CWall::MoveRight(float fTime)
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

void CWall::MoveUp(float fTime)
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

void CWall::MoveDown(float fTime)
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

void CWall::MoveLeftOn(float fTime)
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

void CWall::MoveRightOn(float fTime)
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

void CWall::MoveUpOn(float fTime)
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

void CWall::MoveDownOn(float fTime)
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

void CWall::MoveEnd(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU])
	{
		CCharacter::MoveEnd(fTime);
	}
}


void CWall::CheckWall()
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
		CWall* pUp = pTile->FindWall();

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
		CWall* pDown = pTile->FindWall();

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
		CWall* pLeft = pTile->FindWall();

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
		CWall* pRight = pTile->FindWall();

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

void CWall::SetWallType()
{
	if (m_bLeft && m_bRight && m_bUp && m_bDown)
		m_iWallType = 15;

	else if (m_bLeft && m_bUp && m_bDown)
		m_iWallType = 14;

	else if (m_bRight && m_bUp && m_bDown)
		m_iWallType = 11;

	else if (m_bUp && m_bLeft && m_bRight)
		m_iWallType = 7;

	else if (m_bDown && m_bLeft && m_bRight)
		m_iWallType = 13;

	else if (m_bUp && m_bLeft)
		m_iWallType = 6;

	else if (m_bUp && m_bRight)
		m_iWallType = 3;

	else if (m_bDown && m_bLeft)
		m_iWallType = 12;

	else if (m_bDown && m_bRight)
		m_iWallType = 9;

	else if (m_bLeft && m_bRight)
		m_iWallType = 5;

	else if (m_bUp && m_bDown)
		m_iWallType = 10;

	else if (m_bUp)
		m_iWallType = 2;

	else if (m_bDown)
		m_iWallType = 8;

	else if (m_bLeft)
		m_iWallType = 4;

	else if (m_bRight)
		m_iWallType = 1;

	else
		m_iWallType = 0;

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


void CWall::ChangeWallAnimation()
{
	switch (m_iWallType)
	{
	case 0:	ChangeAnimation("Wall_0");
		break;
	case 1:ChangeAnimation("Wall_1");
		break;
	case 2:ChangeAnimation("Wall_2");
		break;
	case 3:ChangeAnimation("Wall_3");
		break;
	case 4:ChangeAnimation("Wall_4");
		break;
	case 5:ChangeAnimation("Wall_5");
		break;
	case 6:ChangeAnimation("Wall_6");
		break;
	case 7:ChangeAnimation("Wall_7");
		break;
	case 8:ChangeAnimation("Wall_8");
		break;
	case 9:ChangeAnimation("Wall_9");
		break;
	case 10:ChangeAnimation("Wall_10");
		break;
	case 11:ChangeAnimation("Wall_11");
		break;
	case 12:ChangeAnimation("Wall_12");
		break;
	case 13:ChangeAnimation("Wall_13");
		break;
	case 14:ChangeAnimation("Wall_14");
		break;
	case 15:ChangeAnimation("Wall_15");
		break;
	}
}
