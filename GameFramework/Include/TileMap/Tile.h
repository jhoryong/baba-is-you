#pragma once

#include "../Game.h"

class CTile
{
	friend class CTileMap; // Tile 은 TileMap 에서만 생성 가능하게 한다.

private:
	CTile();
	~CTile();

private:
	list<class CBlockObj*>	m_listBlockObj; // 해당 타일에 위치한 블럭 오브젝트.

	class CScene*		m_pScene; // 해당 씬
	bool				m_bTexture;
	class CTexture*		m_pTexture; // 타일의 텍스쳐
	AnimationFrameInfo	m_tTileFrame; // 타일의 애니메이션 프레임정보

	TILE_TYPE	m_eType; // 타일타입
	Vector2		m_vPos; // 위치
	Vector2		m_vSize; // 사이즈

	int		m_iIndexX; // 인덱스 x
	int		m_iIndexY; // 인덱스 y
	int		m_iIndex; // 인덱스

public:
	class CConnect* FindConnect();
	class CState* FindState();
	class CName* FindName();
	class CWall* FindWall();
	class CGrass* FindGrass();
	class CNumber* FindNumber();
	class CWater* FindWater();
	class CBrick* FindBrick();
	class CLava* FindLava();

public:
	void AddBlockObj(class CBlockObj* pBlockObj);
	class CBlockObj* FindBlockObj(const string& strName);
	class CName* FindName(const string& strName);
	bool DeleteBlockObj(const string& strName);
	void ClearList();
	bool IsEmpty();

public:
	void SetTileTexture(const string& steTexName); // 타일의 텍스쳐를 지정한다.
	void SetTileTexture(const string& strTileTexName, // 텍스쳐를 불러와서 지정한다.
		const TCHAR* pFileName, const string& strPathName = TEXTURE_PATH);
	void SetTileTextureFrame(const Vector2& vStart, const Vector2& vEnd); // 아틀라스 텍스쳐일경우 프레임정보를 저장한다.
	void Render(HDC hDC, float fTime);

public:
	void Save(FILE* pFile);
	void Load(FILE* pFile);

public:
	list<class CBlockObj*> GetBlockList() const
	{
		return m_listBlockObj;
	}

	int GetTileIndex()
	{
		return m_iIndex;
	}

	int GetIndexX()
	{
		return m_iIndexX;
	}

	int GetIndexY()
	{
		return m_iIndexY;
	}

	Vector2 GetTilePos()
	{
		return m_vPos;
	}

	TILE_TYPE GetTileType()	const
	{
		return m_eType;
	}

	void SetTileType(TILE_TYPE eType)
	{
		m_eType = eType;
	}

	void SetPos(const Vector2& vPos)
	{
		m_vPos = vPos;
	}

	void SetSize(const Vector2& vSize)
	{
		m_vSize = vSize;
	}

	void SetIndex(int x, int y, int idx)
	{
		m_iIndexX = x;
		m_iIndexY = y;
		m_iIndex = idx;
	}
};

