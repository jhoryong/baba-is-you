#include "SceneStage.h"

#include "SceneResource.h"
#include "Camera.h"
#include "../Object/Obj.h"
#include "../Object/MapObj.h"
#include "../GameManager.h"
#include "../Object/BlockObj.h"

#include "../PathManager.h"
#include "../Scene/SceneMainMap.h"
#include "../Scene/SceneManager.h"
#include "../Input.h"
#include "../TileMap/TileMap.h"
#include "../Object/Text.h"
#include "../Object/BlockObj.h"

CSceneStage::CSceneStage()
{
	m_eType = SCENE_TYPE::STAGE;
}

CSceneStage::~CSceneStage()
{
	
}

bool CSceneStage::Init()
{
	LoadTexture();
	LoadAnimation();
	AddPrototype();
	LoadSound();

	m_pResource->SoundPlay("Stage0");

	CText* pUndo = CreateObject<CText>("Undo");

	pUndo->SetTextMode(TM_UI);
	pUndo->SetText(TEXT("Z - UNDO"));
	pUndo->SetColor(255, 255, 255);
	pUndo->SetFont("Tahoma");
	pUndo->SetSize(80.f, 15.f);
	pUndo->SetPivot(0.5f, 0.f);
	pUndo->SetPos(RESOLUTION.x / 2.f - 100.f, 10.f);
	pUndo->SetRender(false);
	SAFE_RELEASE(pUndo);

	CText* pRestart = CreateObject<CText>("Restart");

	pRestart->SetTextMode(TM_UI);
	pRestart->SetText(TEXT("R - RESTART"));
	pRestart->SetColor(255, 255, 255);
	pRestart->SetFont("Tahoma");
	pRestart->SetSize(80.f, 15.f);
	pRestart->SetPivot(0.5f, 0.f);
	pRestart->SetPos(RESOLUTION.x / 2.f + 100.f, 10.f);
	pRestart->SetRender(false);
	SAFE_RELEASE(pRestart);

	return true;
}

void CSceneStage::Start()
{
	CScene::Start();

	GET_SINGLE(CInput)->DeleteBindAction("ToMainMap");
	GET_SINGLE(CInput)->AddActionKey("ToMainMap", VK_ESCAPE);
	GET_SINGLE(CInput)->AddBindAction("ToMainMap", KEY_TYPE::DOWN, this, &CSceneStage::SetExit);
}

void CSceneStage::Update(float fTime)
{
	CScene::Update(fTime);

	static bool bSound = true;

	if (m_bStuck)
	{
		if (!m_bTextShown)
			AppearText(fTime);
	}

	else
	{
		if (m_bTextShown)
			InitText();
	}

	if (m_bWin)
		WinTransition(fTime);

	if (m_bExit)
		ToMainMap(fTime);
}

void CSceneStage::LoadSound()
{
	m_pResource->LoadSound(BGM, true, "Stage0", "Music/baba.ogg");
	m_pResource->LoadSound(BGM, true, "Noise", "Music/noise.ogg");

	m_pResource->LoadSound(EFFECT, false, "Win", "Transition/win.ogg");
	m_pResource->LoadSound(EFFECT, false, "Restart", "Transition/restart.ogg");
	m_pResource->LoadSound(EFFECT, false, "GoBack", "Transition/goback.ogg");

	m_pResource->LoadSound(EFFECT, false, "Walk_0", "Walk\\044.ogg");
	m_pResource->LoadSound(EFFECT, false, "Walk_1", "Walk\\047.ogg");
	m_pResource->LoadSound(EFFECT, false, "Walk_2", "Walk\\048.ogg");
	m_pResource->LoadSound(EFFECT, false, "Walk_3", "Walk\\055.ogg");
	m_pResource->LoadSound(EFFECT, false, "Walk_4", "Walk\\058.ogg");

	m_pResource->LoadSound(EFFECT, false, "Push_0", "Push\\049.ogg");
	m_pResource->LoadSound(EFFECT, false, "Push_1", "Push\\050.ogg");
	m_pResource->LoadSound(EFFECT, false, "Push_2", "Push\\053.ogg");
	m_pResource->LoadSound(EFFECT, false, "Push_3", "Push\\054.ogg");

	m_pResource->LoadSound(EFFECT, false, "Connect_0", "Connect\\036.ogg");
	m_pResource->LoadSound(EFFECT, false, "Connect_1", "Connect\\038.ogg");
	m_pResource->LoadSound(EFFECT, false, "Connect_2", "Connect\\039.ogg");
	m_pResource->LoadSound(EFFECT, false, "Connect_3", "Connect\\040.ogg");
	m_pResource->LoadSound(EFFECT, false, "Connect_4", "Connect\\041.ogg");

	m_pResource->LoadSound(EFFECT, false, "Undo_0", "Undo\\016.ogg");
	m_pResource->LoadSound(EFFECT, false, "Undo_1", "Undo\\017.ogg");
	m_pResource->LoadSound(EFFECT, false, "Undo_2", "Undo\\018.ogg");
	m_pResource->LoadSound(EFFECT, false, "Undo_3", "Undo\\019.ogg");
	m_pResource->LoadSound(EFFECT, false, "Undo_4", "Undo\\020.ogg");

	m_pResource->LoadSound(EFFECT, false, "Sink_0", "Sink\\027.ogg");
	m_pResource->LoadSound(EFFECT, false, "Sink_1", "Sink\\028.ogg");
	m_pResource->LoadSound(EFFECT, false, "Sink_2", "Sink\\029.ogg");
	m_pResource->LoadSound(EFFECT, false, "Sink_3", "Sink\\030.ogg");

	m_pResource->LoadSound(EFFECT, false, "Defeat_0", "Defeat\\006.ogg");
	m_pResource->LoadSound(EFFECT, false, "Defeat_1", "Defeat\\007.ogg");
	m_pResource->LoadSound(EFFECT, false, "Defeat_2", "Defeat\\009.ogg");
	m_pResource->LoadSound(EFFECT, false, "Defeat_3", "Defeat\\010.ogg");

	m_pResource->LoadSound(EFFECT, false, "Melt_0", "Melt\\117.ogg");
	m_pResource->LoadSound(EFFECT, false, "Melt_1", "Melt\\118.ogg");
	m_pResource->LoadSound(EFFECT, false, "Melt_2", "Melt\\119.ogg");
	m_pResource->LoadSound(EFFECT, false, "Melt_3", "Melt\\120.ogg");
	m_pResource->LoadSound(EFFECT, false, "Melt_4", "Melt\\121.ogg");
	m_pResource->LoadSound(EFFECT, false, "Melt_5", "Melt\\122.ogg");
}

