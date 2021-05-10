#include "Grass.h"

#include "../Scene/Scene.h"
#include "../Input.h"
#include "../TileMap/Tile.h"
#include "../TileMap/TileMap.h"

CGrass::CGrass() :
	m_iGrassType(0)
{
	m_eCharacterType = CHARACTER_TYPE::GRASS;
}

CGrass::CGrass(const CGrass& obj) :
	CCharacter(obj)
{
	m_iGrassType = 0;
	m_eCharacterType = CHARACTER_TYPE::GRASS;
}

CGrass::~CGrass()
{
	GET_SINGLE(CInput)->DeleteBindAction("GrassMoveLeft");
	GET_SINGLE(CInput)->DeleteBindAction("GrassMoveRight");
	GET_SINGLE(CInput)->DeleteBindAction("GrassMoveUp");
	GET_SINGLE(CInput)->DeleteBindAction("GrassMoveDown");
}

bool CGrass::Init()
{
	CCharacter::Init();

	CreateAnimation();

	AddAnimationSequence("Grass_0");
	AddAnimationSequence("Grass_1");
	AddAnimationSequence("Grass_2");
	AddAnimationSequence("Grass_3");
	AddAnimationSequence("Grass_4");
	AddAnimationSequence("Grass_5");
	AddAnimationSequence("Grass_6");
	AddAnimationSequence("Grass_7");
	AddAnimationSequence("Grass_8");
	AddAnimationSequence("Grass_9");
	AddAnimationSequence("Grass_10");
	AddAnimationSequence("Grass_11");
	AddAnimationSequence("Grass_12");
	AddAnimationSequence("Grass_13");
	AddAnimationSequence("Grass_14");
	AddAnimationSequence("Grass_15");

	return true;
}

bool CGrass::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CGrass::Start()
{
	CCharacter::Start();

	//m_pName = m_pScene->FindName(m_eCharacterType);

	GET_SINGLE(CInput)->AddActionKey("GrassMoveLeft", VK_LEFT);

	GET_SINGLE(CInput)->AddBindAction("GrassMoveLeft", KEY_TYPE::DOWN, this, &CGrass::MoveLeft);
	GET_SINGLE(CInput)->AddBindAction("GrassMoveLeft", KEY_TYPE::ON, this, &CGrass::MoveLeftOn);
	GET_SINGLE(CInput)->AddBindAction("GrassMoveLeft", KEY_TYPE::UP, this, &CGrass::MoveEnd);


	GET_SINGLE(CInput)->AddActionKey("GrassMoveRight", VK_RIGHT);

	GET_SINGLE(CInput)->AddBindAction("GrassMoveRight", KEY_TYPE::DOWN, this, &CGrass::MoveRight);
	GET_SINGLE(CInput)->AddBindAction("GrassMoveRight", KEY_TYPE::ON, this, &CGrass::MoveRightOn);
	GET_SINGLE(CInput)->AddBindAction("GrassMoveRight", KEY_TYPE::UP, this, &CGrass::MoveEnd);


	GET_SINGLE(CInput)->AddActionKey("GrassMoveUp", VK_UP);

	GET_SINGLE(CInput)->AddBindAction("GrassMoveUp", KEY_TYPE::DOWN, this, &CGrass::MoveUp);
	GET_SINGLE(CInput)->AddBindAction("GrassMoveUp", KEY_TYPE::ON, this, &CGrass::MoveUpOn);
	GET_SINGLE(CInput)->AddBindAction("GrassMoveUp", KEY_TYPE::UP, this, &CGrass::MoveEnd);


	GET_SINGLE(CInput)->AddActionKey("GrassMoveDown", VK_DOWN);

	GET_SINGLE(CInput)->AddBindAction("GrassMoveDown", KEY_TYPE::DOWN, this, &CGrass::MoveDown);
	GET_SINGLE(CInput)->AddBindAction("GrassMoveDown", KEY_TYPE::ON, this, &CGrass::MoveDownOn);
	GET_SINGLE(CInput)->AddBindAction("GrassMoveDown", KEY_TYPE::UP, this, &CGrass::MoveEnd);

}

void CGrass::Update(float fTime)
{
	CCharacter::Update(fTime);
}

