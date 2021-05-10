#include "SceneStage05.h"


#include "../Object/MapObj.h"
#include "SceneManager.h"

CSceneStage05::CSceneStage05()
{
}

CSceneStage05::~CSceneStage05()
{
}

bool CSceneStage05::Init()
{
	// Map
	CMapObj* pMapObj = CreateObject<CMapObj>("Map33x18");
	pMapObj->LoadFile("Map33x18.tmp");
	SAFE_RELEASE(pMapObj);

	CSceneStage::Init();

	LoadStage("stage05.txt");

	return true;
}

void CSceneStage05::Start()
{
	CSceneStage::Start();
}

void CSceneStage05::WinTransition(float fTime)
{
	CSceneStage::WinTransition(fTime);

	GET_SINGLE(CSceneManager)->SetClear(5);
}