#include "BlockObj.h"

#include "../Scene/SceneManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneStage.h"
#include "../TileMap/TileMap.h"
#include "../TileMap/Tile.h"
#include "../GameManager.h"
#include "../Collider/ColliderRect.h"
#include "Word.h"
#include "../Scene/SceneMainMap.h"
#include "../Scene/SceneStage.h"
#include "Water.h"
#include "Skull.h"
#include "Lava.h"

CBlockObj::CBlockObj() :
	m_pTileMap(nullptr),
	m_iTileCountX(0),
	m_iTileCountY(0),
	m_iTileIndex(0),
	m_iTileIndexX(0),
	m_iTileIndexY(0),
	m_pTile(nullptr),
	m_bState{}, // ���� �ʱ�ȭ
	m_iZOrder(0)
{
	m_vPivot = Vector2(0.5f, 0.5f); // ��� ���� Ÿ���� �߾����� �������� ����� ���̴�.
	m_bMoving = false;
	m_fSpeed = 200.f;
	m_fMoveDist = 24.f;
	m_vSize = Vector2(24.f, 24.f);
}

CBlockObj::CBlockObj(const CBlockObj& obj) :
	CObj(obj),
	m_iTileCountX(0),
	m_iTileCountY(0),
	m_iTileIndex(0),
	m_iTileIndexX(0),
	m_iTileIndexY(0),
	m_pTile(nullptr),
	m_bState{},
	m_iZOrder(0)
{
	m_pTileMap = obj.m_pTileMap;
	m_vTileSize = obj.m_vTileSize;
	m_iTileCountX = obj.m_iTileCountX;
	m_iTileCountY = obj.m_iTileCountY;
	m_vPivot = Vector2(0.5f, 0.5f);
	m_bMoving = false;
	m_fSpeed = 200.f;
	m_fMoveDist = 24.f;
	m_vSize = Vector2(24.f, 24.f);
	//m_iPrevTileIndex = obj.m_iPrevTileIndex;
	//m_iTileIndex = obj.m_iTileIndex;

	m_vRelPos = obj.m_vRelPos;
}

CBlockObj::~CBlockObj()
{
}


bool CBlockObj::Init()
{
	SetSize(24.f, 24.f);

	CTileMap* pTileMap = m_pScene->FindTileMap(RESOLUTION / 2.f);

	if (pTileMap)
	{
		m_pTileMap = pTileMap;
		m_vTileSize = pTileMap->GetTileSize();
		m_iTileCountX = pTileMap->GetCountX();
		m_iTileCountY = pTileMap->GetCountY();
	}

	CColliderRect* pBody = AddCollider<CColliderRect>("Body");

	pBody->SetRectInfo(-12.f, -12.f, 12.f, 12.f);

	return true;
}

bool CBlockObj::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CBlockObj::Start()
{
	CObj::Start();

	//if (m_bUndo)
	//{
	//	if (m_vPos != m_vBackPos)
	//	{
	//		m_bMoving = true;
	//		m_vMoveDir = m_vBackPos - m_vPos;
	//		m_vMoveDir.Normalize();
	//	}

	//	
	//}

	CTile* pTile = m_pScene->FindTile(m_vPos, m_vRelPos);

	if (pTile)
	{
		m_pTile = pTile;
		m_vTilePos = pTile->GetTilePos();
		m_iTileIndex = pTile->GetTileIndex();
		m_iTileIndexX = pTile->GetIndexX();
		m_iTileIndexY = pTile->GetIndexY();
	}
}

void CBlockObj::Update(float fTime)
{
	//m_vSize = Vector2(24.f, 24.f);

	CObj::Update(fTime);

	// �̵� �� �̵��� ������ Ÿ�� ���� ������Ʈ�� �̵��� �ο��Ѵ�.
	if (m_bMoving && !m_bMoved /*&& m_bMoveStart*/) // �̵����϶���, Ÿ�� �̵��� �Ͼ�� ��������
	{
		CheckCollision(fTime);
		m_bMoveStart = false;
	}
}

