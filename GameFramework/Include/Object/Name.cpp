#include "Name.h"

#include "../TileMap/TileMap.h"
#include "../TileMap/Tile.h"
#include "Connect.h"
#include "State.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CName::CName():
	m_eNameType(NAME_TYPE::END)
{			  
	m_eWordType = WORD_TYPE::NAME;

	m_eStateRight = STATE_TYPE::END;
	m_eStateBottom = STATE_TYPE::END;
	m_eNameRight = NAME_TYPE::END;
	m_eNameBottom = NAME_TYPE::END;

	m_eStateRightPrev = STATE_TYPE::END;
	m_eStateBottomPrev = STATE_TYPE::END;
	m_eNameRightPrev = NAME_TYPE::END;
	m_eNameBottomPrev = NAME_TYPE::END;
}

CName::CName(const CName& obj) :
	CWord(obj),
	m_eNameType(NAME_TYPE::END)
{
	m_eWordType = WORD_TYPE::NAME;
	m_eStateRight = STATE_TYPE::END;
	m_eStateBottom = STATE_TYPE::END;
	m_eNameRight = NAME_TYPE::END;
	m_eNameBottom = NAME_TYPE::END;

	m_eStateRightPrev = STATE_TYPE::END;
	m_eStateBottomPrev = STATE_TYPE::END;
	m_eNameRightPrev = NAME_TYPE::END;
	m_eNameBottomPrev = NAME_TYPE::END;
}

CName::~CName()
{
}

bool CName::Init()
{
	CWord::Init();

	return true;
}

bool CName::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CName::Start()
{
	CWord::Start();
}

void CName::Update(float fTime) // �̵�
{
	CWord::Update(fTime);
}

void CName::PostUpdate(float fTime) // ��� ������Ʈ�� �̵� �� ���¸� ����
{
	CWord::PostUpdate(fTime);
}

void CName::Collision(float fTime) 
{
	CWord::Collision(fTime);
}

void CName::PrevRender(float fTime)
{
	CWord::PrevRender(fTime);

	if (m_bInitialFrame)
	{
		CheckConnection(); 
		m_bInitialFrame = false;
	}

	else
	{
		if (!m_bMoving && m_pScene->GetMoved())
			CheckConnection();
	}
}

void CName::Render(HDC hDC, float fTime)
{
	CWord::Render(hDC, fTime);
}

void CName::PostRender(float fTime)
{
	CWord::PostRender(fTime);
}

