#include "UIBackground.h"
#include "../GameManager.h"

CUIBackground::CUIBackground()
{
}

CUIBackground::~CUIBackground()
{
}

bool CUIBackground::Init()
{
	// if (!CUI::Init())
		// return false;

	return true;
}

bool CUIBackground::Init(const char* pFileName, const string& strPathName)
{
	if (!CUI::Init(pFileName, strPathName))
		return false;

	return true;
}

void CUIBackground::Start()
{
	CUI::Start();
}

void CUIBackground::Update(float fTime)
{
	CUI::Update(fTime);
}

void CUIBackground::PostUpdate(float fTime)
{
	//CUI::PostUpdate(fTime);
}

void CUIBackground::Collision(float fTime)
{
	//CUI::Collision(fTime);
}

void CUIBackground::PrevRender(float fTime)
{
	CUI::PrevRender(fTime);
}

void CUIBackground::Render(HDC hDC, float fTime)
{
	CUI::Render(hDC, fTime);
	/*Vector2 vRS = RESOLUTION;

	HBRUSH hPrevBrush = (HBRUSH)SelectObject(hDC, BGBRUSH);

	Rectangle(hDC, -1, -1, (int)RESOLUTION.x + 1, (int)RESOLUTION.y + 1);

	SelectObject(hDC, hPrevBrush);*/
}

void CUIBackground::PostRender(float fTime)
{
	CUI::PostRender(fTime);
}

CUIBackground* CUIBackground::Clone()
{
	return new CUIBackground(*this);
}

void CUIBackground::AddAnimation(const string& strName)
{
	m_strAnimationName = strName;
	AddAnimationSequence(strName);
}
