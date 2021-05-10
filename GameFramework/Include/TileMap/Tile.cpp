#include "Tile.h"

#include "../Resource/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/Camera.h"
#include "../GameManager.h"
#include "TileMap.h"
#include "../Object/BlockObj.h"
#include "../Object/Word.h"
#include "../Object/Character.h"

CTile::CTile()	:
	m_eType(TILE_TYPE::NORMAL),
	m_bTexture(false),
	m_pTexture(nullptr),
	m_pScene(nullptr),
	m_iIndex(0),
	m_iIndexX(0),
	m_iIndexY(0)
{
}

CTile::~CTile()
{
	SAFE_RELEASE_VECLIST(m_listBlockObj);
	SAFE_RELEASE(m_pTexture);
}

void CTile::AddBlockObj(CBlockObj* pBlockObj)
{
	m_listBlockObj.push_back(pBlockObj);

	pBlockObj->AddRef();
}

CBlockObj* CTile::FindBlockObj(const string& strName)
{
	auto iter = m_listBlockObj.begin();
	auto iterEnd = m_listBlockObj.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == strName)
		{
			(*iter)->AddRef();
			return (*iter);
		}
	}

	return nullptr;
}

CName* CTile::FindName(const string& strName)
{
	auto iter = m_listBlockObj.begin();
	auto iterEnd = m_listBlockObj.end();

	for (; iter != iterEnd; ++iter)
	{
		//if ((*iter)->)

	}

	return nullptr;
}

CConnect* CTile::FindConnect()
{
	auto iter = m_listBlockObj.begin();
	auto iterEnd = m_listBlockObj.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetBlockObjType() == BLOCKOBJ_TYPE::WORD)
		{
			if (((CWord*)(*iter))->GetWordType() == WORD_TYPE::CONNECT)
			{
				(*iter)->AddRef();
				return (CConnect*)(*iter);
			}
		}
	}

	return nullptr;
}

CState* CTile::FindState()
{
	auto iter = m_listBlockObj.begin();
	auto iterEnd = m_listBlockObj.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetBlockObjType() == BLOCKOBJ_TYPE::WORD)
		{
			if (((CWord*)(*iter))->GetWordType() == WORD_TYPE::STATE)
			{
				(*iter)->AddRef();
				return (CState*)(*iter);
			}
		}
	}

	return nullptr;
}

CName* CTile::FindName()
{
	auto iter = m_listBlockObj.begin();
	auto iterEnd = m_listBlockObj.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetBlockObjType() == BLOCKOBJ_TYPE::WORD)
		{
			if (((CWord*)(*iter))->GetWordType() == WORD_TYPE::NAME)
			{
				(*iter)->AddRef();
				return (CName*)(*iter);
			}
		}
	}

	return nullptr;
}

CWall* CTile::FindWall()
{
	auto iter = m_listBlockObj.begin();
	auto iterEnd = m_listBlockObj.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetBlockObjType() == BLOCKOBJ_TYPE::CHARACTER)
		{
			if (((CCharacter*)(*iter))->GetCharacterType() == CHARACTER_TYPE::WALL)
			{
				(*iter)->AddRef();
				return (CWall*)(*iter);
			}
		}
	}

	return nullptr;
}

CGrass* CTile::FindGrass()
{
	auto iter = m_listBlockObj.begin();
	auto iterEnd = m_listBlockObj.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetBlockObjType() == BLOCKOBJ_TYPE::CHARACTER)
		{
			if (((CCharacter*)(*iter))->GetCharacterType() == CHARACTER_TYPE::GRASS)
			{
				(*iter)->AddRef();
				return (CGrass*)(*iter);
			}
		}
	}

	return nullptr;
}

CNumber* CTile::FindNumber()
{
	auto iter = m_listBlockObj.begin();
	auto iterEnd = m_listBlockObj.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetBlockObjType() == BLOCKOBJ_TYPE::WORD)
		{
			if (((CWord*)(*iter))->GetWordType() == WORD_TYPE::NUMBER)
			{
				(*iter)->AddRef();
				return (CNumber*)(*iter);
			}
		}
	}

	return nullptr;
}

CWater* CTile::FindWater()
{
	auto iter = m_listBlockObj.begin();
	auto iterEnd = m_listBlockObj.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetBlockObjType() == BLOCKOBJ_TYPE::CHARACTER)
		{
			if (((CCharacter*)(*iter))->GetCharacterType() == CHARACTER_TYPE::WATER)
			{
				(*iter)->AddRef();
				return (CWater*)(*iter);
			}
		}
	}

	return nullptr;
}

CBrick* CTile::FindBrick()
{
	auto iter = m_listBlockObj.begin();
	auto iterEnd = m_listBlockObj.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetBlockObjType() == BLOCKOBJ_TYPE::CHARACTER)
		{
			if (((CCharacter*)(*iter))->GetCharacterType() == CHARACTER_TYPE::BRICK)
			{
				(*iter)->AddRef();
				return (CBrick*)(*iter);
			}
		}
	}

	return nullptr;
}