void CGrass::PostUpdate(float fTime)
{
	CCharacter::PostUpdate(fTime);

	CheckGrass();

	SetGrassType();

	ChangeGrassAnimation();
}

void CGrass::Collision(float fTime)
{
	CCharacter::Collision(fTime);
}

void CGrass::PrevRender(float fTime)
{
	CCharacter::PrevRender(fTime);
}

void CGrass::Render(HDC hDC, float fTime)
{
	CCharacter::Render(hDC, fTime);

	//TCHAR   string[64] = { };

	/*if (m_bState[(int)STATE_TYPE::STOP] == true)
	{
		_stprintf_s(string, TEXT("Wall State: STOP"));
	}

	else
		_stprintf_s(string, TEXT("Wall State: NOT STOP"));

	TextOut(hDC, 0, 60, string, lstrlen(string));*/
}

void CGrass::PostRender(float fTime)
{
	CCharacter::PostRender(fTime);
}

CGrass* CGrass::Clone()
{
	return new CGrass(*this);
}


void CGrass::MoveLeft(float fTime)
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

void CGrass::MoveRight(float fTime)
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

void CGrass::MoveUp(float fTime)
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

void CGrass::MoveDown(float fTime)
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

void CGrass::MoveLeftOn(float fTime)
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

void CGrass::MoveRightOn(float fTime)
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

void CGrass::MoveUpOn(float fTime)
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

void CGrass::MoveDownOn(float fTime)
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

void CGrass::MoveEnd(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU])
	{
		CCharacter::MoveEnd(fTime);
	}
}


void CGrass::CheckGrass()
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
		CGrass* pUp = pTile->FindGrass();

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
		CGrass* pDown = pTile->FindGrass();

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
		CGrass* pLeft = pTile->FindGrass();

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
		CGrass* pRight = pTile->FindGrass();

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

void CGrass::SetGrassType()
{
	if (m_bLeft && m_bRight && m_bUp && m_bDown)
		m_iGrassType = 15;

	else if (m_bLeft && m_bUp && m_bDown)
		m_iGrassType = 14;

	else if (m_bRight && m_bUp && m_bDown)
		m_iGrassType = 11;

	else if (m_bUp && m_bLeft && m_bRight)
		m_iGrassType = 7;

	else if (m_bDown && m_bLeft && m_bRight)
		m_iGrassType = 13;

	else if (m_bUp && m_bLeft)
		m_iGrassType = 6;

	else if (m_bUp && m_bRight)
		m_iGrassType = 3;

	else if (m_bDown && m_bLeft)
		m_iGrassType = 12;

	else if (m_bDown && m_bRight)
		m_iGrassType = 9;

	else if (m_bLeft && m_bRight)
		m_iGrassType = 5;

	else if (m_bUp && m_bDown)
		m_iGrassType = 10;

	else if (m_bUp)
		m_iGrassType = 2;

	else if (m_bDown)
		m_iGrassType = 8;

	else if (m_bLeft)
		m_iGrassType = 4;

	else if (m_bRight)
		m_iGrassType = 1;

	else
		m_iGrassType = 0;

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


void CGrass::ChangeGrassAnimation()
{
	switch (m_iGrassType)
	{
	case 0:	ChangeAnimation("Grass_0");
		break;
	case 1:ChangeAnimation("Grass_1");
		break;
	case 2:ChangeAnimation("Grass_2");
		break;
	case 3:ChangeAnimation("Grass_3");
		break;
	case 4:ChangeAnimation("Grass_4");
		break;
	case 5:ChangeAnimation("Grass_5");
		break;
	case 6:ChangeAnimation("Grass_6");
		break;
	case 7:ChangeAnimation("Grass_7");
		break;
	case 8:ChangeAnimation("Grass_8");
		break;
	case 9:ChangeAnimation("Grass_9");
		break;
	case 10:ChangeAnimation("Grass_10");
		break;
	case 11:ChangeAnimation("Grass_11");
		break;
	case 12:ChangeAnimation("Grass_12");
		break;
	case 13:ChangeAnimation("Grass_13");
		break;
	case 14:ChangeAnimation("Grass_14");
		break;
	case 15:ChangeAnimation("Grass_15");
		break;
	}
}