void CSceneStage::LoadTexture()
{
	CScene::LoadTexture();
}

void CSceneStage::LoadAnimation()
{
	CScene::LoadAnimation();
}

void CSceneStage::AddPrototype()
{
	CScene::AddPrototype();
}

CBlockObj* CSceneStage::CreateBlockObj(const char* cName)
{
	return CScene::CreateBlockObj(cName);
}

void CSceneStage::WinTransition(float fTime)
{
	static bool bSoundPlay = false;

	if (!bSoundPlay)
	{
		m_pResource->SoundStop("Stage0");
		m_pResource->SoundPlay("Win");
		bSoundPlay = true;
	}

	m_fWinTransitionAcc += fTime;

	if (m_fWinTransitionAcc >= m_fWinTransitionTime)
	{
		bSoundPlay = false;

		m_fWinTransitionAcc = 0;

		GET_SINGLE(CSceneManager)->CreateNextScene<CSceneMainMap>();
	}

}

void CSceneStage::Undo(float fTime)
{
	CScene::Undo(fTime);

	m_bLavaMelt = false;

	InitText();
}

void CSceneStage::Restart(float fTime)
{
	CScene::Restart(fTime);

	m_bLavaMelt = false;

	InitText();
}

void CSceneStage::AppearText(float fTime)
{
	if (!m_bMusicPause)
	{
		m_pResource->SoundPause("Stage0");
		m_pResource->SoundPlay("Noise");

		m_bMusicPause = true;
	}

	m_fTextWaitAcc += fTime;

	if (m_fTextWaitAcc >= m_fTextWaitTime)
	{
		auto iter = m_UIList.begin();
		auto iterEnd = m_UIList.end();

		bool bFinish = false;

		for (; iter != iterEnd; ++iter)
		{
			((CText*)*iter)->SetRender(true);
		}
		m_bTextShown = true;
	}
}

void CSceneStage::InitText()
{
	if (m_bMusicPause)
	{
		m_pResource->SoundResume("Stage0");
		m_pResource->SoundStop("Noise");

		m_bMusicPause = false;
	}

	m_bStuck = false;

	m_fTextWaitAcc = 0.f;
	m_bTextShown = false;

	auto iter = m_UIList.begin();
	auto iterEnd = m_UIList.end();

	for (; iter != iterEnd; ++iter)
	{
		((CText*)*iter)->SetRender(false);
	}
}

void CSceneStage::ToMainMap(float fTime)
{
	static bool bExitSoundPlay = false;

	if (!bExitSoundPlay)
	{
		m_pResource->SoundStop("Stage0");
		m_pResource->SoundPlay("GoBack");
		bExitSoundPlay = true;
	}

	m_fExitTransitionAcc += fTime;

	if (m_fExitTransitionAcc >= m_fExitTransitionTime)
	{
		bExitSoundPlay = false;

		m_fExitTransitionAcc = 0;

		GET_SINGLE(CSceneManager)->CreateNextScene<CSceneMainMap>();
	}
}

bool CSceneStage::FindYou()
{
	auto iter = m_ObjList->begin();
	auto iterEnd = m_ObjList->end();

	int iCount = 0;

	for (; iter != iterEnd; ++iter)
	{
		if (((CBlockObj*)(*iter))->GetYou())
		{
			++iCount;
		}
	}

	if (iCount > 1)
		return true;

	else
		return false;
}

