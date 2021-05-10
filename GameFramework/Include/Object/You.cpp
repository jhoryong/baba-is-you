#include "You.h"

#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/SceneStage.h"

CYou::CYou()
{
	m_eStateType = STATE_TYPE::YOU;
}

CYou::CYou(const CYou& obj) :
	CState(obj)
{
	m_eStateType = STATE_TYPE::YOU;
}

CYou::~CYou()
{
}

bool CYou::Init()
{
	CState::Init();
	
	CreateAnimation();

	AddAnimationSequence("You");
	AddAnimationSequence("You_Off");

	return true;
}

bool CYou::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CYou::Start()
{
	CState::Start();
}

void CYou::Update(float fTime)
{
	CState::Update(fTime);
}

void CYou::PostUpdate(float fTime)
{
	CState::PostUpdate(fTime);
}

void CYou::Collision(float fTime)
{
	CState::Collision(fTime);
}

void CYou::PrevRender(float fTime)
{
	CState::PrevRender(fTime); 

	if (!m_bMoving)
	{
		if (m_pScene->GetMoved() || m_pScene->GetInitialFrame())
		{
			if (m_bConnected)
			{
				ChangeAnimation("You");
				((CSceneStage*)m_pScene)->SetStuck(false);
			}

			else
			{
				ChangeAnimation("You_Off");
				((CSceneStage*)m_pScene)->SetStuck(true);
			}
		}
	}
}

void CYou::Render(HDC hDC, float fTime)
{
	CState::Render(hDC, fTime);
}

void CYou::PostRender(float fTime)
{
	CState::PostRender(fTime);
}

CYou* CYou::Clone()
{
	return new CYou(*this);
}