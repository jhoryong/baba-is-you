#include "SceneStart.h"

#include "../Object/UIButton.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../GameManager.h"
#include "SceneManager.h"
#include "SceneMainMap.h"
#include "SceneEdit.h"
#include "SceneAnimEdit.h"
#include "../Object/UIImage.h"
#include "../Object/UIBackground.h"
#include "../Scene/SceneStage.h"
#include "../Object/UIBaba.h"


CSceneStart::CSceneStart()
{
	m_eType = SCENE_TYPE::START;
}

CSceneStart::~CSceneStart()
{
	m_pResource->SoundStop("Menu");
}

bool CSceneStart::Init()
{
	m_pMainCamera->SetWorldSize(RESOLUTION);

	LoadTexture();
	LoadAnimation();
	LoadSound();

	// 배경은 단순히 render 할 때 뒤에 배경색깔의 Rectangle 을 그린다.

	// Main Logo
	Vector2 vLogoSize = Vector2(419.f, 147.f);
	float fLogoSpace = 80.f;

	CUIImage* pLogo = CreateObject<CUIImage>("Logo");
	pLogo->SetZOrder(1);
	pLogo->CreateAnimation();
	pLogo->AddAnimation("Logo");
	pLogo->SetPos(RESOLUTION.x / 2.f - 210.f, fLogoSpace);
	pLogo->SetSize(vLogoSize);
	SAFE_RELEASE(pLogo);

	// Start Button
	Vector2 fBabaSize = Vector2(24.f, 24.f);
	Vector2 vButtonSize = Vector2(262.f, 22.f);
	float fFirst = vLogoSize.y + fLogoSpace * 2;
	float fSpace = 2.f;

	//// Baba
	CUIBaba* pBaba = CreateObject<CUIBaba>("Baba");
	pBaba->SetZOrder(1);
	pBaba->CreateAnimation();
	pBaba->AddAnimation("Baba_Right_Normal");
	pBaba->SetPivot(0.f, 0.5f);
	pBaba->SetPos(RESOLUTION.x / 2.f - vButtonSize.x / 2.f - fBabaSize.x, fFirst + vButtonSize.y / 2.f);
	pBaba->SetSize(fBabaSize);
	SAFE_RELEASE(pBaba);

	// m_pResource->LoadSound("Effect", false, "ButtonMouseOn", "1Up.wav");
	// m_pResource->LoadSound("Effect", false, "ButtonClick", "Stun.wav");

	CUIButton* pStartButton = CreateObject<CUIButton>("StartButton");
	pStartButton->SetZOrder(1);

	pStartButton->CreateAnimation();

	pStartButton->AddAnimation(BUTTON_STATE::NORMAL, "StartButtonNormal");
	pStartButton->AddAnimation(BUTTON_STATE::MOUSEON, "StartButtonMouseOn");
	pStartButton->AddAnimation(BUTTON_STATE::CLICK, "StartButtonClick");

	pStartButton->SetClickCallback<CSceneStart>(this, &CSceneStart::SetGameEnter);

	pStartButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonHover_0");
	pStartButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonHover_1");
	pStartButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonHover_2");
	pStartButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonHover_3");
	pStartButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonHover_4");
	pStartButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonHover_5");

	pStartButton->SetPos(RESOLUTION.x / 2.f - vButtonSize.x / 2.f, fFirst);
	pStartButton->SetSize(vButtonSize);

	SAFE_RELEASE(pStartButton);

	// Edit Button
	CUIButton* pEditButton = CreateObject<CUIButton>("EditButton");

	pEditButton->SetZOrder(1);
	pEditButton->CreateAnimation();
	pEditButton->AddAnimation(BUTTON_STATE::NORMAL, "EditButtonNormal");
	pEditButton->AddAnimation(BUTTON_STATE::MOUSEON, "EditButtonMouseOn");
	pEditButton->AddAnimation(BUTTON_STATE::CLICK, "EditButtonClick");

	pEditButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonMouseOn");
	pEditButton->SetEventSound(BUTTON_STATE::CLICK, "ButtonClick");

	pEditButton->SetClickCallback<CSceneStart>(this, &CSceneStart::Edit);

	pEditButton->SetPos(RESOLUTION.x / 2.f -vButtonSize.x / 2.f, fFirst + vButtonSize.y + fSpace);
	pEditButton->SetSize(vButtonSize);

	pEditButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonHover_0");
	pEditButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonHover_1");
	pEditButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonHover_2");
	pEditButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonHover_3");
	pEditButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonHover_4");
	pEditButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonHover_5");

	SAFE_RELEASE(pEditButton);

	// Credit Button
	CUIButton* pCreditButton = CreateObject<CUIButton>("pCreditButton");

	pCreditButton->SetZOrder(1);
	pCreditButton->CreateAnimation();
	pCreditButton->AddAnimation(BUTTON_STATE::NORMAL, "CreditButtonNormal");
	pCreditButton->AddAnimation(BUTTON_STATE::MOUSEON, "CreditButtonMouseOn");
	pCreditButton->AddAnimation(BUTTON_STATE::CLICK, "CreditButtonClick");

	pCreditButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonMouseOn");
	pCreditButton->SetEventSound(BUTTON_STATE::CLICK, "ButtonClick");

	pCreditButton->SetClickCallback<CSceneStart>(this, &CSceneStart::AnimEdit);

	pCreditButton->SetPos(RESOLUTION.x / 2.f - vButtonSize.x / 2.f, fFirst + (vButtonSize.y + fSpace) * 2.f);
	pCreditButton->SetSize(vButtonSize);

	pCreditButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonHover_0");
	pCreditButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonHover_1");
	pCreditButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonHover_2");
	pCreditButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonHover_3");
	pCreditButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonHover_4");
	pCreditButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonHover_5");

	SAFE_RELEASE(pCreditButton);

	// Exit Button
	CUIButton* pExitButton = CreateObject<CUIButton>("ExitButton");
	pExitButton->SetZOrder(1);

	pExitButton->CreateAnimation();
	pExitButton->AddAnimation(BUTTON_STATE::NORMAL, "ExitButtonNormal");
	pExitButton->AddAnimation(BUTTON_STATE::MOUSEON, "ExitButtonMouseOn");
	pExitButton->AddAnimation(BUTTON_STATE::CLICK, "ExitButtonClick");

	pExitButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonMouseOn");
	pExitButton->SetEventSound(BUTTON_STATE::CLICK, "ButtonClick");

	pExitButton->SetClickCallback<CSceneStart>(this, &CSceneStart::Exit);

	pExitButton->SetPos(RESOLUTION.x / 2.f - vButtonSize.x / 2.f, fFirst + (vButtonSize.y + fSpace) * 3.f);
	pExitButton->SetSize(vButtonSize);

	pExitButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonHover_0");
	pExitButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonHover_1");
	pExitButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonHover_2");
	pExitButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonHover_3");
	pExitButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonHover_4");
	pExitButton->SetEventSound(BUTTON_STATE::MOUSEON, "ButtonHover_5");

	SAFE_RELEASE(pExitButton);

	m_pResource->SoundPlay("Menu");

	return true;
}

