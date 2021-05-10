#include "Baba.h"

#include "../Input.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/SceneManager.h"

CBaba::CBaba() :
	m_eAnimType(BABA_ANIMATION::NORMAL)
{
	m_eCharacterType = CHARACTER_TYPE::BABA;
	m_iZOrder = 2;
}

CBaba::CBaba(const CBaba& obj) :
	CCharacter(obj)
{
	m_eCharacterType = CHARACTER_TYPE::BABA;
	m_eAnimType = obj.m_eAnimType;
	m_iZOrder = 2;
}

CBaba::~CBaba()
{
	GET_SINGLE(CInput)->DeleteBindAction("BabaMoveLeft");
	GET_SINGLE(CInput)->DeleteBindAction("BabaMoveRight");
	GET_SINGLE(CInput)->DeleteBindAction("BabaMoveUp");
	GET_SINGLE(CInput)->DeleteBindAction("BabaMoveDown");

	//m_pScene->SetReRegisterKeyChar(m_eCharacterType);
}

bool CBaba::Init()
{
	CCharacter::Init();

	CreateAnimation();

	//AddLoadedAnimationSequence("Baba_Right_Normal");
	AddAnimationSequence("Baba_Right_Normal");
	AddAnimationSequence("Baba_Right_Open");
	AddAnimationSequence("Baba_Right_Close");
	AddAnimationSequence("Baba_Left_Open");
	AddAnimationSequence("Baba_Left_Normal");
	AddAnimationSequence("Baba_Left_Close");
	AddAnimationSequence("Baba_Up_Open");
	AddAnimationSequence("Baba_Up_Normal");
	AddAnimationSequence("Baba_Up_Close");
	AddAnimationSequence("Baba_Down_Open");
	AddAnimationSequence("Baba_Down_Normal");
	AddAnimationSequence("Baba_Down_Close");

	return true;
}

