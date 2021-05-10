#include "Connect.h"

#include "../TileMap/Tile.h"
#include "../TileMap/TileMap.h"
#include "State.h"
#include "Name.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CConnect::CConnect()
{
	m_eWordType = WORD_TYPE::CONNECT;
}

CConnect::CConnect(const CConnect& obj) :
	CWord(obj)
{
	m_eWordType = WORD_TYPE::CONNECT;
}

CConnect::~CConnect()
{
}

bool CConnect::Init()
{
	CWord::Init();

	return true;
}

bool CConnect::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CConnect::Start()
{
	CWord::Start();
}

void CConnect::Update(float fTime)
{
	CWord::Update(fTime);
}

void CConnect::PostUpdate(float fTime)
{
	CWord::PostUpdate(fTime);
}

void CConnect::Collision(float fTime)
{
	CWord::Collision(fTime);
}

void CConnect::PrevRender(float fTime)
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

void CConnect::Render(HDC hDC, float fTime)
{
	CWord::Render(hDC, fTime);
}

void CConnect::PostRender(float fTime)
{
	CWord::PostRender(fTime);
}

void CConnect::CheckConnection()
{
	bool bHorizontal = false;
	bool bVertical = false;

	// Horizontal

	CTile* pLeftTile = m_pTileMap->FindTile(m_iTileIndex - 1);

	if (pLeftTile)
	{
		if (pLeftTile != m_pTile && !(pLeftTile->IsEmpty()))
		{
			CName* pName = pLeftTile->FindName();

			if (pName)
			{
				CTile* pRightTile = m_pTileMap->FindTile(m_iTileIndex + 1);

				if (pRightTile)
				{
					if (pRightTile != m_pTile && !(pRightTile->IsEmpty()))
					{
						CState* pState = pRightTile->FindState();
						CName* pName = pRightTile->FindName();

						if (pState || pName)
						{
							bHorizontal = true;
							SAFE_RELEASE(pState);
							SAFE_RELEASE(pName);
						}
					}
				}

				SAFE_RELEASE(pName);
			}
		}
	}

	// Vertical

	CTile* pUpTile = m_pTileMap->FindTile(m_iTileIndex - m_iTileCountX);

	if (pUpTile)
	{
		if (pUpTile != m_pTile && !(pUpTile->IsEmpty()))
		{
			CName* pName = pUpTile->FindName();

			if (pName)
			{
				CTile* pDownTile = m_pTileMap->FindTile(m_iTileIndex + m_iTileCountX);

				if (pDownTile)
				{
					if (pDownTile != m_pTile && !(pDownTile->IsEmpty()))
					{
						CState* pState = pDownTile->FindState();
						CName* pName = pDownTile->FindName();

						if (pState || pName)
						{
							bVertical = true;
							SAFE_RELEASE(pState);
							SAFE_RELEASE(pName);
						}
					}
				}

				SAFE_RELEASE(pName);
			}
		}
	}

	if (!bHorizontal && !bVertical)
		m_bConnected = false;

	else
		m_bConnected = true;
}