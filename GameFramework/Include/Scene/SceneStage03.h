#pragma once
#include "SceneStage.h"
class CSceneStage03 :
    public CSceneStage
{
	friend class CSceneManager;

protected:
	CSceneStage03();
	virtual ~CSceneStage03();

public:
	virtual bool Init();
	virtual void Start();

public:
	virtual void WinTransition(float fTime);
};

