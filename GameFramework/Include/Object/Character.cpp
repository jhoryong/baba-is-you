#include "Character.h"

#include "../Input.h"
#include "../TileMap/Tile.h"
#include "../Scene/Scene.h"
#include "../TileMap/TileMap.h"
#include "Name.h"
#include "State.h"
#include "../GameManager.h"
#include "Baba.h"
#include "Rock.h"
#include "Flag.h"
#include "Wall.h"
#include "Water.h"
#include "Skull.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../GameManager.h"
#include "../Scene/SceneStage.h"


CCharacter::CCharacter():
	//m_pName(nullptr),
	m_eCharacterType(CHARACTER_TYPE::END),
	m_fWait(0.05f),
	m_fWaitAcc(0.f)
{
	m_vMoveDir = Vector2(1.f, 0.f);
	m_eBlockObjType = BLOCKOBJ_TYPE::CHARACTER;
	m_iZOrder = 1;
}

CCharacter::CCharacter(const CCharacter& obj) :
	CBlockObj(obj), 
	//m_pName(nullptr),
	m_eCharacterType(CHARACTER_TYPE::END),
	m_fWait(0.05f),
	m_fWaitAcc(0.f)
{
	m_vMoveDir = obj.m_vMoveDir;
	m_eBlockObjType = BLOCKOBJ_TYPE::CHARACTER;
	m_iZOrder = 1;
}

CCharacter::~CCharacter()
{
	SAFE_RELEASE_VECLIST(m_vecName);
}

bool CCharacter::Init()
{
	CBlockObj::Init();
	return true;
}

bool CCharacter::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CCharacter::Start()
{
	CBlockObj::Start();

	vector<CName*> vecName = m_pScene->FindName(m_eCharacterType);

	//if (vecName.size() > 0)
	m_vecName = vecName;
}

void CCharacter::Update(float fTime)
{
	CBlockObj::Update(fTime);
}

void CCharacter::PostUpdate(float fTime)
{
	CBlockObj::PostUpdate(fTime);

	if (m_pScene->GetMoved())
		m_fWaitAcc = 0.f;
}

void CCharacter::Collision(float fTime) // Word 들의 상태가 갱신된 후 캐릭터로 전달.
{
	CBlockObj::Collision(fTime);
}

void CCharacter::PrevRender(float fTime)
{
	CBlockObj::PrevRender(fTime);
}

void CCharacter::Render(HDC hDC, float fTime)
{
	CBlockObj::Render(hDC, fTime);
}

void CCharacter::PostRender(float fTime)
{
	CBlockObj::PostRender(fTime);

	if (m_bInitialFrame)
	{
		m_bInitialFrame = false;

		if (!m_vecName.empty())
		{
			ClearState();

			size_t iSize = m_vecName.size();
			
			for (size_t i = 0; i < iSize; ++i)
			{
				SetState(m_vecName[i]->GetRightState());
				SetState(m_vecName[i]->GetBottomState());

				m_eNameRight = m_vecName[i]->GetNameRight();
				m_eNameBottom = m_vecName[i]->GetNameBottom();
			}
		/*	SetState(m_pName->GetRightState());
			SetState(m_pName->GetBottomState());*/

			// 아무 Name 도 없다면 NAME::END 를 반환할 것이다.
			/*m_eNameRight = m_pName->GetNameRight();
			m_eNameBottom = m_pName->GetNameBottom();*/
		}

		CheckNoneState();

		CheckNameConnection();
	}

	else
	{
		if (!m_bMoving && m_pScene->GetMoved())
		{
			//MessageBox(WINDOWHANDLE, TEXT("상태체크"), TEXT("상태체크"), 0);

			if (!m_vecName.empty())
			{
				ClearState();

				//SetState(m_pName->GetRightState());
				//SetState(m_pName->GetBottomState());

				//// 아무 Name 도 없다면 NAME::END 를 반환할 것이다.
				//m_eNameRight = m_pName->GetNameRight();
				//m_eNameBottom = m_pName->GetNameBottom();

				size_t iSize = m_vecName.size();

				for (size_t i = 0; i < iSize; ++i)
				{
					SetState(m_vecName[i]->GetRightState());
					SetState(m_vecName[i]->GetBottomState());

					m_eNameRight = m_vecName[i]->GetNameRight();
					m_eNameBottom = m_vecName[i]->GetNameBottom();
				}
			}

			CheckNoneState();

			CheckWinState(fTime);

			CheckNameConnection();
		}
	}

	if (m_bSink || m_bDefeat || m_bMelt)
	{
		m_pScene->SetReRegisterKeyChar(m_eCharacterType); 
	}
}

