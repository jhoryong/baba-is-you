#pragma once
#include "SceneStage.h"
class CSceneStage05 :
    public CSceneStage
{
	friend class CSceneManager;

protected:
	CSceneStage05();
	virtual ~CSceneStage05();

public:
	virtual bool Init();
	virtual void Start();

public:
	virtual void WinTransition(float fTime);
};

