#pragma once
#include "SceneStage.h"
class CSceneStage04 :
    public CSceneStage
{
	friend class CSceneManager;

protected:
	CSceneStage04();
	virtual ~CSceneStage04();

public:
	virtual bool Init();
	virtual void Start();

public:
	virtual void WinTransition(float fTime);
};

