#pragma once
#include "SceneStage.h"
class CSceneStage07 :
    public CSceneStage
{
	friend class CSceneManager;

protected:
	CSceneStage07();
	virtual ~CSceneStage07();

public:
	virtual bool Init();
	virtual void Start();

public:
	virtual void WinTransition(float fTime);
};

