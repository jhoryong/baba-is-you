#include "SceneStage00.h"

#include "../Object/MapObj.h"
#include "SceneManager.h"

CSceneStage00::CSceneStage00()
{
}

CSceneStage00::~CSceneStage00()
{
}

bool CSceneStage00::Init()
{
	// Map
	CMapObj* pMapObj = CreateObject<CMapObj>("Stage33x18");
	pMapObj->LoadFile("Map33x18.tmp");
	SAFE_RELEASE(pMapObj);

	CSceneStage::Init();

	LoadStage("stage00.txt");

	return true;
}

void CSceneStage00::Start()
{
	CSceneStage::Start();
}

void CSceneStage00::WinTransition(float fTime)
{
	CSceneStage::WinTransition(fTime);

	GET_SINGLE(CSceneManager)->SetClear(0);
}