void CBlockObj::PostUpdate(float fTime)
{
	CObj::PostUpdate(fTime);

	// ���� Ÿ�� ��ġ�� �����Ѵ�. !! ���� ������ ���� !!
	m_pPrevTile = m_pTile;

	// �����δ�.
	if (
		// ���� �÷��̾�ų� PUSH ������ ���̰ų�
		(m_bState[(int)STATE_TYPE::YOU] || m_bState[(int)STATE_TYPE::PUSH])
			&& m_bMoving // �̵����϶���
			&& (m_vMoveDir != m_vStopDir) // �����̴� ������ Stop block �� �ƴ� ����
		)
	{
		m_fMoveDistAcc += m_fSpeed * fTime; // �Ÿ�

		m_vPos += m_vMoveDir * m_fSpeed * fTime;

		if (m_fMoveDistAcc >= m_fMoveDist) // �Ÿ��� �� ���� ���
		{
			// �ʰ��� �Ÿ��� �ִٸ� ���ش�.
			m_fMoveDistAcc -= m_fMoveDist;

			m_vPos -= m_vMoveDir * m_fMoveDistAcc;

			m_fMoveDistAcc = 0.f; // �Ÿ� �ʱ�ȭ

			m_bMoving = false;
			//if (!m_bMoving)
				//MessageBox(WINDOWHANDLE, TEXT("Moving Off"), TEXT("Moving Off"), 0);
			//TCHAR speed[50] = {};
			//_sntprintf(speed, 50, TEXT("%0.2f"), m_fSpeed);
			//MessageBox(WINDOWHANDLE, speed, speed, 0);
			m_pScene->SetMoved(true);
		}

		if (!m_pTile)
			m_vPos -= m_vMoveDir * m_fSpeed * fTime;
	}

	// Ÿ�ϸ��� ����ٸ� �������ش�.
	Vector2 vMapStart = m_pTileMap->GetStartPos();
	Vector2 vTileStart = vMapStart + (m_vTileSize * m_vPivot);
	Vector2 vMapRB = RESOLUTION / 2.f + m_pTileMap->GetMapSize() / 2.f;
	Vector2 vTileEnd = vMapRB - (m_vTileSize * m_vPivot);

	m_vPos.x = m_vPos.x < vTileStart.x ? vTileStart.x : m_vPos.x;
	m_vPos.y = m_vPos.y < vTileStart.y ? vTileStart.y : m_vPos.y;
	m_vPos.x = m_vPos.x > vTileEnd.x ? vTileEnd.x : m_vPos.x;
	m_vPos.y = m_vPos.y > vTileEnd.y ? vTileEnd.y : m_vPos.y;

	// Ÿ�ϸʻ��� ��� ��ġ�� ����
	m_vRelPos = m_vPos - vMapStart;

	// ���� Ÿ�� ���� : �߾����� �������� ������ ���� ���� Ÿ���� �����ش�.
	CTile* pTile = m_pScene->FindTile(m_vPos, m_vRelPos);

	if (pTile)
	{
		m_iPrevTileIndex = m_iTileIndex;
		m_pTile = pTile;
		m_vTilePos = pTile->GetTilePos();
		m_iTileIndex = pTile->GetTileIndex();
		m_iTileIndexX = pTile->GetIndexX();
		m_iTileIndexY = pTile->GetIndexY();
	}
	
	// �̵��� ������ ��� ��ġ�� Ÿ�Ͽ� ��Ȯ�� �����ش�.
	if (!m_bMoving)
	{
		m_vPos = m_vTilePos + (m_vTileSize * m_vPivot);
		m_bMoved = false;
		//m_pScene->SetMoved(false);

		m_pScene->SetMoveSoundPlay(false);

		// ���࿡ �׵θ� Ÿ���̶�� ���ʷ� ������ �� Stop Dir �ο��Ѵ�.
		if (m_iTileIndexX <= 0
			|| m_iTileIndexY <= 0
			|| m_iTileIndexX >= m_iTileCountX - 1
			|| m_iTileIndexY >= m_iTileCountY - 1)
		{
			if (!m_bBoundEnter)
			{
				m_bBoundEnter = true;
				m_vStopDir = m_vMoveDir;
			}
		}

		else
			m_bBoundEnter = false;
	}
}