void CSceneStart::Start()
{
	CScene::Start();

}

void CSceneStart::Update(float fTime)
{
	CScene::Update(fTime);

	if (m_bGameEnter)
		StartClick(fTime);
}

void CSceneStart::LoadTexture()
{
	// Background
	//m_pResource->LoadTexture("Background", TEXT("Background.bmp"));

	// Logo
	m_pResource->LoadTexture("Logo", TEXT("logo/logo_%d.bmp"), 3);
	m_pResource->SetColorKeyAll("Logo", 255, 0, 255);

	// Game Sprite
	m_pResource->LoadTexture("Sprite", TEXT("Sprite.bmp"));
	m_pResource->SetColorKey("Sprite", 255, 0, 255);

	// StartButton
	m_pResource->LoadTexture("StartButtonNormal", TEXT("MenuButton/StartButton_0.bmp"));
	m_pResource->SetColorKey("StartButtonNormal", 255, 0, 255);

	m_pResource->LoadTexture("StartButtonMouseOn", TEXT("MenuButton/StartButton_1.bmp"));
	m_pResource->SetColorKey("StartButtonMouseOn", 255, 0, 255);

	// EditButton
	m_pResource->LoadTexture("EditButtonNormal", TEXT("MenuButton/EditButton_0.bmp"));
	m_pResource->SetColorKey("EditButtonNormal", 255, 0, 255);

	m_pResource->LoadTexture("EditButtonMouseOn", TEXT("MenuButton/EditButton_1.bmp"));
	m_pResource->SetColorKey("EditButtonMouseOn", 255, 0, 255);

	// CreditButton
	m_pResource->LoadTexture("CreditButtonNormal", TEXT("MenuButton/CreditButton_0.bmp"));
	m_pResource->SetColorKey("CreditButtonNormal", 255, 0, 255);

	m_pResource->LoadTexture("CreditButtonMouseOn", TEXT("MenuButton/CreditButton_1.bmp"));
	m_pResource->SetColorKey("CreditButtonMouseOn", 255, 0, 255);

	// ExitButton
	m_pResource->LoadTexture("ExitButtonNormal", TEXT("MenuButton/ExitButton_0.bmp"));
	m_pResource->SetColorKey("ExitButtonNormal", 255, 0, 255);

	m_pResource->LoadTexture("ExitButtonMouseOn", TEXT("MenuButton/ExitButton_1.bmp"));
	m_pResource->SetColorKey("ExitButtonMouseOn", 255, 0, 255);
}

