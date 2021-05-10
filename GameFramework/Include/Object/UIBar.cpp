#include "UIBar.h"

CUIBar::CUIBar()	:
	m_fMin(0.f),
	m_fMax(1.f),
	m_fValue(1.f),
	m_fPercent(1.f)
{
}

CUIBar::~CUIBar()
{
}

bool CUIBar::Init()
{
	if (!CUI::Init())
		return false;

	SetSize(200.f, 30.f);

	return true;
}

bool CUIBar::Init(const char* pFileName, const string& strPathName)
{
	if (!CUI::Init(pFileName, strPathName))
		return false;

	return true;
}

void CUIBar::Start()
{
	CUI::Start();
}

void CUIBar::Update(float fTime)
{
	CUI::Update(fTime);

	SetPivot(0.f, 0.f);

	SetSize(m_vBarExtent * Vector2(m_fPercent, 1.f));
}

void CUIBar::PostUpdate(float fTime)
{
	CUI::PostUpdate(fTime);
}

void CUIBar::Collision(float fTime)
{
	CUI::Collision(fTime);
}

void CUIBar::PrevRender(float fTime)
{
	CUI::PrevRender(fTime);
}

void CUIBar::Render(HDC hDC, float fTime)
{
	CUI::Render(hDC, fTime);
}

void CUIBar::PostRender(float fTime)
{
	CUI::PostRender(fTime);
}

CUIBar* CUIBar::Clone()
{
	return new CUIBar(*this);
}
