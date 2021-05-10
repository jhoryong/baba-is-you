#include "Lava.h"


#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Input.h"
#include "../TileMap/Tile.h"
#include "../TileMap/TileMap.h"

CLava::CLava() :
	m_iLavaType(0)
{
	m_eCharacterType = CHARACTER_TYPE::LAVA;
}

CLava::CLava(const CLava& obj) :
	CCharacter(obj)
{
	m_iLavaType = 0;
	m_eCharacterType = CHARACTER_TYPE::LAVA;
}

CLava::~CLava()
{
	GET_SINGLE(CInput)->DeleteBindAction("LavaMoveLeft");
	GET_SINGLE(CInput)->DeleteBindAction("LavaMoveRight");
	GET_SINGLE(CInput)->DeleteBindAction("LavaMoveUp");
	GET_SINGLE(CInput)->DeleteBindAction("LavaMoveDown");
}

bool CLava::Init()
{
	CCharacter::Init();

	CreateAnimation();

	AddAnimationSequence("Lava_0");
	AddAnimationSequence("Lava_1");
	AddAnimationSequence("Lava_2");
	AddAnimationSequence("Lava_3");
	AddAnimationSequence("Lava_4");
	AddAnimationSequence("Lava_5");
	AddAnimationSequence("Lava_6");
	AddAnimationSequence("Lava_7");
	AddAnimationSequence("Lava_8");
	AddAnimationSequence("Lava_9");
	AddAnimationSequence("Lava_10");
	AddAnimationSequence("Lava_11");
	AddAnimationSequence("Lava_12");
	AddAnimationSequence("Lava_13");
	AddAnimationSequence("Lava_14");
	AddAnimationSequence("Lava_15");

	return true;
}