void CBlockObj::Collision(float fTime)
{
	//CObj::Collision(fTime);
	if (m_pScene->GetMoved() && m_bUndo)
		DisableUndo();

	if (m_pPrevTile)
	{
		// ���� Ÿ�ϰ� ���� Ÿ���� �ٸ� ��� �߾����� �ٸ� Ÿ�Ͽ� �ִٴ� ���̴�. -> �̵��ߴ�.
		if (m_pPrevTile != m_pTile)
		{
			// ���� Ÿ�Ͽ��� �ڽ��� �����Ѵ�.
			m_pPrevTile->DeleteBlockObj(m_strName);
			m_bMoved = true;
		}
	}

	// �����϶����� ������Ʈ�� �ִ� ��� Ÿ���� ����Ʈ�� �����Ѵ�.
	/*if (m_pScene->GetMoved())
	{
		m_pTile->ClearList();
		m_pTile->AddBlockObj(this);
	}*/

	// ���� Ÿ�Ͽ� �ڽ��� ���ٸ� ó�� ������ ����. 
	if (!m_pTile->FindBlockObj(m_strName))
		m_pTile->AddBlockObj(this); // �ڽ��� Ÿ�Ͽ� �߰��Ѵ�.

	else
		Release();

}

void CBlockObj::PrevRender(float fTime)
{
	CObj::PrevRender(fTime);
}

void CBlockObj::Render(HDC hDC, float fTime)
{
	CObj::Render(hDC, fTime);
}

void CBlockObj::PostRender(float fTime)
{
	CObj::PostRender(fTime);

	if (m_bSink || m_bDefeat || m_bMelt)
	{
		DestroyObject();
	}
}

void CBlockObj::Move(Vector2 vDir)
{
	m_bMoving = true;
	m_vMoveDir = vDir;
}

