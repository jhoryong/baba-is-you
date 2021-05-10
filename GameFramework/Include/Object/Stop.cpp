#include "Stop.h"


CStop::CStop()
{
	m_eStateType = STATE_TYPE::STOP;
}

CStop::CStop(const CStop& obj) :
	CState(obj)
{
	m_eStateType = STATE_TYPE::STOP;
}

CStop::~CStop()
{
}

bool CStop::Init()
{
	CState::Init();

	CreateAnimation();

	AddAnimationSequence("Stop");
	AddAnimationSequence("Stop_Off");

	return true;
}

bool CStop::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CStop::Start()
{
	CState::Start();
}

void CStop::Update(float fTime)
{
	CState::Update(fTime);
}

void CStop::PostUpdate(float fTime)
{
	CState::PostUpdate(fTime);
}

void CStop::Collision(float fTime)
{
	CState::Collision(fTime);
}

void CStop::PrevRender(float fTime)
{
	CState::PrevRender(fTime);
	if (!m_bMoving)
	{
		if (m_bConnected)
			ChangeAnimation("Stop");

		else
			ChangeAnimation("Stop_Off");
	}
}

void CStop::Render(HDC hDC, float fTime)
{
	
	CState::Render(hDC, fTime);
}

void CStop::PostRender(float fTime)
{
	CState::PostRender(fTime);
}

CStop* CStop::Clone()
{
	return new CStop(*this);
}