void CSceneStart::LoadAnimation()
{
	// LOGO
	m_pResource->CreateAnimationSequence("Logo", "Logo", ANIM_TYPE::FRAME, ANIM_OPTION::LOOP, ANIM_PLAY_TYPE::NORMAL, 0.5f);
	for (int i = 0; i < 3; ++i)
	{
		m_pResource->AddAnimationFrame("Logo",
			Vector2(0.f, 0.f), Vector2(419.f, 147.f));
	}	

	// Baba icon
	m_pResource->CreateAnimationSequence("Baba_Right_Normal", "Baba_Right_Normal.asq");

	// 시작버튼
	m_pResource->CreateAnimationSequence("StartButtonNormal", "StartButtonNormal", ANIM_TYPE::FRAME, ANIM_OPTION::LOOP, ANIM_PLAY_TYPE::NORMAL, 0.5f);
	m_pResource->AddAnimationFrame("StartButtonNormal",
		Vector2(0.f, 0.f), Vector2(262.f, 22.f));

	m_pResource->CreateAnimationSequence("StartButtonMouseOn", "StartButtonMouseOn", ANIM_TYPE::FRAME, ANIM_OPTION::LOOP, ANIM_PLAY_TYPE::NORMAL, 0.5f);
	m_pResource->AddAnimationFrame("StartButtonMouseOn",
		Vector2(0.f, 0.f), Vector2(262.f, 22.f));

	m_pResource->CreateAnimationSequence("StartButtonClick", "StartButtonMouseOn", ANIM_TYPE::FRAME, ANIM_OPTION::LOOP, ANIM_PLAY_TYPE::NORMAL, 0.5f);
	m_pResource->AddAnimationFrame("StartButtonClick",
		Vector2(0.f, 0.f), Vector2(262.f, 22.f));

	// Edit 버튼
	m_pResource->CreateAnimationSequence("EditButtonNormal", "EditButtonNormal", ANIM_TYPE::FRAME, ANIM_OPTION::LOOP, ANIM_PLAY_TYPE::NORMAL, 0.5f);
	m_pResource->AddAnimationFrame("EditButtonNormal",
		Vector2(0.f, 0.f), Vector2(262.f, 22.f));

	m_pResource->CreateAnimationSequence("EditButtonMouseOn", "EditButtonMouseOn", ANIM_TYPE::FRAME, ANIM_OPTION::LOOP, ANIM_PLAY_TYPE::NORMAL, 0.5f);
	m_pResource->AddAnimationFrame("EditButtonMouseOn",
		Vector2(0.f, 0.f), Vector2(262.f, 22.f));

	m_pResource->CreateAnimationSequence("EditButtonClick", "EditButtonMouseOn", ANIM_TYPE::FRAME, ANIM_OPTION::LOOP, ANIM_PLAY_TYPE::NORMAL, 0.5f);
	m_pResource->AddAnimationFrame("EditButtonClick",
		Vector2(0.f, 0.f), Vector2(262.f, 22.f));

	// Credit 버튼
	m_pResource->CreateAnimationSequence("CreditButtonNormal", "CreditButtonNormal", ANIM_TYPE::FRAME, ANIM_OPTION::LOOP, ANIM_PLAY_TYPE::NORMAL, 0.5f);
	m_pResource->AddAnimationFrame("CreditButtonNormal",
		Vector2(0.f, 0.f), Vector2(262.f, 22.f));

	m_pResource->CreateAnimationSequence("CreditButtonMouseOn", "CreditButtonMouseOn", ANIM_TYPE::FRAME, ANIM_OPTION::LOOP, ANIM_PLAY_TYPE::NORMAL, 0.5f);
	m_pResource->AddAnimationFrame("CreditButtonMouseOn",
		Vector2(0.f, 0.f), Vector2(262.f, 22.f));

	m_pResource->CreateAnimationSequence("CreditButtonClick", "CreditButtonMouseOn", ANIM_TYPE::FRAME, ANIM_OPTION::LOOP, ANIM_PLAY_TYPE::NORMAL, 0.5f);
	m_pResource->AddAnimationFrame("CreditButtonClick",
		Vector2(0.f, 0.f), Vector2(262.f, 22.f));

	// Exit 버튼
	m_pResource->CreateAnimationSequence("ExitButtonNormal", "ExitButtonNormal", ANIM_TYPE::FRAME, ANIM_OPTION::LOOP, ANIM_PLAY_TYPE::NORMAL, 0.5f);
	m_pResource->AddAnimationFrame("ExitButtonNormal",
		Vector2(0.f, 0.f), Vector2(262.f, 22.f));

	m_pResource->CreateAnimationSequence("ExitButtonMouseOn", "ExitButtonMouseOn", ANIM_TYPE::FRAME, ANIM_OPTION::LOOP, ANIM_PLAY_TYPE::NORMAL, 0.5f);
	m_pResource->AddAnimationFrame("ExitButtonMouseOn",
		Vector2(0.f, 0.f), Vector2(262.f, 22.f));

	m_pResource->CreateAnimationSequence("ExitButtonClick", "ExitButtonMouseOn", ANIM_TYPE::FRAME, ANIM_OPTION::LOOP, ANIM_PLAY_TYPE::NORMAL, 0.5f);
	m_pResource->AddAnimationFrame("ExitButtonClick",
		Vector2(0.f, 0.f), Vector2(262.f, 22.f));
}

