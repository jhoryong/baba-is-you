#include "SceneStage02.h"

#include "../Object/MapObj.h"
#include "SceneManager.h"

CSceneStage02::CSceneStage02()
{
}

CSceneStage02::~CSceneStage02()
{
}

bool CSceneStage02::Init()
{
	// Map
	CMapObj* pMapObj = CreateObject<CMapObj>("Map24x18");
	pMapObj->LoadFile("Map24x18.tmp");
	SAFE_RELEASE(pMapObj);

	CSceneStage::Init();

	LoadStage("stage02.txt");

	return true;
}

void CSceneStage02::Start()
{
	CSceneStage::Start();
}

void CSceneStage02::WinTransition(float fTime)
{
	CSceneStage::WinTransition(fTime);

	GET_SINGLE(CSceneManager)->SetClear(2);
}
