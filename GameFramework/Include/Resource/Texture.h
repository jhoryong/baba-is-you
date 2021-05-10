#pragma once

#include "../Ref.h"

typedef struct _tagTextureInfo
{
	HDC				hDC;
	HBITMAP			hBmp;
	HBITMAP			hPrevBmp;
	BITMAP			tBmpInfo;
	bool			bColorKey;
	unsigned int	iColorKey;

	_tagTextureInfo()
	{
		bColorKey = false;
		iColorKey = 0;
		hDC = 0;
		hBmp = 0;
		hPrevBmp = 0;
		memset(&tBmpInfo, 0, sizeof(tBmpInfo));
	}

	~_tagTextureInfo()
	{
		SelectObject(hDC, hPrevBmp);
		DeleteObject(hBmp);
		DeleteDC(hDC);
	}
}TextureInfo, *PTextureInfo;

class CTexture :
	public CRef
{
	friend class CResourceManager;

private:
	CTexture();
	~CTexture();

private:
	vector<PTextureInfo>	m_vecTexture;

public:
	HDC GetDC(int iIndex = 0)
	{
		return m_vecTexture[iIndex]->hDC;
	}

public:
	bool LoadTexture(const string& strName, const TCHAR* pFileName,
		const string& strPathName = TEXTURE_PATH);
	bool LoadTexture(const string& strName, const vector<const TCHAR*>& vecFileName,
		const string& strPathName = TEXTURE_PATH);
	bool LoadTexture(const string& strName, const TCHAR* pFileName,
		int iCount, const string& strPathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const string& strName,
		const TCHAR* pFullPath);
	void SetColorKey(unsigned char r, unsigned char g, unsigned char b,
		int iIndex = 0);
	void SetColorKeyAll(unsigned char r, unsigned char g, unsigned char b);
	void Render(HDC hDC, const Vector2& vPos, 	const Vector2& vImagePos,
		const Vector2& vSize, int iIndex = 0);
	void RenderAlphaBlend(unsigned char cAlpha, HDC hDC, const Vector2& vPos, const Vector2& vImagePos,
		const Vector2& vSize, int iIndex = 0);

public:
	void Save(FILE* pFile);
};

