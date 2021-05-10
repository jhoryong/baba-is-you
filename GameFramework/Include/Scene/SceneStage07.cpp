#include "SceneStage07.h"


#include "../Object/MapObj.h"
#include "SceneManager.h"

CSceneStage07::CSceneStage07()
{
}

CSceneStage07::~CSceneStage07()
{
}

bool CSceneStage07::Init()
{
	// Map
	CMapObj* pMapObj = CreateObject<CMapObj>("Map24x14");
	pMapObj->LoadFile("Map24x14.tmp");
	SAFE_RELEASE(pMapObj);

	CSceneStage::Init();

	LoadStage("stage07.txt");

	return true;
}

void CSceneStage07::Start()
{
	CSceneStage::Start();
}

void CSceneStage07::WinTransition(float fTime)
{
	CSceneStage::WinTransition(fTime);

	GET_SINGLE(CSceneManager)->SetClear(7);
}
