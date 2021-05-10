#pragma once
#include "Obj.h"

// ���⿡ �ʿ� �ʿ��� ��ɵ��� �߰��Ѵ�.
class CMapObj :
	public CObj
{
public:
	CMapObj();
	virtual ~CMapObj();

private:
	class CTileMap* m_pTileMap;
	Vector2			m_vTileMapRenderPos;

public: 
	// Ÿ�ϸ��� �����Ѵ�.
	bool CreateTileMap(int iCountX, int iCountY,
		float fTileSizeX, float fTileSizeY, unsigned int iColor, bool bTransparent);
	void SetTileMapRenderPos(const Vector2& vPos)
	{
		m_vTileMapRenderPos = vPos;
	}

public:
	virtual bool Init();
	virtual bool Init(const char* pFileName,
		const string& strPathName = DATA_PATH);
	virtual void Start();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void PrevRender(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual void PostRender(float fTime);
	virtual CMapObj* Clone();

public:
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};

