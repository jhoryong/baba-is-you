#include "Text.h"
#include "../FontManager.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"

CText::CText()
{
	m_eTextMode = TM_UI;
	m_hFont = GET_SINGLE(CFontManager)->FindFont("Helvetica");
	m_bTransparent = true;
	m_Color = RGB(0, 0, 0);

	m_iTextCount = 256;

	m_pText = new TCHAR[257];
	memset(m_pText, 0, sizeof(TCHAR) * 256);
}

CText::~CText()
{
	delete[]	m_pText;
}

void CText::SetFont(const string& strName)
{
	m_hFont = GET_SINGLE(CFontManager)->FindFont(strName);
}

void CText::SetText(const TCHAR* pText)
{
	size_t	iLength = lstrlen(pText);

	if (iLength > m_iTextCount)
	{
		m_iTextCount = iLength;
		delete[]	m_pText;
		m_pText = new TCHAR[iLength + 1];
		memset(m_pText, 0, sizeof(TCHAR) * (iLength + 1));
	}

	lstrcpy(m_pText, pText);
}

bool CText::Init()
{
	//if (!CUI::Init())
		//return false;

	return true;
}

bool CText::Init(const char* pFileName, const string& strPathName)
{
	//if (!CUI::Init(pFileName, strPathName))
	//	return false;

	return true;
}

void CText::Start()
{
	//CUI::Start();
}

void CText::Update(float fTime)
{
	//CUI::Update(fTime);
}

void CText::PostUpdate(float fTime)
{
	//CUI::PostUpdate(fTime);
}

void CText::Collision(float fTime)
{
	//CUI::Collision(fTime);
}

void CText::PrevRender(float fTime)
{
	if (m_eTextMode == TM_WORLD)
		m_vRenderPos = m_vPos - m_pScene->GetMainCamera()->GetPos();

	else
		m_vRenderPos = m_vPos;
}

void CText::Render(HDC hDC, float fTime)
{
	if (m_bRender)
	{
		if (m_bTransparent)
			SetBkMode(hDC, TRANSPARENT);

		else
			SetBkMode(hDC, OPAQUE);

		SetTextColor(hDC, m_Color);

		//SetTextAlign(hDC, TA_CENTER);

		Vector2	vLT = m_vRenderPos - m_vPivot * m_vSize;

		// 폰트를 적용한다.
		HFONT		hOldFont = (HFONT)SelectObject(hDC, m_hFont);

		TextOut(hDC, (int)vLT.x, (int)vLT.y, m_pText, (int)m_iTextCount);

		SelectObject(hDC, hOldFont);
	}
}

void CText::PostRender(float fTime)
{
	CUI::PostRender(fTime);
}

CText* CText::Clone()
{
	return new CText(*this);
}

