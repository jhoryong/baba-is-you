#pragma once

#include "Game.h"

class CFontManager
{
private:
	unordered_map<string, HFONT>	m_mapFont;

public:
	bool Init();
	bool AddFont(const string& strName, const TCHAR* pFontName,
		int iHeight, int iWeight, bool bItalic, 
		bool bUnderLine, bool bStrikeOut);
	HFONT FindFont(const string& strName);

	DECLARE_SINGLE(CFontManager)
};