void CCharacter::ClearState()
{
	memset(m_bState, false, sizeof(bool) * (int)STATE_TYPE::END);
}

void CCharacter::CheckNoneState()
{
	bool bState = false;

	for (int i = 0; i < (int)STATE_TYPE::END; ++i)
	{
		if (m_bState[i] == true)
			bState = true;
	}

	if (bState == false) // 모든 상태가 false 라면
	{
		if (m_eCharacterType != CHARACTER_TYPE::BABA  // 바바찡은 무조건 z-order 2
			&& !m_bMoving) // 끝까지 이동한 후 상태를 부여한다.
		{
			m_bNone = true; //  None 상태이다.
			m_iZOrder = 0; // ZOrder 도 0 이 된다.
		}
	}

	else // 상태가 하나라도 있으면
	{
		m_bNone = false;
		m_iZOrder = 1;
	}
}

void CCharacter::CheckWinState(float fTime)
{
	if (m_bState[(int)STATE_TYPE::YOU] && m_bState[(int)STATE_TYPE::WIN])
	{
		((CSceneStage*)m_pScene)->SetWin(true);
	}
}

void CCharacter::CheckNameConnection()
{
	// Name
	if (m_eNameRight != NAME_TYPE::END)
	{
		// 오브젝트 생성
		CBlockObj* pBlockObj = nullptr;

		switch (m_eNameRight)
		{
		case NAME_TYPE::BABA:
		{
			pBlockObj = m_pScene->CreateCloneBlockObj<CBaba>("Baba");
			pBlockObj->SetTileIndex(m_iTileIndex);
			break;
		}
		case NAME_TYPE::ROCK:
		{
			pBlockObj = m_pScene->CreateCloneBlockObj<CRock>("Rock");
			pBlockObj->SetTileIndex(m_iTileIndex);
			break;
		}
		case NAME_TYPE::FLAG:
		{
			pBlockObj = m_pScene->CreateCloneBlockObj<CFlag>("Flag");
			pBlockObj->SetTileIndex(m_iTileIndex);
			break;
		}
		case NAME_TYPE::WALL:
		{
			pBlockObj = m_pScene->CreateCloneBlockObj<CWall>("Wall");
			pBlockObj->SetTileIndex(m_iTileIndex);
			break;
		}
		case NAME_TYPE::WATER:
		{
			pBlockObj = m_pScene->CreateCloneBlockObj<CWater>("Water");
			pBlockObj->SetTileIndex(m_iTileIndex);
		}
		case NAME_TYPE::SKULL:
		{
			pBlockObj = m_pScene->CreateCloneBlockObj<CSkull>("Skull");
			pBlockObj->SetTileIndex(m_iTileIndex);
		}
		}

		//타일 오브젝트 리스트 갱신
		if (m_pTile)
		{
			m_pTile->DeleteBlockObj(m_strName);
			m_pTile->AddBlockObj(pBlockObj);

			// 오브젝트 삭제
			Destroy();
		}

		SAFE_RELEASE(pBlockObj);

	}

	if (m_eNameBottom != NAME_TYPE::END)
	{
		// 오브젝트 생성
		CBlockObj* pBlockObj = nullptr;

		switch (m_eNameBottom)
		{
		case NAME_TYPE::BABA:
		{
			pBlockObj = m_pScene->CreateCloneBlockObj<CBaba>("Baba");
			pBlockObj->SetTileIndex(m_iTileIndex);
			break;
		}
		case NAME_TYPE::ROCK:
		{
			pBlockObj = m_pScene->CreateCloneBlockObj<CRock>("Rock");
			pBlockObj->SetTileIndex(m_iTileIndex);
			break;
		}
		case NAME_TYPE::FLAG:
		{
			pBlockObj = m_pScene->CreateCloneBlockObj<CFlag>("Flag");
			pBlockObj->SetTileIndex(m_iTileIndex);
			break;
		}
		case NAME_TYPE::WALL:
		{
			pBlockObj = m_pScene->CreateCloneBlockObj<CWall>("Wall");
			pBlockObj->SetTileIndex(m_iTileIndex);
			break;
		}
		case NAME_TYPE::WATER:
		{
			pBlockObj = m_pScene->CreateCloneBlockObj<CWater>("Water");
			pBlockObj->SetTileIndex(m_iTileIndex);
		}
		case NAME_TYPE::SKULL:
		{
			pBlockObj = m_pScene->CreateCloneBlockObj<CSkull>("Skull");
			pBlockObj->SetTileIndex(m_iTileIndex);
		}
		}

		// 타일 오브젝트 리스트 갱신
		if (m_pTile)
		{
			m_pTile->DeleteBlockObj(m_strName);
			m_pTile->AddBlockObj(pBlockObj);

			// 오브젝트 삭제
			Destroy();
		}

		SAFE_RELEASE(pBlockObj);

	}
}

