#include "State.h"
#include "../TileMap/TileMap.h"
#include "../TileMap/Tile.h"
#include "Name.h"
#include "Connect.h"
#include "../Scene/Scene.h"

CState::CState():
	m_eStateType(STATE_TYPE::END)
{
	m_eWordType = WORD_TYPE::STATE;
	
}

CState::CState(const CState& obj) :
	CWord(obj),
	m_eStateType(STATE_TYPE::END)
{
	m_eWordType = WORD_TYPE::STATE;
}

CState::~CState()
{
}

bool CState::Init()
{
	CWord::Init();

	return true;
}

bool CState::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CState::Start()
{
	CWord::Start();
}

void CState::Update(float fTime)
{
	CWord::Update(fTime);
}

void CState::PostUpdate(float fTime)
{
	CWord::PostUpdate(fTime);
}

void CState::Collision(float fTime)
{
	CWord::Collision(fTime);
}

void CState::PrevRender(float fTime)
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

void CState::Render(HDC hDC, float fTime)
{
	CWord::Render(hDC, fTime);
}

void CState::PostRender(float fTime)
{
	CWord::PostRender(fTime);
}

void CState::CheckConnection()
{
	bool bHorizontal = false;
	bool bVertical = false;

	// Horizontal

	CTile* pLeftTile = m_pTileMap->FindTile(m_iTileIndex - 1);

	if (pLeftTile)
	{
		if (pLeftTile != m_pTile && !(pLeftTile->IsEmpty()))
		{
			CConnect* pConnect = pLeftTile->FindConnect();

			if (pConnect)
			{
				CTile* pLeftLeftTile = m_pTileMap->FindTile(m_iTileIndex -2);

				if (pLeftLeftTile)
				{
					if (pLeftLeftTile != m_pTile && !(pLeftLeftTile->IsEmpty()))
					{
						CName* pName = pLeftLeftTile->FindName();

						if (pName) // Connect가 있다
						{
							bHorizontal = true;
							SAFE_RELEASE(pName);
						}
					}
				}

				SAFE_RELEASE(pConnect);
			}
		}
	}

	// Vertical

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

						if (pName) // Connect가 있다
						{
							bVertical = true;
							SAFE_RELEASE(pName);
						}
					}
				}

				SAFE_RELEASE(pConnect);
			}
		}
	}

	if (!bHorizontal && !bVertical)
		m_bConnected = false;

	else
		m_bConnected = true;
}