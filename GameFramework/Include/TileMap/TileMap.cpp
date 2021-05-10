#include "TileMap.h"
#include "../Scene/Scene.h"
#include "Tile.h"
#include "../Scene/Camera.h"
#include "../GameManager.h"
#include "../Input.h"
#include "../Scene/SceneManager.h"

CTileMap::CTileMap() :
	m_pScene(nullptr),
	m_iCountY(0),
	m_iCountX(0),
	m_bColor(true),
	m_iColor(0),
	m_hPen(nullptr),
	m_hBrush(nullptr),
	m_hPrevBrush(nullptr),
	m_hPrevPen(nullptr)
{
}

CTileMap::~CTileMap()
{
	DeleteObject(m_hPen);
	DeleteObject(m_hBrush);

	//GET_SINGLE(CInput)->DeleteBindAction("Grid");
	SAFE_DELETE_VECLIST(m_vecTile);
	m_pScene->DeleteTileMap(this);
}

void CTileMap::SetScene(CScene* pScene)
{
	m_pScene = pScene;
	if (m_pScene)
		m_pScene->AddTileMap(this);
}

void CTileMap::ClearTile()
{
	auto iter = m_vecTile.begin();
	auto iterEnd = m_vecTile.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->ClearList();
	}
	
}

CTile* CTileMap::FindTile(const Vector2& vRelPos) const
{
	int	iIndexX = (int)(vRelPos.x / m_vTileSize.x);
	int	iIndexY = (int)(vRelPos.y / m_vTileSize.y);
		
	// �ε��� �������� �۰ų� �Ѿ�� ����
	if (iIndexX < 0 || iIndexX >= m_iCountX ||
		iIndexY < 0 || iIndexY >= m_iCountY)
		return nullptr;

	int iIndex = (iIndexY * m_iCountX) + iIndexX;

	return m_vecTile[iIndex];
}

CTile* CTileMap::FindTile(const int iIndexX, const int iIndexY) const
{
	int iIndex = (iIndexY * m_iCountX) + iIndexX;

	return m_vecTile[iIndex];
}

CTile* CTileMap::FindTile(const int iIndex) const
{
	if (iIndex >= m_iCountX * m_iCountY || iIndex < 0)
		return nullptr;

	return m_vecTile[iIndex];
}

bool CTileMap::Init(int iCountX, int iCountY,
	const Vector2& vStartPos, const Vector2& vTileSize,
	unsigned int iColor,
	bool bTransparent,
	const string& strTileTexName,
	const TCHAR* pFileName, const string& strPathName)
// Ÿ�ϸ� ������ �����Ѵ�.
{
	m_hPen = BLUEPEN;
	GET_SINGLE(CInput)->DeleteBindAction("Grid");
	GET_SINGLE(CInput)->AddActionKey("Grid", VK_SPACE);
	GET_SINGLE(CInput)->AddBindAction("Grid", KEY_TYPE::DOWN, this, &CTileMap::GridSwitch);

	m_bGrid = true;

	//m_vStartPos = vStartPos;
	//���� Ÿ�ϸ��� 0, 0 ���� �������� �ʱ� ������ �̷��� �ϸ� �ȵȴ�.
	m_vTileSize = vTileSize;
	m_iCountX = iCountX;
	m_iCountY = iCountY;
	
	m_bColor = !bTransparent;
	m_iColor = iColor;
	m_vMapSize = m_vTileSize * Vector2((float)iCountX, (float)iCountY);


	// Ÿ�ϸ��� ���� ��ġ�� �����ش�.
	Vector2 vRS = RESOLUTION;
	vRS /= 2.f;
	m_vStartPos = Vector2(vRS.x - m_vMapSize.x / 2.f, vRS.y - m_vMapSize.y / 2.f);

	m_vecTile.resize((size_t)iCountX * (size_t)iCountY);

	for (int i = 0; i < m_iCountY; ++i)
	{
		for (int j = 0; j < m_iCountX; ++j)
		{
			int	iIndex = i * m_iCountX + j;

			CTile*	pTile = new CTile;

			Vector2	vPos = m_vStartPos + m_vTileSize * Vector2((float)j, (float)i);

			pTile->SetPos(vPos);
			pTile->SetSize(m_vTileSize);
			pTile->SetIndex(j, i, iIndex);
			pTile->m_pScene = m_pScene;

			if (pFileName)
				pTile->SetTileTexture(strTileTexName, pFileName, strPathName);

			m_vecTile[(size_t)iIndex] = pTile;
		}
	}


	return true;
}

