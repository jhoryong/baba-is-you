#include "SceneAnimEdit.h"

#include "Camera.h"
#include "../Input.h"
#include "../AnimationToolDlg.h"
#include "SceneResource.h"
#include "../Object/UIBackground.h"

CSceneAnimEdit::CSceneAnimEdit() :
	m_pAnimationToolDlg(nullptr)
{
	m_eType = SCENE_TYPE::ANIMEDIT;
}

CSceneAnimEdit::~CSceneAnimEdit()
{
	SAFE_DELETE(m_pAnimationToolDlg);
}

bool CSceneAnimEdit::Init()
{
	m_pMainCamera->SetWorldSize(1000.f, 1000.f);

	LoadTexture();

	GET_SINGLE(CInput)->AddActionKey("AnimationEdit", VK_F1);
	GET_SINGLE(CInput)->AddBindAction("AnimationEdit", KEY_TYPE::DOWN, this, &CSceneAnimEdit::OnAnimationToolEditor);

	m_pMainCamera->SetResolution(1000.f, 1000.f);

	return true;
}

void CSceneAnimEdit::Start()
{
	CScene::Start();
}

void CSceneAnimEdit::LoadTexture()
{	
	// Game Sprite
	m_pResource->LoadTexture("Sprite", TEXT("Sprite.bmp"));
	m_pResource->SetColorKey("Sprite", 255, 0, 255);

	m_pResource->LoadTexture("Sprite2", TEXT("Sprite2.bmp"));
	m_pResource->SetColorKey("Sprite2", 255, 0, 255);
}

void CSceneAnimEdit::MoveUPDown(float fScale, float fTime)
{
	Vector2	vMove = Vector2(0.f, 500.f) * fScale * fTime;

	m_pMainCamera->Move(vMove);
}

void CSceneAnimEdit::MoveSide(float fScale, float fTime)
{
	Vector2	vMove = Vector2(500.f, 0.f) * fScale * fTime;

	m_pMainCamera->Move(vMove);
}

void CSceneAnimEdit::OnAnimationToolEditor(float fTime)
{
	if (!m_pAnimationToolDlg)
		m_pAnimationToolDlg = new CAnimationToolDlg;

	m_pAnimationToolDlg->OnDialog(IDD_DIALOG_ANIMATIONTOOL); // 다이얼로그의 ID를 넣고 창을 만들고 띄운다.
}

void CSceneAnimEdit::ReleaseAnimationSequence()
{
	m_pResource->ReleaseAnimationSequence();
}

void CSceneAnimEdit::DeleteAllObject()
{
	auto iter = m_UIList.begin();
	auto iterEnd = m_UIList.end();

	if (!m_UIList.empty())
	{
		for (; iter != iterEnd; ++iter)
		{
			(*iter)->Destroy();
		}
	}
}
