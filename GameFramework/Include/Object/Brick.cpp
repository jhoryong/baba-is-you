#include "Brick.h"

#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Input.h"
#include "../TileMap/Tile.h"
#include "../TileMap/TileMap.h"

CBrick::CBrick() :
	m_iBrickType(0)
{
	m_eCharacterType = CHARACTER_TYPE::BRICK;
}

CBrick::CBrick(const CBrick& obj) :
	CCharacter(obj)
{
	m_iBrickType = 0;
	m_eCharacterType = CHARACTER_TYPE::BRICK;
}

CBrick::~CBrick()
{
	GET_SINGLE(CInput)->DeleteBindAction("BrickMoveLeft");
	GET_SINGLE(CInput)->DeleteBindAction("BrickMoveRight");
	GET_SINGLE(CInput)->DeleteBindAction("BrickMoveUp");
	GET_SINGLE(CInput)->DeleteBindAction("BrickMoveDown");
}

bool CBrick::Init()
{
	CCharacter::Init();

	CreateAnimation();

	AddAnimationSequence("Brick_0");
	AddAnimationSequence("Brick_1");
	AddAnimationSequence("Brick_2");
	AddAnimationSequence("Brick_3");
	AddAnimationSequence("Brick_4");
	AddAnimationSequence("Brick_5");
	AddAnimationSequence("Brick_6");
	AddAnimationSequence("Brick_7");
	AddAnimationSequence("Brick_8");
	AddAnimationSequence("Brick_9");
	AddAnimationSequence("Brick_10");
	AddAnimationSequence("Brick_11");
	AddAnimationSequence("Brick_12");
	AddAnimationSequence("Brick_13");
	AddAnimationSequence("Brick_14");
	AddAnimationSequence("Brick_15");

	return true;
}

