#include "SceneMainMap.h"

#include "Camera.h"
#include "../Resource/ResourceManager.h"

#include "../Object/MapObj.h"
#include "../Object/BackgroundObj.h"
#include "../Object/UIImage.h"
#include "../Object/Selector.h"
#include "../GameManager.h"
#include "../Object/Number.h"
#include "../Object/MapPath.h"
#include "../Object/Flower.h"
#include "../Object/Tree.h"
#include "../Object/Rocket.h"
#include "../Object/Fungi.h"
#include "../Object/LockDoor.h"
#include "../Object/Foliage.h"
#include "../Object/Star.h"
#include "../Object/TPBlock.h"

#include "SceneStage00.h"
#include "SceneStage01.h"
#include "SceneStage02.h"
#include "SceneStage03.h"
#include "SceneStage04.h"
#include "SceneStage05.h"
#include "SceneStage06.h"
#include "SceneStage07.h"
#include "SceneManager.h"
#include "SceneResource.h"

CSceneMainMap::CSceneMainMap()
{
	m_eType = SCENE_TYPE::MAINMAP;
	m_iLevel = GET_SINGLE(CSceneManager)->GetCurrentLevel();
}

CSceneMainMap::~CSceneMainMap()
{
	GET_SINGLE(CInput)->DeleteBindAction("ToMainMap");
}

