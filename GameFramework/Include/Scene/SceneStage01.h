#pragma once
#include "SceneStage.h"
class CSceneStage01 :
    public CSceneStage
{
	friend class CSceneManager;

protected:
	CSceneStage01();
	virtual ~CSceneStage01();

public:
	virtual bool Init();
	virtual void Start();

public:
	virtual void WinTransition(float fTime);
};