bool CTileMap::Init(const char* pFileName, const string& strPathName)
{
	return false;
}

bool CTileMap::Init()
{
	m_hPen = BLUEPEN; // �׸���� �� ����

	//if (GET_SINGLE(CSceneManager)->GetScene()->GetSceneType() == SCENE_TYPE::STAGE)
	//{
	GET_SINGLE(CInput)->DeleteBindAction("Grid");
	GET_SINGLE(CInput)->AddActionKey("Grid", VK_SPACE);
	GET_SINGLE(CInput)->AddBindAction("Grid", KEY_TYPE::DOWN, this, &CTileMap::GridSwitch);
	//}

	return true;
}

void CTileMap::Render(HDC hDC, float fTime)
{
	int	iStartX, iStartY, iEndX, iEndY; // ���� ����, ����

	Vector2	vCameraPos = m_pScene->GetMainCamera()->GetPos();
	Vector2	vResolution = m_pScene->GetMainCamera()->GetResolution();

	vCameraPos -= m_vStartPos; 

	// �ε��� ������ ó���ϱ� ���� TileSize �� �����ش�.
	iStartX = (int)(vCameraPos.x / m_vTileSize.x);
	iStartY = (int)(vCameraPos.y / m_vTileSize.y);
	iEndX = (int)((vCameraPos.x + vResolution.x) / m_vTileSize.x);
	iEndY = (int)((vCameraPos.y + vResolution.y) / m_vTileSize.y);

	if (iStartX >= m_iCountX || iEndX < 0 ||
		iStartY >= m_iCountY || iEndY < 0)
		return;

	iStartX = iStartX < 0 ? 0 : iStartX;
	iEndX = iEndX >= m_iCountX ? m_iCountX - 1 : iEndX;
	iStartY = iStartY < 0 ? 0 : iStartY;
	iEndY = iEndY >= m_iCountY ? m_iCountY - 1 : iEndY;

	m_hPrevBrush = (HBRUSH)SelectObject(hDC, GetStockObject(BLACK_BRUSH)); // �귯�� ����
	//m_hPrevPen = (HPEN)SelectObject(hDC, m_hPen);

	//HPEN hPrevPen = nullptr;
	if (m_pScene->GetSceneType() == SCENE_TYPE::MAINMAP)
		/*hPrevPen = */(HPEN)SelectObject(hDC, TRANSPARENTPEN);

	else
		//m_hPrevPen = (HPEN)SelectObject(hDC, m_hPen);

	for (size_t i = (size_t)iStartY; i <= (size_t)iEndY; ++i)
	{
		for (size_t j = (size_t)iStartX; j <= (size_t)iEndX; ++j)
		{
			m_vecTile[i * (size_t)m_iCountX + j]->Render(hDC, fTime);
		}
	}

	SelectObject(hDC, m_hPrevBrush);

	if (m_pScene->GetSceneType() != SCENE_TYPE::MAINMAP)
		SelectObject(hDC, m_hPrevPen);
	
		//HBRUSH hPrevBrush = (HBRUSH)SelectObject(ALPHADC, TRANSPARENTBRUSH);
		
		HDC hAlphaDC = ALPHADC;

		BYTE iAlpha = 0;

		if (m_bGrid) // �׸��� ���
		{
			iAlpha = 80; // ���İ�
		}
		Vector2 vEndPos = m_vStartPos + m_vMapSize;

		m_hPrevBrush = (HBRUSH)SelectObject(hAlphaDC, GetStockObject(BLACK_BRUSH));
		//m_hPrevPen = (HPEN)SelectObject(hAlphaDC, GetStockObject(BLACK_PEN));
		m_hPrevPen = (HPEN)SelectObject(hAlphaDC, BLUEPEN);

		Rectangle(hAlphaDC, -1, -1, (int)vEndPos.x + 1, (int)vEndPos.y + 1);
		//SelectObject(hAlphaDC, m_hPrevPen);
		
		// ������ : y ���� ���Ѵ�.
		for (int i = 1; i < m_iCountY; ++i)
		{
			MoveToEx(hAlphaDC,
				(int)m_vStartPos.x,
				(int)m_vStartPos.y + (int)m_vTileSize.y * i, nullptr);

			LineTo(hAlphaDC,
				(int)vEndPos.x,
				(int)m_vStartPos.y + (int)m_vTileSize.y * i);
		}

		// ������ : x ���� ���Ѵ�.
		for (int i = 1; i < m_iCountX; ++i)
		{ 
			MoveToEx(hAlphaDC,
				(int)m_vStartPos.x + (int)m_vTileSize.y * i,
				(int)m_vStartPos.y, nullptr);

			LineTo(hAlphaDC,
				(int)m_vStartPos.x + (int)m_vTileSize.y * i,
				(int)vEndPos.y);
		}

		//Vector2 vEnd = vCameraPos + m_vMapSize;

		BLENDFUNCTION tBF = { 0, 0, iAlpha, 0 };

		AlphaBlend(hDC, (int)m_vStartPos.x, (int)m_vStartPos.y, (int)m_vMapSize.x, (int)m_vMapSize.y, hAlphaDC, (int)m_vStartPos.x, (int)m_vStartPos.y, (int)m_vMapSize.x, (int)m_vMapSize.y, tBF);

		SelectObject(hAlphaDC, m_hPrevPen);
		SelectObject(hAlphaDC, m_hPrevBrush);
	
}