bool CSceneMainMap::Init()
{
	m_pMainCamera->SetWorldSize(RESOLUTION);

	// Map
	CMapObj* pMapObj = CreateObject<CMapObj>("MainMap");
	pMapObj->LoadFile("MainMap.tmp");
	SAFE_RELEASE(pMapObj);

	LoadTexture();
	LoadAnimation();
	LoadSound();
	AddPrototype();

	//GET_SINGLE(CResourceManager)->SoundPlay("Map");
	m_pResource->SoundPlay("Map");

	// Island
	CBackgroundObj* pIsland = CreateObject<CBackgroundObj>("Island");
	//pIsland->SetZOrder(1);
	pIsland->CreateAnimation();
	pIsland->AddAnimationSequence("Island");
	pIsland->SetPivot(0.5f, 0.5f);
	pIsland->SetPos(RESOLUTION.x / 2.f, RESOLUTION.y / 2.f);
	pIsland->SetSize(792.f, 432.f);
	SAFE_RELEASE(pIsland);

	// Selector
	CSelector* pSelector = CreateObject<CSelector>("Selector");
	pSelector->SetSelectorPos(m_iLevel);
	SAFE_RELEASE(pSelector);

	// Number 00
	CNumber* pNumber = CreateObject<CNumber>("Number00");
	pNumber->SetTileIndex(9, 15);
	pNumber->SetNumber(0);
	SAFE_RELEASE(pNumber);

	// Number 01
	pNumber = CreateObject<CNumber>("Number01");
	pNumber->SetTileIndex(10, 13);
	pNumber->SetNumber(1);
	SAFE_RELEASE(pNumber);

	// Number 02
	pNumber = CreateObject<CNumber>("Number02");
	pNumber->SetTileIndex(10, 12);
	pNumber->SetNumber(2);
	SAFE_RELEASE(pNumber);

	// Number 03
	pNumber = CreateObject<CNumber>("Number03");
	pNumber->SetTileIndex(11, 13);
	pNumber->SetNumber(3);
	SAFE_RELEASE(pNumber);

	// Number 04
	pNumber = CreateObject<CNumber>("Number04");
	pNumber->SetTileIndex(11, 12);
	pNumber->SetNumber(4);
	SAFE_RELEASE(pNumber);

	// Number 05
	pNumber = CreateObject<CNumber>("Number05");
	pNumber->SetTileIndex(10, 11);
	pNumber->SetNumber(5);
	SAFE_RELEASE(pNumber);

	// Number 06
	pNumber = CreateObject<CNumber>("Number06");
	pNumber->SetTileIndex(12, 12);
	pNumber->SetNumber(6);
	SAFE_RELEASE(pNumber);

	// Number 07
	pNumber = CreateObject<CNumber>("Number07");
	pNumber->SetTileIndex(11, 11);
	pNumber->SetNumber(7);
	SAFE_RELEASE(pNumber);

	// MapPath
	CMapPath* pMapPath = CreateObject<CMapPath>("MapPath_0");
	pMapPath->SetTileIndex(10, 15);
	pMapPath->SetNumber(0);
	SAFE_RELEASE(pMapPath);

	pMapPath = CreateObject<CMapPath>("MapPath_1");
	pMapPath->SetTileIndex(10, 14);
	pMapPath->SetNumber(1);
	SAFE_RELEASE(pMapPath);

	// Tree
	CTree* pTree = CreateCloneBlockObj<CTree>("Tree");
	pTree->SetTileIndex(17, 4);
	SAFE_RELEASE(pTree);

	pTree = CreateCloneBlockObj<CTree>("Tree");
	pTree->SetTileIndex(20, 4);
	SAFE_RELEASE(pTree);

	pTree = CreateCloneBlockObj<CTree>("Tree");
	pTree->SetTileIndex(20, 6);
	SAFE_RELEASE(pTree);

	pTree = CreateCloneBlockObj<CTree>("Tree");
	pTree->SetTileIndex(21, 5);
	SAFE_RELEASE(pTree);

	//Flower
	CFlower* pFlower = CreateCloneBlockObj<CFlower>("Flower");
	pFlower->SetTileIndex(11, 7);
	SAFE_RELEASE(pFlower);

	pFlower = CreateCloneBlockObj<CFlower>("Flower");
	pFlower->SetTileIndex(12, 8);
	SAFE_RELEASE(pFlower);

	pFlower = CreateCloneBlockObj<CFlower>("Flower");
	pFlower->SetTileIndex(14, 6);
	SAFE_RELEASE(pFlower);

	// Fungi
	CFungi* pFungi = CreateCloneBlockObj<CFungi>("Fungi");
	pFungi->SetTileIndex(14, 4);
	SAFE_RELEASE(pFungi);

	pFungi = CreateCloneBlockObj<CFungi>("Fungi");
	pFungi->SetTileIndex(18, 4);
	SAFE_RELEASE(pFungi);

	pFungi = CreateCloneBlockObj<CFungi>("Fungi");
	pFungi->SetTileIndex(15, 6);
	SAFE_RELEASE(pFungi);

	pFungi = CreateCloneBlockObj<CFungi>("Fungi");
	pFungi->SetTileIndex(17, 5);
	SAFE_RELEASE(pFungi);

	pFungi = CreateCloneBlockObj<CFungi>("Fungi");
	pFungi->SetTileIndex(20, 5);
	SAFE_RELEASE(pFungi);

	// Foliage
	CFoliage* pFoliage = CreateCloneBlockObj<CFoliage>("Foliage");
	pFoliage->SetTileIndex(17, 12);
	SAFE_RELEASE(pFoliage);

	pFoliage = CreateCloneBlockObj<CFoliage>("Foliage");
	pFoliage->SetTileIndex(19, 12);
	SAFE_RELEASE(pFoliage);

	pFoliage = CreateCloneBlockObj<CFoliage>("Foliage");
	pFoliage->SetTileIndex(21, 11);
	SAFE_RELEASE(pFoliage);

	pFoliage = CreateCloneBlockObj<CFoliage>("Foliage");
	pFoliage->SetTileIndex(21, 13);
	SAFE_RELEASE(pFoliage);

	pFoliage = CreateCloneBlockObj<CFoliage>("Foliage");
	pFoliage->SetTileIndex(22, 10);
	SAFE_RELEASE(pFoliage);

	//Rocket
	CRocket* pRocket = CreateObject<CRocket>("Rocket");
	pRocket->SetTileIndex(19, 2);
	SAFE_RELEASE(pRocket);

	//LockDoor
	CLockDoor* pLockDoor = CreateObject<CLockDoor>("LockDoor01");
	pLockDoor->SetTileIndex(15, 3);
	SAFE_RELEASE(pLockDoor);

	// Star
	CStar* pStar = CreateObject<CStar>("Star");
	pStar->SetTileIndex(29, 0);
	SAFE_RELEASE(pStar);

	// TP Block
	CTPBlock* pTPBlock = CreateCloneBlockObj<CTPBlock>("TPBlock");
	pTPBlock->SetTileIndex(8, 15);
	SAFE_RELEASE(pTPBlock);

	pTPBlock = CreateCloneBlockObj<CTPBlock>("TPBlock");
	pTPBlock->SetTileIndex(9, 14);
	SAFE_RELEASE(pTPBlock);

	pTPBlock = CreateCloneBlockObj<CTPBlock>("TPBlock");
	pTPBlock->SetTileIndex(9, 13);
	SAFE_RELEASE(pTPBlock);

	pTPBlock = CreateCloneBlockObj<CTPBlock>("TPBlock");
	pTPBlock->SetTileIndex(9, 12);
	SAFE_RELEASE(pTPBlock);

	pTPBlock = CreateCloneBlockObj<CTPBlock>("TPBlock");
	pTPBlock->SetTileIndex(9, 11);
	SAFE_RELEASE(pTPBlock);

	pTPBlock = CreateCloneBlockObj<CTPBlock>("TPBlock");
	pTPBlock->SetTileIndex(10, 10);
	SAFE_RELEASE(pTPBlock);

	pTPBlock = CreateCloneBlockObj<CTPBlock>("TPBlock");
	pTPBlock->SetTileIndex(11, 10);
	SAFE_RELEASE(pTPBlock);

	pTPBlock = CreateCloneBlockObj<CTPBlock>("TPBlock");
	pTPBlock->SetTileIndex(12, 11);
	SAFE_RELEASE(pTPBlock);

	pTPBlock = CreateCloneBlockObj<CTPBlock>("TPBlock");
	pTPBlock->SetTileIndex(13, 12);
	SAFE_RELEASE(pTPBlock);

	pTPBlock = CreateCloneBlockObj<CTPBlock>("TPBlock");
	pTPBlock->SetTileIndex(12, 13);
	SAFE_RELEASE(pTPBlock);

	pTPBlock = CreateCloneBlockObj<CTPBlock>("TPBlock");
	pTPBlock->SetTileIndex(11, 14);
	SAFE_RELEASE(pTPBlock);

	pTPBlock = CreateCloneBlockObj<CTPBlock>("TPBlock");
	pTPBlock->SetTileIndex(11, 15);
	SAFE_RELEASE(pTPBlock);

	pTPBlock = CreateCloneBlockObj<CTPBlock>("TPBlock");
	pTPBlock->SetTileIndex(10, 16);
	SAFE_RELEASE(pTPBlock);

	pTPBlock = CreateCloneBlockObj<CTPBlock>("TPBlock");
	pTPBlock->SetTileIndex(9, 16);
	SAFE_RELEASE(pTPBlock);



	return true;
}

