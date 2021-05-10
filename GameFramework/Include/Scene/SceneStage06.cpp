#include "SceneStage06.h"


#include "../Object/MapObj.h"
#include "SceneManager.h"

CSceneStage06::CSceneStage06()
{
}

CSceneStage06::~CSceneStage06()
{
}

bool CSceneStage06::Init()
{
	// Map
	CMapObj* pMapObj = CreateObject<CMapObj>("Map24x14");
	pMapObj->LoadFile("Map24x14.tmp");
	SAFE_RELEASE(pMapObj);

	CSceneStage::Init();

	LoadStage("stage06.txt");

	return true;
}

void CSceneStage06::Start()
{
	CSceneStage::Start();
}

void CSceneStage06::WinTransition(float fTime)
{
	CSceneStage::WinTransition(fTime);

	GET_SINGLE(CSceneManager)->SetClear(6);
}
