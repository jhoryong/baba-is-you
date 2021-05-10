#include "UIImage.h"

CUIImage::CUIImage()
{
}

CUIImage::~CUIImage()
{
}

bool CUIImage::Init()
{
	if (!CUI::Init())
		return false;

	return true;
}

bool CUIImage::Init(const char* pFileName, const string& strPathName)
{
	if (!CUI::Init(pFileName, strPathName))
		return false;

	return true;
}

void CUIImage::Start()
{
	CUI::Start();
}

void CUIImage::Update(float fTime)
{
	CUI::Update(fTime);
}

void CUIImage::PostUpdate(float fTime)
{
	CUI::PostUpdate(fTime);
}

void CUIImage::Collision(float fTime)
{
	CUI::Collision(fTime);
}

void CUIImage::PrevRender(float fTime)
{
	CUI::PrevRender(fTime);
}

void CUIImage::Render(HDC hDC, float fTime)
{
	CUI::Render(hDC, fTime);
}

void CUIImage::PostRender(float fTime)
{
	CUI::PostRender(fTime);
}

CUIImage* CUIImage::Clone()
{
	return new CUIImage(*this);
}

void CUIImage::AddAnimation(const string& strName)
{
	m_strAnimationName = strName;
	AddAnimationSequence(strName);
}