void CSceneMainMap::Start()
{
	CScene::Start();
}

void CSceneMainMap::Update(float fTime)
{
	CScene::Update(fTime);

	if (m_bSelect)
		EnterTransition(fTime, m_iLevel);
}

void CSceneMainMap::EnterTransition(float fTime, int iLevel)
{
	static bool bSoundPlay = false;

	if (!bSoundPlay)
	{
		m_pResource->SoundStop("Map");
		//GET_SINGLE(CResourceManager)->SoundPause("Map");
		m_pResource->SoundPlay("Enter");
		bSoundPlay = true;
	}

	m_fEnterTransitionAcc += fTime;

	if (m_fEnterTransitionAcc >= m_fEnterTransitionTime)
	{
		m_fEnterTransitionAcc = 0;
		bSoundPlay = false;

		GET_SINGLE(CSceneManager)->SetCurrentLevel(m_iLevel);

		switch (iLevel)
		{
		case 0:
			GET_SINGLE(CSceneManager)->CreateNextScene<CSceneStage00>();
			break;
		case 1:
			GET_SINGLE(CSceneManager)->CreateNextScene<CSceneStage01>();
			break;
		case 2:
			GET_SINGLE(CSceneManager)->CreateNextScene<CSceneStage02>();
			break;
		case 3:
			GET_SINGLE(CSceneManager)->CreateNextScene<CSceneStage03>();
			break;
		case 4:
			GET_SINGLE(CSceneManager)->CreateNextScene<CSceneStage04>();
			break;
		case 5:
			GET_SINGLE(CSceneManager)->CreateNextScene<CSceneStage05>();
			break;
		case 6:
			GET_SINGLE(CSceneManager)->CreateNextScene<CSceneStage06>();
			break;
		case 7:
			GET_SINGLE(CSceneManager)->CreateNextScene<CSceneStage07>();
			break;
		}
	}
}

