#include "MapObj.h"
#include "../Resource/ResourceManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "../Resource/AnimationSequence.h"
#include "../Resource/Texture.h"
#include "../TileMap/TileMap.h"
#include "../TileMap/Tile.h"
#include "../Scene/Camera.h"
#include "../GameManager.h"

CMapObj::CMapObj()	:
	m_pTileMap(nullptr)
{
	m_bEnvironment = true;
}

CMapObj::~CMapObj()
{
	SAFE_DELETE(m_pTileMap);
}

bool CMapObj::CreateTileMap(int iCountX, int iCountY, 
	float fTileSizeX, float fTileSizeY, unsigned int iColor, bool bTransparent)
{
	SAFE_DELETE(m_pTileMap); // 기존 타일맵 제거
	m_pTileMap = new CTileMap; // 타일맵 생성

	m_pTileMap->SetScene(m_pScene); // 씬 지정

	Vector2	vTileSize = Vector2(fTileSizeX, fTileSizeY);

	// 여기서 m_vPos 는 (0.f, 0.f) 인상태이다.

	if (!m_pTileMap->Init(iCountX, iCountY, m_vPos, vTileSize, iColor, bTransparent))
	{
		SAFE_DELETE(m_pTileMap);
		return false;
	}

	SetTileMapRenderPos(m_pTileMap->GetStartPos());

	return true;
}

bool CMapObj::Init()
{
	return true;
}

bool CMapObj::Init(const char* pFileName, const string& strPathName)
{
	if (!CObj::Init(pFileName, strPathName))
		return false;

	return true;
}

void CMapObj::Start()
{
	CObj::Start();
}

void CMapObj::Update(float fTime)
{
	CObj::Update(fTime);
}

void CMapObj::PostUpdate(float fTime)
{
	CObj::PostUpdate(fTime);
}

void CMapObj::Collision(float fTime)
{
	CObj::Collision(fTime);
}

void CMapObj::PrevRender(float fTime)
{
	CObj::PrevRender(fTime);

	m_vTileMapRenderPos = m_pScene->GetMainCamera()->GetPos() - m_vPos;
}

void CMapObj::Render(HDC hDC, float fTime)
{
	//CObj::Render(hDC, fTime);
	if (m_pTexture)
	{
		m_pTexture->Render(hDC, Vector2::Zero,
		m_vTileMapRenderPos, m_vSize);
	}

	if (m_pTileMap)
		m_pTileMap->Render(hDC, fTime);
}

void CMapObj::PostRender(float fTime)
{
	CObj::PostRender(fTime);
}

CMapObj* CMapObj::Clone()
{
	return new CMapObj(*this);
}

void CMapObj::Save(FILE* pFile)
{
	if (!m_pTileMap)
		return;

	// 위치와 크기, Texture가 있을 경우 이름을 저장한다.
	fwrite(&m_vPos, sizeof(Vector2), 1, pFile);
	fwrite(&m_vSize, sizeof(Vector2), 1, pFile);

	bool	bTexture = false;

	if (m_pTexture)
		bTexture = true;

	fwrite(&bTexture, sizeof(bool), 1, pFile);

	if (m_pTexture) // 텍스쳐가 있다면 저장한다.
		m_pTexture->Save(pFile);

	m_pTileMap->Save(pFile); // 타일맵을 저장한다.
}

void CMapObj::Load(FILE* pFile)
{
	// 위치와 크기, Texture가 있을 경우 이름을 저장한다.
	fread(&m_vPos, sizeof(Vector2), 1, pFile);
	fread(&m_vSize, sizeof(Vector2), 1, pFile);

	bool	bTexture = false;

	fread(&bTexture, sizeof(bool), 1, pFile);

	if (bTexture)
	{
		size_t	iLength = 0;
		fread(&iLength, sizeof(size_t), 1, pFile);

		char	strName[256] = {};
		fread(strName, 1, iLength, pFile);

		SetTexture(strName);
	}

	SAFE_DELETE(m_pTileMap);

	m_pTileMap = new CTileMap; // 새 TileMap 생성

	m_pTileMap->SetScene(m_pScene); // Scene 지정

	m_pTileMap->Load(pFile); // TileMap Load

	//SetSize(m_pScene->GetMainCamera()->GetResolution());
	
	m_pScene->GetMainCamera()->SetWorldSize(RESOLUTION);
	// 타일맵의 크기만큼 씬의 월드사이즈를 설정
	/*m_pScene->GetMainCamera()->SetWorldSize(m_pTileMap->GetTileSize().x * m_pTileMap->GetCountX(),
		m_pTileMap->GetTileSize().y * m_pTileMap->GetCountY());*/
}
