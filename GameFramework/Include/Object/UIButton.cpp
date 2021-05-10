#include "UIButton.h"
#include "../Input.h"
#include "../Collider/ColliderRect.h"
#include "../Collider/ColliderSphere.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CUIButton::CUIButton()	:
	m_bMouseCollision(false),
	m_bMouseDown(false),
	m_bMousePush(false),
	m_bMouseUp(false),
	m_bClick(false)
{
}

CUIButton::~CUIButton()
{
}

bool CUIButton::Init()
{
	if (!CUI::Init())
		return false;

	((CColliderRect*)m_pBody)->SetRectInfo(0.f, 0.f, 200.f, 100.f);

	m_pBody->SetMouseCollisionCallback<CUIButton>(COLLISION_STATE::BEGIN,
		this, &CUIButton::CollisionBegin);
	m_pBody->SetMouseCollisionCallback<CUIButton>(COLLISION_STATE::END,
		this, &CUIButton::CollisionEnd);

	m_strAnimationName[(int)BUTTON_STATE::NORMAL] = "ButtonNormal";
	m_strAnimationName[(int)BUTTON_STATE::MOUSEON] = "ButtonMouseOn";
	m_strAnimationName[(int)BUTTON_STATE::CLICK] = "ButtonClick";

	return true;
}

bool CUIButton::Init(const char* pFileName, const string& strPathName)
{
	if (!CUI::Init(pFileName, strPathName))
		return false;

	return true;
}

void CUIButton::Start()
{
	CUI::Start();
}

void CUIButton::Update(float fTime)
{
	CUI::Update(fTime);

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!m_bMouseDown && !m_bMousePush)
		{
			m_bMouseDown = true;
			m_bMousePush = true;

			if (m_bMouseCollision)
			{
				if (!m_strEventSoundName[(int)BUTTON_STATE::CLICK].empty())
				{
					size_t ElementCount = m_strEventSoundName[(int)BUTTON_STATE::CLICK].size();
					size_t iRand = rand() % ElementCount;
					m_pScene->GetSceneResource()->SoundPlay(m_strEventSoundName[(int)BUTTON_STATE::CLICK][iRand]);
				}
			}
		}

		else
		{
			m_bMouseDown = false;
		}
	}

	else if (m_bMousePush)
	{
		m_bMouseUp = true;
		m_bMousePush = false;
		m_bMouseDown = false;
	}

	else
		m_bMouseUp = false;

	if (m_bMouseCollision)
	{
		if (m_bMouseDown)
			m_bClick = true;

		if (m_bClick)
		{
			ChangeAnimation(m_strAnimationName[(int)BUTTON_STATE::CLICK]);

			// 버튼 콜백 활성화
			if (m_bMouseUp)
			{
				m_bClick = false;

				if (m_ClickCallback)
					m_ClickCallback(fTime);
			}
		}

		else
		{
			ChangeAnimation(m_strAnimationName[(int)BUTTON_STATE::MOUSEON]);
		}
	}

	else
	{
		m_bClick = false;
		ChangeAnimation(m_strAnimationName[(int)BUTTON_STATE::NORMAL]);
		if (!m_strEventSoundName[(int)BUTTON_STATE::NORMAL].empty())
		{
			size_t ElementCount = m_strEventSoundName[(int)BUTTON_STATE::NORMAL].size();
			size_t iRand = rand() % ElementCount;
			m_pScene->GetSceneResource()->SoundPlay(m_strEventSoundName[(int)BUTTON_STATE::NORMAL][iRand]);
		}
	}
}

void CUIButton::PostUpdate(float fTime)
{
	CUI::PostUpdate(fTime);
}

void CUIButton::Collision(float fTime)
{
	CUI::Collision(fTime);
}

void CUIButton::PrevRender(float fTime)
{
	CUI::PrevRender(fTime);
}

void CUIButton::Render(HDC hDC, float fTime)
{
	CUI::Render(hDC, fTime);
}

void CUIButton::PostRender(float fTime)
{
	CUI::PostRender(fTime);
}

CUIButton* CUIButton::Clone()
{
	return new CUIButton(*this);
}

void CUIButton::ChangeCollider(COLLIDER_TYPE eType)
{
	CUI::ChangeCollider(eType);

	if (m_pBody)
	{
		m_pBody->SetMouseCollisionCallback<CUIButton>(COLLISION_STATE::BEGIN,
			this, &CUIButton::CollisionBegin);
		m_pBody->SetMouseCollisionCallback<CUIButton>(COLLISION_STATE::END,
			this, &CUIButton::CollisionEnd);
	}
}

void CUIButton::AddAnimation(BUTTON_STATE eState, const string& strName)
{
	m_strAnimationName[(int)eState] = strName;
	AddAnimationSequence(strName);
}

void CUIButton::SetEventSound(BUTTON_STATE eState, const string& strName)
{
	m_strEventSoundName[(int)eState].push_back(strName);
}

void CUIButton::CollisionBegin(CCollider* pSrc,
	const Vector2& vMousePos, float fTime)
{
	m_bMouseCollision = true;

	if (!m_strEventSoundName[(int)BUTTON_STATE::MOUSEON].empty())
	{
		size_t ElementCount = m_strEventSoundName[(int)BUTTON_STATE::MOUSEON].size();
		size_t iRand = rand() % ElementCount;
		m_pScene->GetSceneResource()->SoundPlay(m_strEventSoundName[(int)BUTTON_STATE::MOUSEON][iRand]);
	}
}

void CUIButton::CollisionEnd(CCollider* pSrc, 
	const Vector2& vMousePos, float fTime)
{
	m_bMouseCollision = false;
}

void CUIButton::SetClickCallback(void(*pFunc)(float))
{
	m_ClickCallback = bind(pFunc, placeholders::_1);
}
