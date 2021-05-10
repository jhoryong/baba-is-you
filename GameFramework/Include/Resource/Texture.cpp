#include "Texture.h"
#include "../PathManager.h"
#include "../GameManager.h"

CTexture::CTexture()
{
}

CTexture::~CTexture()
{
	SAFE_DELETE_VECLIST(m_vecTexture);
}

bool CTexture::LoadTexture(const string& strName, 
	const TCHAR* pFileName, const string& strPathName)
{
	SetName(strName);

	const TCHAR* pPath = GET_SINGLE(CPathManager)->FindPath(strPathName);

	TCHAR		strFullPath[MAX_PATH] = {};

	if (pPath)
		lstrcpy(strFullPath, pPath);

	// 경로 뒤에 파일 이름을 붙여주어서 최종 경로를 만들어낸다.
	lstrcat(strFullPath, pFileName);

	PTextureInfo	pTexInfo = new TextureInfo;

	pTexInfo->hDC = CreateCompatibleDC(GET_SINGLE(CGameManager)->GetWindowDC());
	pTexInfo->hBmp = (HBITMAP)LoadImage(GET_SINGLE(CGameManager)->GetWindowInstance(),
		strFullPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	pTexInfo->hPrevBmp = (HBITMAP)SelectObject(pTexInfo->hDC, pTexInfo->hBmp);

	m_vecTexture.push_back(pTexInfo);

	return true;
}

bool CTexture::LoadTexture(const string& strName, 
	const vector<const TCHAR*>& vecFileName, 
	const string& strPathName)
{
	SetName(strName);

	size_t	iSize = vecFileName.size();
	for (size_t i = 0; i < iSize; ++i)
	{
		const TCHAR* pPath = GET_SINGLE(CPathManager)->FindPath(strPathName);

		TCHAR		strFullPath[MAX_PATH] = {};

		if (pPath)
			lstrcpy(strFullPath, pPath);

		// 경로 뒤에 파일 이름을 붙여주어서 최종 경로를 만들어낸다.
		lstrcat(strFullPath, vecFileName[i]);

		PTextureInfo	pTexInfo = new TextureInfo;

		pTexInfo->hDC = CreateCompatibleDC(GET_SINGLE(CGameManager)->GetWindowDC());
		pTexInfo->hBmp = (HBITMAP)LoadImage(GET_SINGLE(CGameManager)->GetWindowInstance(),
			strFullPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		pTexInfo->hPrevBmp = (HBITMAP)SelectObject(pTexInfo->hDC, pTexInfo->hBmp);

		m_vecTexture.push_back(pTexInfo);
	}

	return true;
}

bool CTexture::LoadTexture(const string& strName, 
	const TCHAR* pFileName, int iCount, const string& strPathName)
{
	SetName(strName);

	for (int i = 0; i < iCount; ++i)
	{
		const TCHAR* pPath = GET_SINGLE(CPathManager)->FindPath(strPathName);

		TCHAR		strFullPath[MAX_PATH] = {};

		if (pPath)
			lstrcpy(strFullPath, pPath);

		TCHAR		strFileName[MAX_PATH] = {};

		wsprintf(strFileName, pFileName, i);

		// 경로 뒤에 파일 이름을 붙여주어서 최종 경로를 만들어낸다.
		lstrcat(strFullPath, strFileName);

		PTextureInfo	pTexInfo = new TextureInfo;

		pTexInfo->hDC = CreateCompatibleDC(GET_SINGLE(CGameManager)->GetWindowDC());
		pTexInfo->hBmp = (HBITMAP)LoadImage(GET_SINGLE(CGameManager)->GetWindowInstance(),
			strFullPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		pTexInfo->hPrevBmp = (HBITMAP)SelectObject(pTexInfo->hDC, pTexInfo->hBmp);

		m_vecTexture.push_back(pTexInfo);
	}

	return true;
}

bool CTexture::LoadTextureFullPath(const string& strName, 
	const TCHAR* pFullPath)
{
	SetName(strName);

	PTextureInfo	pTexInfo = new TextureInfo;

	pTexInfo->hDC = CreateCompatibleDC(GET_SINGLE(CGameManager)->GetWindowDC());
	pTexInfo->hBmp = (HBITMAP)LoadImage(GET_SINGLE(CGameManager)->GetWindowInstance(),
		pFullPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	pTexInfo->hPrevBmp = (HBITMAP)SelectObject(pTexInfo->hDC, pTexInfo->hBmp);

	m_vecTexture.push_back(pTexInfo);

	return true;
}

void CTexture::SetColorKey(unsigned char r, unsigned char g, 
	unsigned char b, int iIndex)
{
	m_vecTexture[iIndex]->bColorKey = true;
	m_vecTexture[iIndex]->iColorKey = RGB(r, g, b);
}

void CTexture::SetColorKeyAll(unsigned char r, unsigned char g, 
	unsigned char b)
{
	size_t	iSize = m_vecTexture.size();
	for (size_t i = 0; i < iSize; ++i)
	{
		m_vecTexture[i]->bColorKey = true;
		m_vecTexture[i]->iColorKey = RGB(r, g, b);
	}
}

void CTexture::Render(HDC hDC, const Vector2& vPos, const Vector2& vImagePos,
	const Vector2& vSize, int iIndex)
{
	if (m_vecTexture[iIndex]->bColorKey)
	{
		TransparentBlt(hDC, (int)vPos.x, (int)vPos.y, (int)vSize.x, (int)vSize.y,
			m_vecTexture[iIndex]->hDC, (int)vImagePos.x, (int)vImagePos.y,
			(int)vSize.x, (int)vSize.y, m_vecTexture[iIndex]->iColorKey);
	}

	else
	{
		BitBlt(hDC, (int)vPos.x, (int)vPos.y, (int)vSize.x, (int)vSize.y,
			m_vecTexture[iIndex]->hDC, (int)vImagePos.x, (int)vImagePos.y,
			SRCCOPY);
	}
}

void CTexture::RenderAlphaBlend(unsigned char cAlpha, HDC hDC, const Vector2& vPos, 
	const Vector2& vImagePos, const Vector2& vSize, int iIndex)
{
	BLENDFUNCTION	tBF = {};

	tBF.BlendOp = 0;
	tBF.BlendFlags = 0;
	tBF.SourceConstantAlpha = cAlpha;
	// AC_SRC_OVER로 하면 비트맵이 32비트여야 한다. 24비트일 경우 이 변수의 값을 0으로 준다.
	tBF.AlphaFormat = 0;

	GdiAlphaBlend(hDC, (int)vPos.x, (int)vPos.y, (int)vSize.x, (int)vSize.y,
		m_vecTexture[iIndex]->hDC, (int)vImagePos.x, (int)vImagePos.y, (int)vSize.x, (int)vSize.y, tBF);
}

void CTexture::Save(FILE* pFile)
{
	size_t	iLength = m_strName.length();

	fwrite(&iLength, sizeof(size_t), 1, pFile);
	fwrite(m_strName.c_str(), 1, iLength, pFile);
}
