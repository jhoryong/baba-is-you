#pragma once

#include "Scene.h"

class CSceneStage :
	public CScene
{
	friend class CSceneManager;

protected:
	CSceneStage();
	virtual ~CSceneStage() = 0;

protected:
	bool	m_bWin = false;
	bool    m_bExit = false;
	bool	m_bStuck = false;
	float   m_fTextWaitTime = 2.f;
	float   m_fTextWaitAcc = 0.f;
	bool    m_bTextShown = false;
	bool m_bMusicPause = false;
	float	m_fWinTransitionTime = 3.f;
	float   m_fWinTransitionAcc = 0.f;
	float	m_fExitTransitionTime = 1.f;
	float   m_fExitTransitionAcc = 0.f;

public:
	virtual bool Init();
	virtual void Start();
	virtual void Update(float fTime);

private:
	void LoadSound();

public:
	virtual void LoadTexture();
	virtual void LoadAnimation();
	virtual	void AddPrototype();
	virtual class CBlockObj* CreateBlockObj(const char* cName);

public:
	virtual void WinTransition(float fTime) = 0;
	virtual void Undo(float fTime);
	virtual void Restart(float fTime);
	void AppearText(float fTime);
	void InitText();

private:
	void ToMainMap(float fTime);

public:
	void SetWin(bool bWin)
	{
		m_bWin = bWin;
	}

	bool GetWin()
	{
		return m_bWin;
	}

	void SetExit(float fTime)
	{
		m_bExit = true;
	}

	bool GetExit()
	{
		return m_bExit;
	}

	void SetStuck(bool bStuck)
	{
		m_bStuck = bStuck;
	};

	bool GetStuck()
	{
		return m_bStuck;
	}
	
	bool FindYou();
};