void CSceneMainMap::LoadTexture()
{
	// Island
	m_pResource->LoadTexture("Island", TEXT("Island\\Mainmap_%d.bmp"), 3);
	// Sprite
	m_pResource->LoadTexture("Sprite", TEXT("Sprite.bmp"));
	m_pResource->SetColorKey("Sprite", 255, 0, 255);
	// 00
	m_pResource->LoadTexture("00", TEXT("Text_00.bmp"));
	m_pResource->SetColorKey("00", 255, 0, 255);
	// 01
	m_pResource->LoadTexture("01", TEXT("Text_01.bmp"));
	m_pResource->SetColorKey("01", 255, 0, 255);
	// 02
	m_pResource->LoadTexture("02", TEXT("Text_02.bmp"));
	m_pResource->SetColorKey("02", 255, 0, 255);
	// 03
	m_pResource->LoadTexture("03", TEXT("Text_03.bmp"));
	m_pResource->SetColorKey("03", 255, 0, 255);
	// 04
	m_pResource->LoadTexture("04", TEXT("Text_04.bmp"));
	m_pResource->SetColorKey("04", 255, 0, 255);
	// 05
	m_pResource->LoadTexture("05", TEXT("Text_05.bmp"));
	m_pResource->SetColorKey("05", 255, 0, 255);
	// 06
	m_pResource->LoadTexture("06", TEXT("Text_06.bmp"));
	m_pResource->SetColorKey("06", 255, 0, 255);
	// 07
	m_pResource->LoadTexture("07", TEXT("Text_07.bmp"));
	m_pResource->SetColorKey("07", 255, 0, 255);
}

