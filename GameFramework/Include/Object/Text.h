#pragma once
#include "UI.h"
class CText :
	public CUI
{
public:
	CText();
	virtual ~CText();

private:
	TEXT_MODE	m_eTextMode;
	HFONT		m_hFont;
	bool		m_bTransparent;
	COLORREF	m_Color;
	TCHAR*		m_pText;
	size_t		m_iTextCount;
	float		m_fSlideDist = 30.f;
	float		m_fSlideDistAcc = 0.f;
	float		m_fSpeed = 20.f;
	float		m_bSlideFinish = false;
	bool		m_bRender = false;

public:
	void SetFont(const string& strName);
	void SetText(const TCHAR* pText);

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
	virtual CText* Clone();

public:
	void SetTextMode(TEXT_MODE eMode)
	{
		m_eTextMode = eMode;
	}

	void SetColor(unsigned char r, unsigned char g, unsigned char b)
	{
		m_Color = RGB(r, g, b);
	}

	void SetRender(bool bRender)
	{
		m_bRender = bRender;
	}
};