void CCharacter::SoundPlay()
{	
	if (m_pScene->GetMoveSoundPlay())
		return;

	CTile* pTile = m_pTileMap->FindTile(m_vRelPos + m_vMoveDir * m_vSize);

	// 5개
	if (pTile->IsEmpty() || m_eCharacterType == CHARACTER_TYPE::SELECTOR)
	{
		int iNumber = rand() % 5;

		switch (iNumber)
		{
		case 0:
			m_pScene->GetSceneResource()->SoundPlay("Walk_0");
			break;
		case 1:
			m_pScene->GetSceneResource()->SoundPlay("Walk_1");
			break;
		case 2:
			m_pScene->GetSceneResource()->SoundPlay("Walk_2");
			break;
		case 3:
			m_pScene->GetSceneResource()->SoundPlay("Walk_3");
			break;
		case 4:
			m_pScene->GetSceneResource()->SoundPlay("Walk_4");
			break;
		}
	}
	
	else
	{
		int iNumber = rand() % 4;

		switch (iNumber)
		{
		case 0:
			m_pScene->GetSceneResource()->SoundPlay("Push_0");
			break;
		case 1:
			m_pScene->GetSceneResource()->SoundPlay("Push_1");
			break;
		case 2:
			m_pScene->GetSceneResource()->SoundPlay("Push_2");
			break;
		case 3:
			m_pScene->GetSceneResource()->SoundPlay("Push_3");
			break;
		}
	}

	m_pScene->SetMoveSoundPlay(true);
}

void CCharacter::RegisterKey()
{
}

void CCharacter::ChangeObject(NAME_TYPE eNameType)
{
	
}


void CCharacter::MoveLeft(float fTime)
{
	CBlockObj::MoveLeft(fTime);

	m_bMoving = true;
	m_vMoveDir = Vector2(-1.f, 0.f);
}

void CCharacter::MoveRight(float fTime)
{
	CBlockObj::MoveRight(fTime);

	m_bMoving = true;
	m_vMoveDir = Vector2(1.f, 0.f);
}

void CCharacter::MoveUp(float fTime)
{
	CBlockObj::MoveUp(fTime);

	m_bMoving = true;
	m_vMoveDir = Vector2(0.f, -1.f);
}

void CCharacter::MoveDown(float fTime)
{
	CBlockObj::MoveDown(fTime);

	m_bMoving = true;
	m_vMoveDir = Vector2(0.f, 1.f);
}

void CCharacter::MoveLeftOn(float fTime)
{
	m_bMoving = true;
	m_vMoveDir = Vector2(-1.f, 0.f);
}

void CCharacter::MoveRightOn(float fTime)
{
	m_bMoving = true;
	m_vMoveDir = Vector2(1.f, 0.f);
}

void CCharacter::MoveUpOn(float fTime)
{
	m_bMoving = true;
	m_vMoveDir = Vector2(0.f, -1.f);
}

void CCharacter::MoveDownOn(float fTime)
{
	m_bMoving = true;
	m_vMoveDir = Vector2(0.f, 1.f);
}

void CCharacter::MoveEnd(float fTime)
{
	m_fWaitAcc = 0.f;
}