bool CLava::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CLava::Start()
{
	CCharacter::Start();

	//m_pName = m_pScene->FindName(m_eCharacterType);

	GET_SINGLE(CInput)->AddActionKey("LavaMoveLeft", VK_LEFT);
	GET_SINGLE(CInput)->AddBindAction("LavaMoveLeft", KEY_TYPE::DOWN, this, &CLava::MoveLeft);
	GET_SINGLE(CInput)->AddBindAction("LavaMoveLeft", KEY_TYPE::ON, this, &CLava::MoveLeftOn);
	GET_SINGLE(CInput)->AddBindAction("LavaMoveLeft", KEY_TYPE::UP, this, &CLava::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("LavaMoveRight", VK_RIGHT);
	GET_SINGLE(CInput)->AddBindAction("LavaMoveRight", KEY_TYPE::DOWN, this, &CLava::MoveRight);
	GET_SINGLE(CInput)->AddBindAction("LavaMoveRight", KEY_TYPE::ON, this, &CLava::MoveRightOn);
	GET_SINGLE(CInput)->AddBindAction("LavaMoveRight", KEY_TYPE::UP, this, &CLava::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("LavaMoveUp", VK_UP);
	GET_SINGLE(CInput)->AddBindAction("LavaMoveUp", KEY_TYPE::DOWN, this, &CLava::MoveUp);
	GET_SINGLE(CInput)->AddBindAction("LavaMoveUp", KEY_TYPE::ON, this, &CLava::MoveUpOn);
	GET_SINGLE(CInput)->AddBindAction("LavaMoveUp", KEY_TYPE::UP, this, &CLava::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("LavaMoveDown", VK_DOWN);
	GET_SINGLE(CInput)->AddBindAction("LavaMoveDown", KEY_TYPE::DOWN, this, &CLava::MoveDown);
	GET_SINGLE(CInput)->AddBindAction("LavaMoveDown", KEY_TYPE::ON, this, &CLava::MoveDownOn);
	GET_SINGLE(CInput)->AddBindAction("LavaMoveDown", KEY_TYPE::UP, this, &CLava::MoveEnd);
}

void CLava::Update(float fTime)
{
	CCharacter::Update(fTime);
}

void CLava::PostUpdate(float fTime)
{
	CCharacter::PostUpdate(fTime);

	CheckLava();

	SetLavaType();

	ChangeLavaAnimation();
}

void CLava::Collision(float fTime)
{
	CCharacter::Collision(fTime);
}

void CLava::PrevRender(float fTime)
{
	CCharacter::PrevRender(fTime);
}

void CLava::Render(HDC hDC, float fTime)
{
	CCharacter::Render(hDC, fTime);

	//TCHAR   string[64] = { };

	//if (m_bState[(int)STATE_TYPE::SINK] == true)
	//{
	//	_stprintf_s(string, TEXT("Lava State: SINK"));
	//}

	//else
	//	_stprintf_s(string, TEXT("Lava State: NOT SINK"));

	//TextOut(hDC, 0, 200, string, lstrlen(string));
}

void CLava::PostRender(float fTime)
{
	CCharacter::PostRender(fTime);

	if (m_bState[(int)STATE_TYPE::MELT])
	{
		if (!m_pScene->GetLavaMelt())
			PlayMeltSound();

		m_pScene->SetLavaMelt();
		m_bMelt = true;
	}
}

CLava* CLava::Clone()
{
	return new CLava(*this);
}

void CLava::PlayMeltSound()
{
	int iNumber = rand() % 6;

	switch (iNumber)
	{
	case 0:
		m_pScene->GetSceneResource()->SoundPlay("Melt_0");
		break;
	case 1:
		m_pScene->GetSceneResource()->SoundPlay("Melt_1");
		break;
	case 2:
		m_pScene->GetSceneResource()->SoundPlay("Melt_2");
		break;
	case 3:
		m_pScene->GetSceneResource()->SoundPlay("Melt_3");
		break;
	case 4:
		m_pScene->GetSceneResource()->SoundPlay("Melt_4");
		break;
	case 5:
		m_pScene->GetSceneResource()->SoundPlay("Melt_5");
		break;
	}
}


void CLava::MoveLeft(float fTime)
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

void CLava::MoveRight(float fTime)
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

void CLava::MoveUp(float fTime)
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

void CLava::MoveDown(float fTime)
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

void CLava::MoveLeftOn(float fTime)
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

void CLava::MoveRightOn(float fTime)
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

void CLava::MoveUpOn(float fTime)
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

void CLava::MoveDownOn(float fTime)
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

void CLava::MoveEnd(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU])
	{
		CCharacter::MoveEnd(fTime);
	}
}


void CLava::CheckLava()
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
		CLava* pUp = pTile->FindLava();

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
		CLava* pDown = pTile->FindLava();

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
		CLava* pLeft = pTile->FindLava();

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
		CLava* pRight = pTile->FindLava();

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

void CLava::SetLavaType()
{
	if (m_bLeft && m_bRight && m_bUp && m_bDown)
		m_iLavaType = 15;

	else if (m_bLeft && m_bUp && m_bDown)
		m_iLavaType = 14;

	else if (m_bRight && m_bUp && m_bDown)
		m_iLavaType = 11;

	else if (m_bUp && m_bLeft && m_bRight)
		m_iLavaType = 7;

	else if (m_bDown && m_bLeft && m_bRight)
		m_iLavaType = 13;

	else if (m_bUp && m_bLeft)
		m_iLavaType = 6;

	else if (m_bUp && m_bRight)
		m_iLavaType = 3;

	else if (m_bDown && m_bLeft)
		m_iLavaType = 12;

	else if (m_bDown && m_bRight)
		m_iLavaType = 9;

	else if (m_bLeft && m_bRight)
		m_iLavaType = 5;

	else if (m_bUp && m_bDown)
		m_iLavaType = 10;

	else if (m_bUp)
		m_iLavaType = 2;

	else if (m_bDown)
		m_iLavaType = 8;

	else if (m_bLeft)
		m_iLavaType = 4;

	else if (m_bRight)
		m_iLavaType = 1;

	else
		m_iLavaType = 0;

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


void CLava::ChangeLavaAnimation()
{
	switch (m_iLavaType)
	{
	case 0:	ChangeAnimation("Lava_0");
		break;
	case 1:ChangeAnimation("Lava_1");
		break;
	case 2:ChangeAnimation("Lava_2");
		break;
	case 3:ChangeAnimation("Lava_3");
		break;
	case 4:ChangeAnimation("Lava_4");
		break;
	case 5:ChangeAnimation("Lava_5");
		break;
	case 6:ChangeAnimation("Lava_6");
		break;
	case 7:ChangeAnimation("Lava_7");
		break;
	case 8:ChangeAnimation("Lava_8");
		break;
	case 9:ChangeAnimation("Lava_9");
		break;
	case 10:ChangeAnimation("Lava_10");
		break;
	case 11:ChangeAnimation("Lava_11");
		break;
	case 12:ChangeAnimation("Lava_12");
		break;
	case 13:ChangeAnimation("Lava_13");
		break;
	case 14:ChangeAnimation("Lava_14");
		break;
	case 15:ChangeAnimation("Lava_15");
		break;
	}
}