void CTileMap::Save(FILE* pFile)
{
	fwrite(&m_iCountX, sizeof(int), 1, pFile);
	fwrite(&m_iCountY, sizeof(int), 1, pFile);

	fwrite(&m_vStartPos, sizeof(Vector2), 1, pFile);
	fwrite(&m_vMapSize, sizeof(Vector2), 1, pFile);
	fwrite(&m_vTileSize, sizeof(Vector2), 1, pFile);

	fwrite(&m_bColor, sizeof(bool), 1, pFile);

	if (m_bColor)
		fwrite(&m_iColor, sizeof(unsigned int), 1, pFile);

	size_t	iSize = m_vecTile.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		m_vecTile[i]->Save(pFile); // ���� Ÿ���� �����Ѵ�.
	}
}

void CTileMap::Load(FILE* pFile)
{
	fread(&m_iCountX, sizeof(int), 1, pFile);
	fread(&m_iCountY, sizeof(int), 1, pFile);

	fread(&m_vStartPos, sizeof(Vector2), 1, pFile);
	fread(&m_vMapSize, sizeof(Vector2), 1, pFile);
	fread(&m_vTileSize, sizeof(Vector2), 1, pFile);

	fread(&m_bColor, sizeof(bool), 1, pFile);

	if (m_bColor)
	{
		fread(&m_iColor, sizeof(unsigned int), 1, pFile);
		m_hBrush = CreateSolidBrush(m_iColor); // Ÿ�� ���� �´� �귯�� ����
		m_hPen = CreatePen(PS_SOLID, 2, m_iColor);
	}

	else
	{
		m_hBrush = TRANSPARENTBRUSH;
		m_hPen = (HPEN)GetStockObject(NULL_PEN);
	}
		
	int	iCount = m_iCountX * m_iCountY;

	SAFE_DELETE_VECLIST(m_vecTile);

	m_vecTile.resize(iCount);

	for (int i = 0; i < iCount; ++i) // ������ŭ Ÿ�� ����
	{
		CTile* pTile = new CTile;

		pTile->m_pScene = m_pScene; // Ÿ���� Scene ����
		pTile->Load(pFile);

		m_vecTile[i] = pTile;
	}

	Init();
}