bool CBrick::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CBrick::Start()
{
	CCharacter::Start();

	//m_pName = m_pScene->FindName(m_eCharacterType);

	GET_SINGLE(CInput)->AddActionKey("BrickMoveLeft", VK_LEFT);
	GET_SINGLE(CInput)->AddBindAction("BrickMoveLeft", KEY_TYPE::DOWN, this, &CBrick::MoveLeft);
	GET_SINGLE(CInput)->AddBindAction("BrickMoveLeft", KEY_TYPE::ON, this, &CBrick::MoveLeftOn);
	GET_SINGLE(CInput)->AddBindAction("BrickMoveLeft", KEY_TYPE::UP, this, &CBrick::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("BrickMoveRight", VK_RIGHT);
	GET_SINGLE(CInput)->AddBindAction("BrickMoveRight", KEY_TYPE::DOWN, this, &CBrick::MoveRight);
	GET_SINGLE(CInput)->AddBindAction("BrickMoveRight", KEY_TYPE::ON, this, &CBrick::MoveRightOn);
	GET_SINGLE(CInput)->AddBindAction("BrickMoveRight", KEY_TYPE::UP, this, &CBrick::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("BrickMoveUp", VK_UP);
	GET_SINGLE(CInput)->AddBindAction("BrickMoveUp", KEY_TYPE::DOWN, this, &CBrick::MoveUp);
	GET_SINGLE(CInput)->AddBindAction("BrickMoveUp", KEY_TYPE::ON, this, &CBrick::MoveUpOn);
	GET_SINGLE(CInput)->AddBindAction("BrickMoveUp", KEY_TYPE::UP, this, &CBrick::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("BrickMoveDown", VK_DOWN);
	GET_SINGLE(CInput)->AddBindAction("BrickMoveDown", KEY_TYPE::DOWN, this, &CBrick::MoveDown);
	GET_SINGLE(CInput)->AddBindAction("BrickMoveDown", KEY_TYPE::ON, this, &CBrick::MoveDownOn);
	GET_SINGLE(CInput)->AddBindAction("BrickMoveDown", KEY_TYPE::UP, this, &CBrick::MoveEnd);
}

void CBrick::Update(float fTime)
{
	CCharacter::Update(fTime);
}

void CBrick::PostUpdate(float fTime)
{
	CCharacter::PostUpdate(fTime);

	CheckBrick();

	SetBrickType();

	ChangeBrickAnimation();
}

void CBrick::Collision(float fTime)
{
	CCharacter::Collision(fTime);
}

void CBrick::PrevRender(float fTime)
{
	CCharacter::PrevRender(fTime);
}

void CBrick::Render(HDC hDC, float fTime)
{
	CCharacter::Render(hDC, fTime);

	//TCHAR   string[64] = { };

	//if (m_bState[(int)STATE_TYPE::SINK] == true)
	//{
	//	_stprintf_s(string, TEXT("Brick State: SINK"));
	//}

	//else
	//	_stprintf_s(string, TEXT("Brick State: NOT SINK"));

	//TextOut(hDC, 0, 200, string, lstrlen(string));
}

void CBrick::PostRender(float fTime)
{
	CCharacter::PostRender(fTime);
}

CBrick* CBrick::Clone()
{
	return new CBrick(*this);
}


void CBrick::MoveLeft(float fTime)
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

void CBrick::MoveRight(float fTime)
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

void CBrick::MoveUp(float fTime)
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

void CBrick::MoveDown(float fTime)
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

void CBrick::MoveLeftOn(float fTime)
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

void CBrick::MoveRightOn(float fTime)
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

void CBrick::MoveUpOn(float fTime)
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

void CBrick::MoveDownOn(float fTime)
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

void CBrick::MoveEnd(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU])
	{
		CCharacter::MoveEnd(fTime);
	}
}


void CBrick::CheckBrick()
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
		CBrick* pUp = pTile->FindBrick();

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
		CBrick* pDown = pTile->FindBrick();

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
		CBrick* pLeft = pTile->FindBrick();

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
		CBrick* pRight = pTile->FindBrick();

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

void CBrick::SetBrickType()
{
	if (m_bLeft && m_bRight && m_bUp && m_bDown)
		m_iBrickType = 15;

	else if (m_bLeft && m_bUp && m_bDown)
		m_iBrickType = 14;

	else if (m_bRight && m_bUp && m_bDown)
		m_iBrickType = 11;

	else if (m_bUp && m_bLeft && m_bRight)
		m_iBrickType = 7;

	else if (m_bDown && m_bLeft && m_bRight)
		m_iBrickType = 13;

	else if (m_bUp && m_bLeft)
		m_iBrickType = 6;

	else if (m_bUp && m_bRight)
		m_iBrickType = 3;

	else if (m_bDown && m_bLeft)
		m_iBrickType = 12;

	else if (m_bDown && m_bRight)
		m_iBrickType = 9;

	else if (m_bLeft && m_bRight)
		m_iBrickType = 5;

	else if (m_bUp && m_bDown)
		m_iBrickType = 10;

	else if (m_bUp)
		m_iBrickType = 2;

	else if (m_bDown)
		m_iBrickType = 8;

	else if (m_bLeft)
		m_iBrickType = 4;

	else if (m_bRight)
		m_iBrickType = 1;

	else
		m_iBrickType = 0;

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


void CBrick::ChangeBrickAnimation()
{
	switch (m_iBrickType)
	{
	case 0:	ChangeAnimation("Brick_0");
		break;
	case 1:ChangeAnimation("Brick_1");
		break;
	case 2:ChangeAnimation("Brick_2");
		break;
	case 3:ChangeAnimation("Brick_3");
		break;
	case 4:ChangeAnimation("Brick_4");
		break;
	case 5:ChangeAnimation("Brick_5");
		break;
	case 6:ChangeAnimation("Brick_6");
		break;
	case 7:ChangeAnimation("Brick_7");
		break;
	case 8:ChangeAnimation("Brick_8");
		break;
	case 9:ChangeAnimation("Brick_9");
		break;
	case 10:ChangeAnimation("Brick_10");
		break;
	case 11:ChangeAnimation("Brick_11");
		break;
	case 12:ChangeAnimation("Brick_12");
		break;
	case 13:ChangeAnimation("Brick_13");
		break;
	case 14:ChangeAnimation("Brick_14");
		break;
	case 15:ChangeAnimation("Brick_15");
		break;
	}
}