#pragma once

#include "../Game.h"

// 타일 묶음.
class CTileMap
{
public:
	CTileMap();
	~CTileMap();

private:
	class CScene*	m_pScene;			// 속해있는 Scene
	vector<class CTile*>	m_vecTile;	// 타일 벡터
	int		m_iCountX;					// 가로 tile 개수
	int		m_iCountY;					// 세로 tile 개수
	Vector2		m_vStartPos;			// 시작위치
	Vector2		m_vMapSize;				// 맵의 사이즈
	Vector2		m_vTileSize;			// 각 타일의 사이즈

	// 타일 컬러 (한 맵 내의 모든 타일 동일)
	bool			m_bColor;
	unsigned int	m_iColor;			

	// 타일 render 에 사용할 도구
	HPEN	m_hPen;
	HPEN	m_hPrevPen;
	HBRUSH	m_hBrush;
	HBRUSH	m_hPrevBrush;

	// 그리드 출력 여부
	bool m_bGrid = false;

public:
	// Edit Scene 에서 타일맵 정보를 세팅한다.
	bool Init(
		int iCountX, int iCountY,
		const Vector2& vStartPos,
		const Vector2& vTileSize,
		unsigned int iColor,
		bool bTransparent,
		const string& strTileTexName = "",
		const TCHAR* pFileName = nullptr, 
		const string& strPathName = TEXTURE_PATH
	);
	bool Init(const char* pFileName, const string& strPathName = DATA_PATH);
	bool Init();
	void Render(HDC hDC, float fTime);

public:
	void Save(FILE* pFile);
	void Load(FILE* pFile);

public:
	class CTile* FindTile(const Vector2& vRelPos)	const; // 해당 위치의 타일을 찾는다.
	class CTile* FindTile(const int iIndexX, const int iIndexY) const;
	class CTile* FindTile(const int iIndex) const;

public:
	void SetScene(class CScene* pScene); // 해당 맵의 씬을 지정하고 씬에 해당 맵을 추가한다.

	void SetStartPos(const Vector2& vPos)
	{
		m_vStartPos = vPos;
	}

	Vector2 GetStartPos()	const
	{
		return m_vStartPos;
	}

	Vector2 GetMapSize()	const
	{
		return m_vMapSize;
	}

	Vector2 GetTileSize()	const
	{
		return m_vTileSize;
	}

	int GetCountX()	const
	{
		return m_iCountX;
	}

	int GetCountY()	const
	{
		return m_iCountY;
	}

	HPEN GetPen()
	{
		return m_hPen;
	}

	HBRUSH GetBrush()
	{
		return m_hBrush;
	}

	bool GetGrid()
	{
		return m_bGrid;
	}

	void GridSwitch(float fTime = 0.f)
	{
		if (m_bGrid)
			m_bGrid = false;

		else
			m_bGrid = true;
	}

	void ClearTile();
};

