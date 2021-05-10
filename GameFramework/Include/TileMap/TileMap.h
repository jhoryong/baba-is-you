#pragma once

#include "../Game.h"

// Ÿ�� ����.
class CTileMap
{
public:
	CTileMap();
	~CTileMap();

private:
	class CScene*	m_pScene;			// �����ִ� Scene
	vector<class CTile*>	m_vecTile;	// Ÿ�� ����
	int		m_iCountX;					// ���� tile ����
	int		m_iCountY;					// ���� tile ����
	Vector2		m_vStartPos;			// ������ġ
	Vector2		m_vMapSize;				// ���� ������
	Vector2		m_vTileSize;			// �� Ÿ���� ������

	// Ÿ�� �÷� (�� �� ���� ��� Ÿ�� ����)
	bool			m_bColor;
	unsigned int	m_iColor;			

	// Ÿ�� render �� ����� ����
	HPEN	m_hPen;
	HPEN	m_hPrevPen;
	HBRUSH	m_hBrush;
	HBRUSH	m_hPrevBrush;

	// �׸��� ��� ����
	bool m_bGrid = false;

public:
	// Edit Scene ���� Ÿ�ϸ� ������ �����Ѵ�.
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
	class CTile* FindTile(const Vector2& vRelPos)	const; // �ش� ��ġ�� Ÿ���� ã�´�.
	class CTile* FindTile(const int iIndexX, const int iIndexY) const;
	class CTile* FindTile(const int iIndex) const;

public:
	void SetScene(class CScene* pScene); // �ش� ���� ���� �����ϰ� ���� �ش� ���� �߰��Ѵ�.

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

