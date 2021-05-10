#pragma once
#include "Scene.h"
class CSceneStart :
	public CScene
{
	friend class CSceneManager;

protected:
	CSceneStart();
	virtual ~CSceneStart();

private:
	bool m_bGameEnter = false;
	float m_fGameEnterTransition = 1.f;
	float m_fGameEnterAcc = 0.f;

public:
	virtual bool Init();
	virtual void Start();
	virtual void Update(float fTime);

private:
	void LoadTexture();
	void LoadAnimation();
	void LoadSound();

public:
	void StartClick(float fTime);
	void Edit(float fTime);
	void AnimEdit(float fTime);
	void Exit(float fTime);

public:
	void SetGameEnter(float f)
	{
		m_bGameEnter = true;
	}
};

