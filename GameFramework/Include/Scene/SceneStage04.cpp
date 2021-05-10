#include "SceneStage04.h"

#include "../Object/MapObj.h"
#include "SceneManager.h"

CSceneStage04::CSceneStage04()
{
}

CSceneStage04::~CSceneStage04()
{
}

bool CSceneStage04::Init()
{
	// Map
	CMapObj* pMapObj = CreateObject<CMapObj>("Map24x14");
	pMapObj->LoadFile("Map24x14.tmp");
	SAFE_RELEASE(pMapObj);

	CSceneStage::Init();

	LoadStage("stage04.txt");

	return true;
}

void CSceneStage04::Start()
{
	CSceneStage::Start();
}

void CSceneStage04::WinTransition(float fTime)
{
	CSceneStage::WinTransition(fTime);

	GET_SINGLE(CSceneManager)->SetClear(4);
}
