#pragma once
#include "Scene.h"

class CSceneMainMap :
    public CScene
{
	friend class CSceneManager;

protected:
	CSceneMainMap();
	virtual ~CSceneMainMap();

protected:
	int		m_iLevel = -1;
	int		m_bSelect = false;
	float	m_fEnterTransitionTime = 1.f;
	float	m_fEnterTransitionAcc = 0.f;

public:
	virtual bool Init();
	virtual void Start();
	virtual void Update(float fTime);

public:
	void EnterTransition(float fTime, int iLevel);

private:
	virtual void AddPrototype();
	virtual void LoadTexture();
	virtual void LoadAnimation();
	void LoadSound();

public:
	void SetLevel(int iLevel)
	{
		m_iLevel = iLevel;
	}

	void SetSelect(bool bSelect)
	{
		m_bSelect = bSelect;
	}
};