CLava* CTile::FindLava()
{
	auto iter = m_listBlockObj.begin();
	auto iterEnd = m_listBlockObj.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetBlockObjType() == BLOCKOBJ_TYPE::CHARACTER)
		{
			if (((CCharacter*)(*iter))->GetCharacterType() == CHARACTER_TYPE::LAVA)
			{
				(*iter)->AddRef();
				return (CLava*)(*iter);
			}
		}
	}

	return nullptr;
}

bool CTile::DeleteBlockObj(const string& strName)
{
	auto iter = m_listBlockObj.begin();
	auto iterEnd = m_listBlockObj.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == strName)
		{
			SAFE_RELEASE((*iter));
			m_listBlockObj.erase(iter);
			return true;
		}
	}

	return false;
}


void CTile::ClearList()
{
	SAFE_RELEASE_VECLIST(m_listBlockObj);
}

bool CTile::IsEmpty()
{
	return m_listBlockObj.empty();
}

void CTile::SetTileTexture(const string& steTexName)
{
	SAFE_RELEASE(m_pTexture);
	m_pTexture = m_pScene->GetSceneResource()->FindTexture(steTexName);
}

void CTile::SetTileTexture(const string& strTileTexName,
	const TCHAR* pFileName, const string& strPathName)
{
	m_pScene->GetSceneResource()->LoadTexture(strTileTexName,
		pFileName, strPathName); // 텍스쳐를 게임에 로드한다.

	SAFE_RELEASE(m_pTexture); // 기존 텍스쳐 있다면 제거
	m_pTexture = m_pScene->GetSceneResource()->FindTexture(strTileTexName); // 텍스쳐 지정

	m_tTileFrame.vEnd = m_vSize;
}

void CTile::SetTileTextureFrame(const Vector2& vStart, const Vector2& vEnd)
{
	m_tTileFrame.vStart = vStart;
	m_tTileFrame.vEnd = vEnd;
}

void CTile::Render(HDC hDC, float fTime)
{
	//HPEN hPen = nullptr;
	//switch (m_eType)
	//{
	//case TILE_TYPE::NORMAL: // 갈수있는곳 - 파랑색
	//	hPen = GET_SINGLE(CGameManager)->GetBluePen();
	//	break;
	//case TILE_TYPE::NOMOVE: // 못가는곳 - 보라색
	//	hPen = GET_SINGLE(CGameManager)->GetMagentaPen();
	//	break;
	//}
	//hPen = CreatePen(PS_SOLID, 1, RGB(25, 43, 49));

	Vector2	vPos = m_vPos - m_pScene->GetMainCamera()->GetPos();
	/*HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
	SelectObject(hDC, hBrush);*/
	Rectangle(hDC, (int)(vPos.x), (int)(vPos.y), (int)(vPos.x + m_vSize.x), (int)(vPos.y + m_vSize.y));

	//RECT	rc = {};
	//SetRect(&rc, (int)vPos.x + 1, (int)vPos.y + 1, (int)(vPos.x + m_vSize.x - 1), (int)(vPos.y + m_vSize.y - 1));
	//FrameRect(hDC, &rc, hBrush);

	if (m_pTexture) // 텍스쳐가 있으면 텍스쳐를 render 한다.
	{
		m_pTexture->Render(hDC, vPos, m_tTileFrame.vStart,
			m_vSize);
	}

	//SelectObject(hDC, hPrevBrush);
	//SelectObject(hDC, hPrevPen);
	//DeleteObject(hBrush);
	//DeleteObject(hPen);
}

void CTile::Save(FILE* pFile)
{
	fwrite(&m_tTileFrame, sizeof(AnimationFrameInfo), 1, pFile);
	fwrite(&m_eType, sizeof(TILE_TYPE), 1, pFile);
	fwrite(&m_vPos, sizeof(Vector2), 1, pFile);
	fwrite(&m_vSize, sizeof(Vector2), 1, pFile);

	fwrite(&m_iIndexX, sizeof(int), 1, pFile);
	fwrite(&m_iIndexY, sizeof(int), 1, pFile);
	fwrite(&m_iIndex, sizeof(int), 1, pFile);

	fwrite(&m_bTexture, sizeof(bool), 1, pFile);

	if (m_bTexture) // 타일의 텍스쳐가 있다면 저장한다.
		m_pTexture->Save(pFile);
}

void CTile::Load(FILE* pFile)
{
	fread(&m_tTileFrame, sizeof(AnimationFrameInfo), 1, pFile);
	fread(&m_eType, sizeof(TILE_TYPE), 1, pFile);
	fread(&m_vPos, sizeof(Vector2), 1, pFile);
	fread(&m_vSize, sizeof(Vector2), 1, pFile);

	fread(&m_iIndexX, sizeof(int), 1, pFile);
	fread(&m_iIndexY, sizeof(int), 1, pFile);
	fread(&m_iIndex, sizeof(int), 1, pFile);

	fread(&m_bTexture, sizeof(bool), 1, pFile);

	if (m_bTexture)
	{
		size_t	iLength = 0;
		fread(&iLength, sizeof(size_t), 1, pFile);

		char	strName[256] = {};
		fread(strName, 1, iLength, pFile);

		SetTileTexture(strName); // 타일 텍스쳐 지정
	}
}
