#include "SceneStage03.h"

#include "../Object/MapObj.h"
#include "SceneManager.h"

CSceneStage03::CSceneStage03()
{
}

CSceneStage03::~CSceneStage03()
{
}

bool CSceneStage03::Init()
{
	// Map
	CMapObj* pMapObj = CreateObject<CMapObj>("Map22x16");
	pMapObj->LoadFile("Map22x16.tmp");
	SAFE_RELEASE(pMapObj);

	CSceneStage::Init();

	LoadStage("stage03.txt");

	return true;
}

void CSceneStage03::Start()
{
	CSceneStage::Start();
}

void CSceneStage03::WinTransition(float fTime)
{
	CSceneStage::WinTransition(fTime);

	GET_SINGLE(CSceneManager)->SetClear(3);
}
