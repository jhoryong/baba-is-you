#include "Defeat.h"



CDefeat::CDefeat()
{
	m_eStateType = STATE_TYPE::DEFEAT;
}

CDefeat::CDefeat(const CDefeat& obj) :
	CState(obj)
{
	m_eStateType = STATE_TYPE::DEFEAT;
}

CDefeat::~CDefeat()
{
}

bool CDefeat::Init()
{
	CState::Init();

	CreateAnimation();

	AddAnimationSequence("Defeat");
	AddAnimationSequence("Defeat_Off");

	return true;
}

bool CDefeat::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CDefeat::Start()
{
	CState::Start();
}

void CDefeat::Update(float fTime)
{
	CState::Update(fTime);
}

void CDefeat::PostUpdate(float fTime)
{
	CState::PostUpdate(fTime);
}

void CDefeat::Collision(float fTime)
{
	CState::Collision(fTime);
}

void CDefeat::PrevRender(float fTime)
{
	CState::PrevRender(fTime);

	if (!m_bMoving)
	{
		if (m_bConnected)
			ChangeAnimation("Defeat");

		else
			ChangeAnimation("Defeat_Off");
	}

}

void CDefeat::Render(HDC hDC, float fTime)
{
	CState::Render(hDC, fTime);
}

void CDefeat::PostRender(float fTime)
{
	CState::PostRender(fTime);
}

CDefeat* CDefeat::Clone()
{
	return new CDefeat(*this);
}