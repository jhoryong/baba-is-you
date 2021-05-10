#pragma once

#include "../Game.h"

class CTile
{
	friend class CTileMap; // Tile �� TileMap ������ ���� �����ϰ� �Ѵ�.

private:
	CTile();
	~CTile();

private:
	list<class CBlockObj*>	m_listBlockObj; // �ش� Ÿ�Ͽ� ��ġ�� �� ������Ʈ.

	class CScene*		m_pScene; // �ش� ��
	bool				m_bTexture;
	class CTexture*		m_pTexture; // Ÿ���� �ؽ���
	AnimationFrameInfo	m_tTileFrame; // Ÿ���� �ִϸ��̼� ����������

	TILE_TYPE	m_eType; // Ÿ��Ÿ��
	Vector2		m_vPos; // ��ġ
	Vector2		m_vSize; // ������

	int		m_iIndexX; // �ε��� x
	int		m_iIndexY; // �ε��� y
	int		m_iIndex; // �ε���

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
	void SetTileTexture(const string& steTexName); // Ÿ���� �ؽ��ĸ� �����Ѵ�.
	void SetTileTexture(const string& strTileTexName, // �ؽ��ĸ� �ҷ��ͼ� �����Ѵ�.
		const TCHAR* pFileName, const string& strPathName = TEXTURE_PATH);
	void SetTileTextureFrame(const Vector2& vStart, const Vector2& vEnd); // ��Ʋ�� �ؽ����ϰ�� ������������ �����Ѵ�.
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

