#pragma once

#include "Game.h"

class CGameManager
{
	DECLARE_SINGLE(CGameManager)

private:
	HINSTANCE		m_hInst;
	HWND			m_hWnd;
	HDC				m_hDC;
	HDC				m_hBackDC;
	HBITMAP			m_hBackBmp;
	HBITMAP			m_hBackPrevBmp;

	TCHAR			m_strTitle[256];
	TCHAR			m_strClass[256];
	static bool		m_bLoop;
	class CTimer*	m_pTimer;
	Vector2			m_tResolution;

	HDC		m_hAlphaDC;
	HBITMAP m_hAlphaBmp;
	HBITMAP m_hPrevAlphaBmp;

	HBRUSH		m_hGreenBrush;
	HBRUSH		m_hRedBrush;
	HBRUSH		m_hTransparentBrush;
	HBRUSH		m_hBlueBrush;
	HBRUSH		m_hGrayBrush;
	HBRUSH		m_hPurpleBrush;
	HBRUSH		m_hBGBrush;
	HPEN		m_hTransparentPen;
	HPEN		m_hGreenPen;
	HPEN		m_hRedPen;
	HPEN		m_hBluePen;
	HPEN		m_hMagentaPen;
	bool	m_bPrintInfo = false;

public:
	bool Init(HINSTANCE hInst);

private:
	void Register();
	void Create();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public: 
	int Run();

private:
	void Logic();
	void Input(float fTime);
	bool Update(float fTime);
	bool Collision(float fTime);
	void Render(float fTime);

public:
	void Exit();


public:
	CTimer* GetTimer()
	{
		return m_pTimer;
	}

	HBRUSH GetBlueBrush()	const
	{
		return m_hBlueBrush;
	}

	HPEN GetBluePen()	const
	{
		return m_hBluePen;
	}

	HPEN GetMagentaPen()	const
	{
		return m_hMagentaPen;
	}

	HBRUSH GetGrayBrush()	const
	{
		return m_hGrayBrush;
	}

	HBRUSH GetPurpleBrush()	const
	{
		return m_hPurpleBrush;
	}

	HBRUSH GetGreenBrush()	const
	{
		return m_hGreenBrush;
	}

	HBRUSH GetRedBrush()	const
	{
		return m_hRedBrush;
	}

	HBRUSH GetTransparentBrush()	const
	{
		return m_hTransparentBrush;
	}

	HBRUSH GetBGBrush()	const
	{
		return m_hBGBrush;
	}

	HPEN GetGreenPen()	const
	{
		return m_hGreenPen;
	}

	HPEN GetRedPen()	const
	{
		return m_hRedPen;
	}

	Vector2 GetResolution()	const
	{
		return m_tResolution;
	}

	HINSTANCE GetWindowInstance()
	{
		return m_hInst;
	}

	HWND GetWindowHandle()
	{
		return m_hWnd;
	}

	HDC GetWindowDC()	const
	{
		return m_hDC;
	}

	HDC GetBackDC()	const
	{
		return m_hBackDC;
	}

	HDC GetAlphaDC()
	{
		return m_hAlphaDC;
	}

	HPEN GetTransparentPen()
	{
		return m_hTransparentPen;
	}

	bool GetPrintInfo()
	{
		return m_bPrintInfo;
	}

	void PrintInfoSwitch(float f)
	{
		if (m_bPrintInfo)
			m_bPrintInfo = false;

		else
			m_bPrintInfo = true;
	}
};