void CName::CheckConnection()
{
	// ���� ���� ����
	m_eStateRightPrev = m_eStateRight;
	m_eStateBottomPrev = m_eStateBottom;
	m_eNameRightPrev = m_eNameRight;
	m_eNameBottomPrev = m_eNameBottom;

	// ���� �ʱ�ȭ
	m_eStateRight = STATE_TYPE::END;
	m_eStateBottom = STATE_TYPE::END;
	m_eNameRight = NAME_TYPE::END;
	m_eNameBottom = NAME_TYPE::END;

	bool bHorizontalRight = false;
	bool bHorizontalLeft= false;
	bool bVerticalDown = false;
	bool bVerticalUp = false;

	bool bHorizontalChange = false;
	bool bVerticalChange = false;

	// Horizontal - Right 

	CTile* pRightTile = m_pTileMap->FindTile(m_iTileIndex + 1);

	if (pRightTile)
	{
		if (pRightTile != m_pTile && !(pRightTile->IsEmpty()))
		// �浹 Ÿ���� �� Ÿ���� �ƴϰ� �浹 Ÿ�Ͽ� �������� �־��� ��� �浹�� �Ǵ��Ѵ�.
		{
			CConnect* pConnect = pRightTile->FindConnect();

			if (pConnect) // Connect�� �ִ�
			{
				CTile* pRightRightTile = m_pTileMap->FindTile(m_iTileIndex + 2);

				if (pRightRightTile)
				{
					CState* pState = pRightRightTile->FindState();

					if (pState)
					{
						m_eStateRight = pState->GetStateType();

						if (m_eStateRight != m_eStateRightPrev)
						{
							bHorizontalChange = true;
						}

						bHorizontalRight = true;
						SAFE_RELEASE(pState);
					}

					else
					{
						CName* pName = pRightRightTile->FindName();

						if (pName)
						{
							m_eNameRight = pName->GetNameType();

							if (m_eNameRight != m_eNameRightPrev)
							{
								bHorizontalChange = true;
							}

							bHorizontalRight = true;
							SAFE_RELEASE(pName);
						}
					}
				}

				SAFE_RELEASE(pConnect);
			}

		}
	}


	// Horizontal - Left (������� �˻�)

	CTile* pLeftTile = m_pTileMap->FindTile(m_iTileIndex - 1);

	if (pLeftTile)
	{
		if (pLeftTile != m_pTile && !(pLeftTile->IsEmpty()))
		{
			CConnect* pConnect = pLeftTile->FindConnect();

			if (pConnect)
			{
				CTile* pLeftLeftTile = m_pTileMap->FindTile(m_iTileIndex - 2);

				if (pLeftLeftTile)
				{
					if (pLeftLeftTile != m_pTile && !(pLeftLeftTile->IsEmpty()))
					{
						CName* pName = pLeftLeftTile->FindName();

						if (pName)
						{
							bHorizontalLeft = true;
							SAFE_RELEASE(pName);
						}
					}
				}

				SAFE_RELEASE(pConnect);
			}
		}
	}

	// Vertical - Down

	CTile* pDownTile = m_pTileMap->FindTile(m_iTileIndex + m_iTileCountX);

	if (pDownTile)
	{
		if (pDownTile != m_pTile && !(pDownTile->IsEmpty()))
			// �浹 Ÿ���� �� Ÿ���� �ƴϰ� �浹 Ÿ�Ͽ� �������� �־��� ��� �浹�� �Ǵ��Ѵ�.
		{
			CConnect* pConnect = pDownTile->FindConnect();

			if (pConnect) // ������ �ִٸ�
			{
				CTile* pDownDownTile = m_pTileMap->FindTile(m_iTileIndex + m_iTileCountX * 2);

				if (pDownDownTile)
				{
					CState* pState = pDownDownTile->FindState();

					if (pState) // ������Ʈ�� �ִٸ�
					{
						m_eStateBottom = pState->GetStateType();

						if (m_eStateBottom != m_eStateBottomPrev)
						{
							bVerticalChange = true;
						}

						SAFE_RELEASE(pState);
						bVerticalDown = true;
					}

					else
					{
						CName* pName = pDownDownTile->FindName();

						if (pName)
						{
							m_eNameBottom = pName->GetNameType();

							if (m_eNameBottom != m_eNameBottomPrev)
							{
								bVerticalChange = true;
							}

							SAFE_RELEASE(pName);
							bVerticalDown = true;
						}
					}
				}

				SAFE_RELEASE(pConnect);
			}
		}
	}

	// Vertical - Up (������� �˻�)

	CTile* pUpTile = m_pTileMap->FindTile(m_iTileIndex - m_iTileCountX);

	if (pUpTile)
	{
		if (pUpTile != m_pTile && !(pUpTile->IsEmpty()))
		{
			CConnect* pConnect = pUpTile->FindConnect();

			if (pConnect)
			{
				CTile* pUpUpTile = m_pTileMap->FindTile(m_iTileIndex - m_iTileCountX * 2);

				if (pUpUpTile)
				{
					if (pUpUpTile != m_pTile && !(pUpUpTile->IsEmpty()))
					{
						CName* pName = pUpUpTile->FindName();

						if (pName) // Connect�� �ִ�
						{
							bVerticalUp = true;
							SAFE_RELEASE(pName);
						}
					}
				}

				SAFE_RELEASE(pConnect);
			}
		}
	}

	if (!m_bInitialFrame) // �Ҹ��� right �� bottom ��
	{
		if (!bHorizontalRight)
			m_bSoundHR = false;

		if (!bVerticalDown)
			m_bSoundVB = false;

		if (bHorizontalChange)
		{
			SoundPlay();
			m_bSoundHR = true;
		}

		else if (bVerticalChange)
		{
			SoundPlay();
			m_bSoundVB = true;
		}

		else
		{
			if (!m_bConnected)
			{
				if (bHorizontalRight && !m_bSoundHR)
				{
					SoundPlay();
					m_bSoundHR = true;
				}

				else if (bVerticalDown && !m_bSoundVB)
				{
					SoundPlay();
					m_bSoundVB = true;
				}
			}
		}
	}
	

	if (!bHorizontalLeft && !bHorizontalRight && !bVerticalDown && !bVerticalUp)
	{
		m_bConnected = false;
	}
		
	else
		m_bConnected = true;
}

void CName::SoundPlay()
{
	int iNumber = rand() % 5;

	switch (iNumber)
	{
	case 0:
		m_pScene->GetSceneResource()->SoundPlay("Connect_0");
		break;
	case 1:
		m_pScene->GetSceneResource()->SoundPlay("Connect_1");
		break;
	case 2:
		m_pScene->GetSceneResource()->SoundPlay("Connect_2");
		break;
	case 3:
		m_pScene->GetSceneResource()->SoundPlay("Connect_3");
		break;
	case 4:
		m_pScene->GetSceneResource()->SoundPlay("Connect_4");
		break;
	}
}
