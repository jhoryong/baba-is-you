#pragma once
#include "SceneStage.h"
class CSceneStage02 :
    public CSceneStage
{
	friend class CSceneManager;

protected:
	CSceneStage02();
	virtual ~CSceneStage02();

public:
	virtual bool Init();
	virtual void Start();

public:
	virtual void WinTransition(float fTime);
};