bool CBaba::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CBaba::Start()
{
	CCharacter::Start();
	
	GET_SINGLE(CInput)->AddActionKey("BabaMoveLeft", VK_LEFT);
	GET_SINGLE(CInput)->AddBindAction("BabaMoveLeft", KEY_TYPE::DOWN, this, &CBaba::MoveLeft);
	GET_SINGLE(CInput)->AddBindAction("BabaMoveLeft", KEY_TYPE::ON, this, &CBaba::MoveLeftOn);
	GET_SINGLE(CInput)->AddBindAction("BabaMoveLeft", KEY_TYPE::UP, this, &CBaba::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("BabaMoveRight", VK_RIGHT);
	GET_SINGLE(CInput)->AddBindAction("BabaMoveRight", KEY_TYPE::DOWN, this, &CBaba::MoveRight);
	GET_SINGLE(CInput)->AddBindAction("BabaMoveRight", KEY_TYPE::ON, this, &CBaba::MoveRightOn);
	GET_SINGLE(CInput)->AddBindAction("BabaMoveRight", KEY_TYPE::UP, this, &CBaba::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("BabaMoveUp", VK_UP);
	GET_SINGLE(CInput)->AddBindAction("BabaMoveUp", KEY_TYPE::DOWN, this, &CBaba::MoveUp);
	GET_SINGLE(CInput)->AddBindAction("BabaMoveUp", KEY_TYPE::ON, this, &CBaba::MoveUpOn);
	GET_SINGLE(CInput)->AddBindAction("BabaMoveUp", KEY_TYPE::UP, this, &CBaba::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("BabaMoveDown", VK_DOWN);
	GET_SINGLE(CInput)->AddBindAction("BabaMoveDown", KEY_TYPE::DOWN, this, &CBaba::MoveDown);
	GET_SINGLE(CInput)->AddBindAction("BabaMoveDown", KEY_TYPE::ON, this, &CBaba::MoveDownOn);
	GET_SINGLE(CInput)->AddBindAction("BabaMoveDown", KEY_TYPE::UP, this, &CBaba::MoveEnd);

	//m_pName = m_pScene->FindName(m_eCharacterType);
}

void CBaba::Update(float fTime)
{
	CCharacter::Update(fTime);
}

void CBaba::PostUpdate(float fTime)
{
	CCharacter::PostUpdate(fTime);
}

void CBaba::Collision(float fTime)
{
	CCharacter::Collision(fTime);
}

void CBaba::PrevRender(float fTime)
{
	CCharacter::PrevRender(fTime);
}

void CBaba::Render(HDC hDC, float fTime)
{
	CCharacter::Render(hDC, fTime);

	if (GET_SINGLE(CGameManager)->GetPrintInfo())
	{

		int iSpace = 15;
		int iCount = 4;
		int iX = (int)RESOLUTION.x / 2;
		int iY = 0;

		// 타일인덱스 출력
		TCHAR   string[64] = { };

		_stprintf_s(string, TEXT("Tile Index: %d (%d, %d)"), m_iTileIndex, m_iTileIndexX, m_iTileIndexY);

		TextOut(hDC, iX, iY, string, lstrlen(string));

		// 위치출력
		memset(&string, 0, sizeof(TCHAR) * 64);

		_stprintf_s(string, TEXT("Pos: %0.2f, %0.2f"), m_vPos.x, m_vPos.y);

		TextOut(hDC, iX, iY + iSpace, string, lstrlen(string));

		// 상대위치출력
		memset(&string, 0, sizeof(TCHAR) * 64);

		_stprintf_s(string, TEXT("Rel Pos: %0.2f, %0.2f"), m_vRelPos.x, m_vRelPos.y);

		TextOut(hDC, iX, iY + iSpace * 2, string, lstrlen(string));

		// 현재 위치해 있는 타일의 위치
		memset(&string, 0, sizeof(TCHAR) * 64);

		_stprintf_s(string, TEXT("Tile Start Pos: %0.2f, %0.2f"), m_vTilePos.x, m_vTilePos.y);

		TextOut(hDC, iX, iY + iSpace * 3, string, lstrlen(string));

		// //바바 애니메이션 상태 출력
		//memset(&string, 0, sizeof(TCHAR) * 64);

		//_stprintf_s(string, TEXT("바바 애니메이션 : %d"), m_eAnimType);

		//TextOut(hDC, m_vPos.x, m_vPos.y - iSpace * 5.f, string, lstrlen(string));

		// WaitAcc
		memset(&string, 0, sizeof(TCHAR) * 64);

		_stprintf_s(string, TEXT("WaitAcc: %0.2f"), m_fWaitAcc);

		TextOut(hDC, iX, iY + iSpace * 4, string, lstrlen(string));

		//// MoveOn함수
		memset(&string, 0, sizeof(TCHAR) * 64);

		_stprintf_s(string, TEXT("MoveLeftOn: %d"), m_iMoveCount);

		TextOut(hDC, iX, iY + iSpace * 5, string, lstrlen(string));

		memset(&string, 0, sizeof(TCHAR) * 64);

		if (m_bState[(int)STATE_TYPE::YOU] == true)
		{
			_stprintf_s(string, TEXT("Baba State: YOU"));
		}

		else
			_stprintf_s(string, TEXT("Baba State: NOT YOU"));

		TextOut(hDC, 0, 15, string, lstrlen(string));
	}
}

void CBaba::PostRender(float fTime)
{
	CCharacter::PostRender(fTime);
}

CBaba* CBaba::Clone()
{
	return new CBaba(*this);
}

void CBaba::RegisterKey()
{
	GET_SINGLE(CInput)->AddActionKey("BabaMoveLeft", VK_LEFT);
	GET_SINGLE(CInput)->AddBindAction("BabaMoveLeft", KEY_TYPE::DOWN, this, &CBaba::MoveLeft);
	GET_SINGLE(CInput)->AddBindAction("BabaMoveLeft", KEY_TYPE::ON, this, &CBaba::MoveLeftOn);
	GET_SINGLE(CInput)->AddBindAction("BabaMoveLeft", KEY_TYPE::UP, this, &CBaba::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("BabaMoveRight", VK_RIGHT);
	GET_SINGLE(CInput)->AddBindAction("BabaMoveRight", KEY_TYPE::DOWN, this, &CBaba::MoveRight);
	GET_SINGLE(CInput)->AddBindAction("BabaMoveRight", KEY_TYPE::ON, this, &CBaba::MoveRightOn);
	GET_SINGLE(CInput)->AddBindAction("BabaMoveRight", KEY_TYPE::UP, this, &CBaba::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("BabaMoveUp", VK_UP);
	GET_SINGLE(CInput)->AddBindAction("BabaMoveUp", KEY_TYPE::DOWN, this, &CBaba::MoveUp);
	GET_SINGLE(CInput)->AddBindAction("BabaMoveUp", KEY_TYPE::ON, this, &CBaba::MoveUpOn);
	GET_SINGLE(CInput)->AddBindAction("BabaMoveUp", KEY_TYPE::UP, this, &CBaba::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("BabaMoveDown", VK_DOWN);
	GET_SINGLE(CInput)->AddBindAction("BabaMoveDown", KEY_TYPE::DOWN, this, &CBaba::MoveDown);
	GET_SINGLE(CInput)->AddBindAction("BabaMoveDown", KEY_TYPE::ON, this, &CBaba::MoveDownOn);
	GET_SINGLE(CInput)->AddBindAction("BabaMoveDown", KEY_TYPE::UP, this, &CBaba::MoveEnd);
	
}

void CBaba::MoveLeft(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] // 내가 'YOU' 상태이고
		&& !m_bMoving // 이동중이 아니고
		&& m_iTileIndexX > 0 // 테두리 타일이 아닐 때
		) 
	{
		CCharacter::MoveLeft(fTime);

		if (m_vMoveDir != m_vStopDir)
		{
			SoundPlay();

			ChangeAnimationState();

			ChangeAnimationLeft();
		}
	}
}

void CBaba::MoveRight(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] && !m_bMoving && (m_iTileIndexX < m_iTileCountX - 1))
	{
		CCharacter::MoveRight(fTime);

		if (m_vMoveDir != m_vStopDir)
		{
			SoundPlay();

			ChangeAnimationState();

			ChangeAnimationRight();
		}
	}
}

void CBaba::MoveUp(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] && !m_bMoving && m_iTileIndexY > 0)
	{
		CCharacter::MoveUp(fTime);

		if (m_vMoveDir != m_vStopDir)
		{
			SoundPlay();

			ChangeAnimationState();

			ChangeAnimationUp();
		}
	}
}