void CSceneStart::LoadSound()
{
	m_pResource->LoadSound(BGM, true, "Menu", "Music/menu.ogg");

	m_pResource->LoadSound(EFFECT, false, "ButtonHover_0", "Button/067.ogg");
	m_pResource->LoadSound(EFFECT, false, "ButtonHover_1", "Button/068.ogg");
	m_pResource->LoadSound(EFFECT, false, "ButtonHover_2", "Button/069.ogg");
	m_pResource->LoadSound(EFFECT, false, "ButtonHover_3", "Button/070.ogg");
	m_pResource->LoadSound(EFFECT, false, "ButtonHover_4", "Button/070.ogg");
	m_pResource->LoadSound(EFFECT, false, "ButtonHover_5", "Button/072.ogg");
	m_pResource->LoadSound(EFFECT, false, "GoBack", "Transition/goback.ogg");

}

void CSceneStart::StartClick(float fTime)
{
	static bool bGameEnterSoundPlay = false;

	if (!bGameEnterSoundPlay)
	{
		m_pResource->SoundStop("Menu");
		m_pResource->SoundPlay("GoBack");
		bGameEnterSoundPlay = true;
	}

	m_fGameEnterAcc += fTime;

	if (m_fGameEnterAcc >= m_fGameEnterTransition)
	{
		bGameEnterSoundPlay = false;

		m_fGameEnterAcc = 0;

		GET_SINGLE(CSceneManager)->CreateNextScene<CSceneMainMap>();
	}
}

void CSceneStart::Edit(float fTime)
{
	GET_SINGLE(CSceneManager)->CreateNextScene<CSceneEdit>();
	m_pResource->SoundPlay("GoBack");
}

void CSceneStart::AnimEdit(float fTime)
{
	GET_SINGLE(CSceneManager)->CreateNextScene<CSceneAnimEdit>();
	m_pResource->SoundPlay("GoBack");
}

void CSceneStart::Exit(float fTime)
{
	GET_SINGLE(CGameManager)->Exit();
}