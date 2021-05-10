#pragma once
#include "SceneStage.h"
class CSceneStage00 :
    public CSceneStage
{
	friend class CSceneManager;

protected:
	CSceneStage00();
	virtual ~CSceneStage00();

public:
	virtual bool Init();
	virtual void Start();

public:
	virtual void WinTransition(float fTime);
};