void CBaba::MoveDown(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] && !m_bMoving && (m_iTileIndexY < m_iTileCountY - 1))
	{
		CCharacter::MoveDown(fTime);

		if (m_vMoveDir != m_vStopDir)
		{
			SoundPlay();

			ChangeAnimationState();

			ChangeAnimationDown();
		}
	}
}

void CBaba::MoveLeftOn(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] && !m_bMoving && m_iTileIndexX > 0)
	{
		m_fWaitAcc += fTime;

		if (m_fWaitAcc >= m_fWait)
		{
			m_fWaitAcc -= m_fWait;

			++m_iMoveCount;

			CCharacter::MoveLeftOn(fTime);

			if (m_vMoveDir != m_vStopDir)
			{
				SoundPlay();

				ChangeAnimationState();

				ChangeAnimationLeft();
			}
		}
	}
}

void CBaba::MoveRightOn(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] && !m_bMoving && (m_iTileIndexX < m_iTileCountX - 1))
	{
		m_fWaitAcc += fTime;
	
		if (m_fWaitAcc >= m_fWait)
		{
			m_fWaitAcc -= m_fWait; ++m_iMoveCount;

			CCharacter::MoveRightOn(fTime);

			if (m_vMoveDir != m_vStopDir)
			{
				SoundPlay();

				ChangeAnimationState();

				ChangeAnimationRight();
			}
		}
	}
}