void CBlockObj::CheckCollision(float fTime)
{
	CTile* pCollideTile = nullptr;
	Vector2 vColTile = m_vRelPos;

	vColTile += m_vSize * m_vMoveDir;
	pCollideTile = m_pScene->FindTile(m_vPos, vColTile);
	
	if (pCollideTile)
	{
		if (pCollideTile != m_pTile && !(pCollideTile->IsEmpty())) 
		// �浹 Ÿ���� �� Ÿ���� �ƴϰ� �浹 Ÿ�Ͽ� �������� �־��� ��� �浹�� �Ǵ��Ѵ�.
		{
			list<CBlockObj*> list = pCollideTile->GetBlockList();

			auto iter = list.begin();
			auto iterEnd = list.end();

			for (; iter != iterEnd; ++iter)
			{
				// STOP Ÿ���� ��� ����ġ�� �з�����.
				if ((*iter)->m_bState[(int)STATE_TYPE::STOP])
				{
					m_vStopDir = m_vMoveDir;
					m_bMoving = false;
					//MessageBox(WINDOWHANDLE, TEXT("Stop Tile"), TEXT("Stop Tile"), 0);
					//m_bPushedBack = true;
				}

				// PUSH Ÿ���� ��� (*iter) �� ���ĳ���
				else if ((*iter)->m_bState[(int)STATE_TYPE::PUSH])
				{
					if ((*iter)->GetStopDir() == m_vMoveDir)
					{
						m_bMoving = false;
						m_vStopDir = m_vMoveDir;
					}

					else
					{
						// �̵����� �� ���� �ο�
						(*iter)->Move(m_vMoveDir);
						//(*iter)->SetStopDir(Vector2::Zero);
						m_vStopDir = Vector2::Zero; // �浹 Ÿ���� STOP �� �ƴϾ��� ��� �ʱ�ȭ
					}
				}

				else if ((*iter)->m_bNone)
				{
					m_vStopDir = Vector2::Zero;
					//MessageBox(WINDOWHANDLE, TEXT("Stopdir init"), TEXT("Stopdir init"), 0);
				}

				else if (m_bState[(int)STATE_TYPE::YOU] && (*iter)->m_bState[(int)STATE_TYPE::WIN])
				{
					((CSceneStage*)m_pScene)->SetWin(true);
				}
				
				else if ((*iter)->m_bState[(int)STATE_TYPE::SINK])
				{
					m_bSink = true;
					(*iter)->SetSink();
					m_pScene->SetSink();
					((CWater*)(*iter))->PlaySinkSound();

					if (m_bState[(int)STATE_TYPE::YOU])
						((CSceneStage*)m_pScene)->SetStuck(true);
				}

				else if (m_bState[(int)STATE_TYPE::YOU] && (*iter)->m_bState[(int)STATE_TYPE::DEFEAT])
				{
					if (!m_pScene->GetPlayDefeatSound())
					{
						((CSkull*)(*iter))->PlayDefeatSound();
						m_pScene->SetPlayDefeatSound(true);
					}

					m_bDefeat = true;
					m_pScene->SetDefeat();

					if (!((CSceneStage*)m_pScene)->FindYou())
					{
						((CSceneStage*)m_pScene)->SetStuck(true);
					}
				}

				else if (m_bState[(int)STATE_TYPE::YOU] && m_bState[(int)STATE_TYPE::MELT]&& (*iter)->m_bState[(int)STATE_TYPE::HOT])
				{
					m_bMelt = true;
					m_pScene->SetMelt();
					((CLava*)(*iter))->PlayMeltSound();
					((CSceneStage*)m_pScene)->SetStuck(true);
				}
			}
		}

		else // Ÿ�Ͽ� �ƹ��� ������ ���
		{
			m_vStopDir = Vector2::Zero;
		}
	}

	else // Ÿ���� ������ ��� (���� �ٴٶ��� ���)
	{
		m_vStopDir = m_vMoveDir;
		m_bMoving = false;
	}
}

void CBlockObj::DestroyObject()
{
	//Ÿ�� ������Ʈ ����Ʈ ����
	if (m_pTile)
	{
		m_pTile->DeleteBlockObj(m_strName);
		Destroy();
	}
}


void CBlockObj::SetTileIndex(int x, int y)
{
	Vector2 vPos = Vector2(m_vTileSize.x * (float)x, m_vTileSize.y * (float)y);

	vPos += m_vSize / 2.f;

	SetRelPos(vPos);
}

void CBlockObj::SetTileIndex(int iIndex)
{
	int iIndexX = iIndex % m_iTileCountX;
	int iIndexY = iIndex / m_iTileCountX;

	Vector2 vPos = Vector2(m_vTileSize.x * (float)iIndexX, m_vTileSize.y * (float)iIndexY);

	vPos += m_vSize / 2.f;
	 
	SetRelPos(vPos);
}

void CBlockObj::SetRelPos(const Vector2& vRelPos)
{
	m_vRelPos = vRelPos;
	Vector2 vStartPos = m_pTileMap->GetStartPos();
	m_vPos = m_vRelPos + vStartPos;
}

void CBlockObj::SetRelPos(float x, float y)
{
	m_vRelPos = Vector2(x, y);
	Vector2 vStartPos = m_pTileMap->GetStartPos();
	m_vPos = m_vRelPos + vStartPos;
}

void CBlockObj::MoveLeft(float fTime)
{
}

void CBlockObj::MoveRight(float fTime)
{
}

void CBlockObj::MoveUp(float fTime)
{
}

void CBlockObj::MoveDown(float fTime)
{
}

void CBlockObj::MoveLeftOn(float fTime)
{
}

void CBlockObj::MoveRightOn(float fTime)
{
}

void CBlockObj::MoveUpOn(float fTime)
{
}

void CBlockObj::MoveDownOn(float fTime)
{
}