void CSceneMainMap::LoadAnimation()
{
	// MapPath
	m_pResource->CreateAnimationSequence("MapPath_0", "MapPath_0.asq");
	m_pResource->CreateAnimationSequence("MapPath_1", "MapPath_1.asq");

	m_pResource->CreateAnimationSequence("Level00", "Level00.asq");
	m_pResource->CreateAnimationSequence("Level01", "Level01.asq");
	m_pResource->CreateAnimationSequence("Level02", "Level02.asq");
	m_pResource->CreateAnimationSequence("Level03", "Level03.asq");
	m_pResource->CreateAnimationSequence("Level04", "Level04.asq");
	m_pResource->CreateAnimationSequence("Level05", "Level05.asq");
	m_pResource->CreateAnimationSequence("Level06", "Level06.asq");
	m_pResource->CreateAnimationSequence("Level07", "Level07.asq");

	m_pResource->CreateAnimationSequence("Level00_Clear", "Level00_Clear.asq");
	m_pResource->CreateAnimationSequence("Level01_Clear", "Level01_Clear.asq");
	m_pResource->CreateAnimationSequence("Level02_Clear", "Level02_Clear.asq");
	m_pResource->CreateAnimationSequence("Level03_Clear", "Level03_Clear.asq");
	m_pResource->CreateAnimationSequence("Level04_Clear", "Level04_Clear.asq");
	m_pResource->CreateAnimationSequence("Level05_Clear", "Level05_Clear.asq");
	m_pResource->CreateAnimationSequence("Level06_Clear", "Level06_Clear.asq");
	m_pResource->CreateAnimationSequence("Level07_Clear", "Level07_Clear.asq");

	m_pResource->CreateAnimationSequence("Fungi", "Fungi.asq");
	m_pResource->CreateAnimationSequence("Foliage", "Foliage.asq");
	m_pResource->CreateAnimationSequence("Tree", "Tree.asq");
	m_pResource->CreateAnimationSequence("Flower", "Flower.asq");
	m_pResource->CreateAnimationSequence("Rocket", "Rocket.asq");
	m_pResource->CreateAnimationSequence("LockDoor", "LockDoor.asq");
	m_pResource->CreateAnimationSequence("Star", "Star.asq");

	// Island
	m_pResource->CreateAnimationSequence("Island", "Island", ANIM_TYPE::FRAME, ANIM_OPTION::LOOP, ANIM_PLAY_TYPE::NORMAL, 0.5f);

	// Selector
	m_pResource->CreateAnimationSequence("Selector", "Sprite", ANIM_TYPE::ATLAS, ANIM_OPTION::LOOP, ANIM_PLAY_TYPE::NORMAL, 0.5f);

	if (m_bInitial)
	{
		for (int i = 0; i < 3; ++i)
		{
			m_pResource->AddAnimationFrame(
				"Island",
				Vector2::Zero,
				Vector2(792.f, 432.f));
		}
		
		for (int i = 0; i < 3; ++i)
		{
			m_pResource->AddAnimationFrame(
				"Selector",
				Vector2(716.f, 528.f + 32.f * (float)i),
				Vector2(716.f + 32.f, 528.f + 32.f * (float)(i + 1)));
		}
	}

	m_bInitial = false;
}

void CSceneMainMap::LoadSound()
{
	m_pResource->LoadSound(BGM, true, "Map", "Music/map.ogg");

	m_pResource->LoadSound(EFFECT, false, "Enter", "Transition/enter.ogg");

	m_pResource->LoadSound(EFFECT, false, "Walk_0", "Walk\\044.ogg");
	m_pResource->LoadSound(EFFECT, false, "Walk_1", "Walk\\047.ogg");
	m_pResource->LoadSound(EFFECT, false, "Walk_2", "Walk\\048.ogg");
	m_pResource->LoadSound(EFFECT, false, "Walk_3", "Walk\\055.ogg");
	m_pResource->LoadSound(EFFECT, false, "Walk_4", "Walk\\058.ogg");

	m_pResource->LoadSound(EFFECT, false, "Undo_0", "Undo\\016.ogg");
	m_pResource->LoadSound(EFFECT, false, "Undo_1", "Undo\\017.ogg");
	m_pResource->LoadSound(EFFECT, false, "Undo_2", "Undo\\018.ogg");
	m_pResource->LoadSound(EFFECT, false, "Undo_3", "Undo\\019.ogg");
	m_pResource->LoadSound(EFFECT, false, "Undo_4", "Undo\\020.ogg");
}

void CSceneMainMap::AddPrototype()
{
	CObj* pNumber = CreatePrototype<CNumber>("Number");
	SAFE_RELEASE(pNumber);

	CObj* pFungi = CreatePrototype<CFungi>("Fungi");
	SAFE_RELEASE(pFungi);

	CObj* pFlower = CreatePrototype<CFlower>("Flower");
	SAFE_RELEASE(pFlower);

	CObj* pFoliage = CreatePrototype<CFoliage>("Foliage");
	SAFE_RELEASE(pFoliage);

	CObj* pTree = CreatePrototype<CTree>("Tree");
	SAFE_RELEASE(pTree);

	CObj* pRocket = CreatePrototype<CRocket>("Rocket");
	SAFE_RELEASE(pRocket);

	CObj* pTPBlock = CreatePrototype<CTPBlock>("TPBlock");
	SAFE_RELEASE(pTPBlock);
}