void CBaba::MoveUpOn(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] && !m_bMoving && (m_iTileIndexY > 0))
	{
		m_fWaitAcc += fTime;

		if (m_fWaitAcc >= m_fWait)
		{
			m_fWaitAcc -= m_fWait; ++m_iMoveCount;

			CCharacter::MoveUpOn(fTime);

			if (m_vMoveDir != m_vStopDir)
			{
				SoundPlay();

				ChangeAnimationState();

				ChangeAnimationUp();
			}
		}	
	}
}

void CBaba::MoveDownOn(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] && !m_bMoving && (m_iTileIndexY < m_iTileCountY - 1))
	{
		m_fWaitAcc += fTime;

		if (m_fWaitAcc >= m_fWait)
		{
			m_fWaitAcc -= m_fWait; ++m_iMoveCount;

			CCharacter::MoveDownOn(fTime);

			if (m_vMoveDir != m_vStopDir)
			{
				SoundPlay();

				ChangeAnimationState();

				ChangeAnimationDown();
			}
		}
	}
}

void CBaba::MoveEnd(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU])
	{
		CCharacter::MoveEnd(fTime);
	}
}

void CBaba::ChangeAnimationState()
{
	switch (m_eAnimType)
	{
	case BABA_ANIMATION::NORMAL:
		m_eAnimType = BABA_ANIMATION::OPEN;
		break;
	case BABA_ANIMATION::OPEN:
		m_eAnimType = BABA_ANIMATION::NORMAL2;
		break;
	case BABA_ANIMATION::NORMAL2:
		m_eAnimType = BABA_ANIMATION::CLOSE;
		break;
	case BABA_ANIMATION::CLOSE:
		m_eAnimType = BABA_ANIMATION::NORMAL;
		break;
	}
}

void CBaba::ChangeAnimationLeft()
{
	switch (m_eAnimType)
	{
	case BABA_ANIMATION::NORMAL:
		ChangeAnimation("Baba_Left_Normal");
		break;
	case BABA_ANIMATION::OPEN:
		ChangeAnimation("Baba_Left_Open");
		break;
	case BABA_ANIMATION::NORMAL2:
		ChangeAnimation("Baba_Left_Normal");
		break;
	case BABA_ANIMATION::CLOSE:
		ChangeAnimation("Baba_Left_Close");
		break;
	}
}

void CBaba::ChangeAnimationRight()
{
	switch (m_eAnimType)
	{
	case BABA_ANIMATION::NORMAL:
		ChangeAnimation("Baba_Right_Normal");
		break;
	case BABA_ANIMATION::OPEN:
		ChangeAnimation("Baba_Right_Open");
		break;
	case BABA_ANIMATION::NORMAL2:
		ChangeAnimation("Baba_Right_Normal");
		break;
	case BABA_ANIMATION::CLOSE:
		ChangeAnimation("Baba_Right_Close");
		break;
	}
}

void CBaba::ChangeAnimationUp()
{
	switch (m_eAnimType)
	{
	case BABA_ANIMATION::NORMAL:
		ChangeAnimation("Baba_Up_Normal");
		break;
	case BABA_ANIMATION::OPEN:
		ChangeAnimation("Baba_Up_Open");
		break;
	case BABA_ANIMATION::NORMAL2:
		ChangeAnimation("Baba_Up_Normal");
		break;
	case BABA_ANIMATION::CLOSE:
		ChangeAnimation("Baba_Up_Close");
		break;
	}
}

void CBaba::ChangeAnimationDown()
{
	switch (m_eAnimType)
	{
	case BABA_ANIMATION::NORMAL:
		ChangeAnimation("Baba_Down_Normal");
		break;
	case BABA_ANIMATION::OPEN:
		ChangeAnimation("Baba_Down_Open");
		break;
	case BABA_ANIMATION::NORMAL2:
		ChangeAnimation("Baba_Down_Normal");
		break;
	case BABA_ANIMATION::CLOSE:
		ChangeAnimation("Baba_Down_Close");
		break;
	}
}
