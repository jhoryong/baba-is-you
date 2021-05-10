#include "SceneStage01.h"

#include "SceneManager.h"
#include "../Object/MapObj.h"

CSceneStage01::CSceneStage01()
{
}

CSceneStage01::~CSceneStage01()
{
}

bool CSceneStage01::Init()
{
	// Map
	CMapObj* pMapObj = CreateObject<CMapObj>("Map24x18");
	pMapObj->LoadFile("Map24x18.tmp");
	SAFE_RELEASE(pMapObj);

	CSceneStage::Init();

	LoadStage("stage01.txt");

	return true;
}

void CSceneStage01::Start()
{
	CSceneStage::Start();
}

void CSceneStage01::WinTransition(float fTime)
{
	CSceneStage::WinTransition(fTime);

	GET_SINGLE(CSceneManager)->SetClear(1);
}



