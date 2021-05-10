#include "FontManager.h"

DEFINITION_SINGLE(CFontManager)

CFontManager::CFontManager()
{
}

CFontManager::~CFontManager()
{
	auto	iter = m_mapFont.begin();
	auto	iterEnd = m_mapFont.end();

	for (; iter != iterEnd; ++iter)
	{
		DeleteObject(iter->second);
	}
}

bool CFontManager::Init()
{
	/*
	두께 기본값
	FF_DONTCARE		0
	FW_THIN					100
	FW_EXTRALIGHT	200
	FW_ULTRALIGHT	200
	FW_LIGHT				300
	FW_NORMAL			400
	FW_REGULAR			400
	FW_MEDIUM			500
	FW_SEMIBOLD		600
	FW_DEMIBOLD		600
	FW_BOLD				700
	FW_EXTRABOLD		800
	FW_ULTRABOLD		800
	FW_HEAVY				900
	FW_BLACK				900
	*/
	AddFont("Helvetica", TEXT("Helvetica"), 20, FW_BOLD, false,
		false, false); 
	AddFont("AppleSDGothicNeoB00", TEXT("AppleSDGothicNeoB00"), 20, FW_BOLD, false,
		false, false);
	AddFont("Tahoma", TEXT("Tahoma"), 20, FW_BOLD, false,
		false, false);
		AddFont("Press Start 2P", TEXT("Press Start 2P"), 20, FW_BOLD, false,
			false, false);
	return true;
}

bool CFontManager::AddFont(const string& strName,
	const TCHAR* pFontName, int iHeight,
	int iWeight, bool bItalic, bool bUnderLine, bool bStrikeOut)
{
	HFONT		hFont = FindFont(strName);

	if (hFont)
		return false;

	hFont = CreateFont(iHeight, 0, 0, 0, iWeight,
		(DWORD)bItalic, (DWORD)bUnderLine, (DWORD)bStrikeOut,
		DEFAULT_CHARSET/*HANGEUL_CHARSET*/, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN,
		pFontName);

	if (!hFont)
		return false;

	m_mapFont.insert(make_pair(strName, hFont));

	return true;
}

HFONT CFontManager::FindFont(const string& strName)
{
	auto	iter = m_mapFont.find(strName);

	if (iter == m_mapFont.end())
		return 0;
	
	return iter->second;
}
