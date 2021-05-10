#include "UIBaba.h"
#include "../Input.h"
#include "../Collider/ColliderRect.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/SceneStart.h"

CUIBaba::CUIBaba()
{
}

CUIBaba::~CUIBaba()
{
	GET_SINGLE(CInput)->DeleteBindAction("MenuMoveUp");
	GET_SINGLE(CInput)->DeleteBindAction("MenuMoveDown");
	GET_SINGLE(CInput)->DeleteBindAction("MenuKeyboardSelect");
}

bool CUIBaba::Init()
{
	if (!CUI::Init())
		return false;

	((CColliderRect*)m_pBody)->SetRectInfo(0.f, -12.f, 24.f, 12.f);

	return true;
}

bool CUIBaba::Init(const char* pFileName, const string& strPathName)
{
	if (!CUI::Init(pFileName, strPathName))
		return false;


	return true;
}

void CUIBaba::Start()
{
	CUI::Start();

	GET_SINGLE(CInput)->AddActionKey("MenuMoveUp", VK_UP);
	GET_SINGLE(CInput)->AddBindAction("MenuMoveUp", KEY_TYPE::DOWN, this, &CUIBaba::MoveUp);
	GET_SINGLE(CInput)->AddBindAction("MenuMoveUp", KEY_TYPE::ON, this, &CUIBaba::MoveUpOn);
	GET_SINGLE(CInput)->AddBindAction("MenuMoveUp", KEY_TYPE::UP, this, &CUIBaba::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("MenuMoveDown", VK_DOWN);
	GET_SINGLE(CInput)->AddBindAction("MenuMoveDown", KEY_TYPE::DOWN, this, &CUIBaba::MoveDown);
	GET_SINGLE(CInput)->AddBindAction("MenuMoveDown", KEY_TYPE::ON, this, &CUIBaba::MoveDownOn);
	GET_SINGLE(CInput)->AddBindAction("MenuMoveDown", KEY_TYPE::UP, this, &CUIBaba::MoveEnd);

	GET_SINGLE(CInput)->AddActionKey("MenuKeyboardSelect", VK_RETURN);
	GET_SINGLE(CInput)->AddBindAction("MenuKeyboardSelect", KEY_TYPE::DOWN, this, &CUIBaba::MenuKeyboardSelect);
}

void CUIBaba::Update(float fTime)
{
	//CUI::Update(fTime);
	CObj::Update(fTime);
}

void CUIBaba::PostUpdate(float fTime)
{
	CUI::PostUpdate(fTime);
}

void CUIBaba::Collision(float fTime)
{
	CUI::Collision(fTime);
}

void CUIBaba::PrevRender(float fTime)
{
	CUI::PrevRender(fTime);
}

void CUIBaba::Render(HDC hDC, float fTime)
{
	CUI::Render(hDC, fTime);
}

void CUIBaba::PostRender(float fTime)
{
	CUI::PostRender(fTime);
}

CUIBaba* CUIBaba::Clone()
{
	return new CUIBaba(*this);
}

void CUIBaba::AddAnimation(const string& strName)
{
	m_strAnimationName = strName;
	AddAnimationSequence(strName);
}

void CUIBaba::MoveUp(float fTime)
{
	if (m_vPos.y <= 318.f)
	{
		m_vPos.y = 390.f;
	}
	else
		m_vPos.y -= 24.f;

	PlayButtonSound();
}

void CUIBaba::MoveUpOn(float fTime)
{
	m_fWaitAcc += fTime;

	if (m_fWaitAcc >= m_fWait)
	{
		m_fWaitAcc -= m_fWait;

		MoveUp(fTime);
	}
}

void CUIBaba::MoveEnd(float fTime)
{
	m_fWaitAcc = 0.f;
}

void CUIBaba::MoveDown(float fTime)
{
	if (m_vPos.y >= 390.f)
	{
		m_vPos.y = 318.f;
	}
	else
		m_vPos.y += 24.f;

	PlayButtonSound();
}

void CUIBaba::MoveDownOn(float fTime)
{
	m_fWaitAcc += fTime;

	if (m_fWaitAcc >= m_fWait)
	{
		m_fWaitAcc -= m_fWait;

		MoveDown(fTime);
	}
}

void CUIBaba::MenuKeyboardSelect(float fTime)
{
	switch ((int)m_vPos.y)
	{
	case 318:
		((CSceneStart*)m_pScene)->SetGameEnter(fTime);
		break;
	case 342:
		((CSceneStart*)m_pScene)->Edit(fTime);
		break;
	case 366:
		((CSceneStart*)m_pScene)->AnimEdit(fTime);
		break;
	case 390:
		((CSceneStart*)m_pScene)->Exit(fTime);
		break;
	}
}

void CUIBaba::PlayButtonSound()
{
	int iRand = rand() % 6;

	switch (iRand)
	{
	case 0:
		m_pScene->GetSceneResource()->SoundPlay("ButtonHover_0");
		break;
	case 1:
		m_pScene->GetSceneResource()->SoundPlay("ButtonHover_1");
		break;
	case 2:
		m_pScene->GetSceneResource()->SoundPlay("ButtonHover_2");
		break;
	case 3:
		m_pScene->GetSceneResource()->SoundPlay("ButtonHover_3");
		break;
	case 4:
		m_pScene->GetSceneResource()->SoundPlay("ButtonHover_4");
		break;
	case 5:
		m_pScene->GetSceneResource()->SoundPlay("ButtonHover_5");
		break;
	}
}

