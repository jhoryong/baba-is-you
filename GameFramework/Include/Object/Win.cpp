#include "Win.h"


CWin::CWin()
{
	m_eStateType = STATE_TYPE::WIN;
}

CWin::CWin(const CWin& obj) :
	CState(obj)
{
	m_eStateType = STATE_TYPE::WIN;
}

CWin::~CWin()
{
}

bool CWin::Init()
{
	CState::Init();

	CreateAnimation();

	AddAnimationSequence("Win");
	AddAnimationSequence("Win_Off");

	return true;
}

bool CWin::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CWin::Start()
{
	CState::Start();
}

void CWin::Update(float fTime)
{
	CState::Update(fTime);
}

void CWin::PostUpdate(float fTime)
{
	CState::PostUpdate(fTime);
}

void CWin::Collision(float fTime)
{
	CState::Collision(fTime);
}

void CWin::PrevRender(float fTime)
{
	CState::PrevRender(fTime);

	if (!m_bMoving)
	{
		if (m_bConnected)
			ChangeAnimation("Win");

		else
			ChangeAnimation("Win_Off");
	}
}

void CWin::Render(HDC hDC, float fTime)
{
	
	CState::Render(hDC, fTime);
}

void CWin::PostRender(float fTime)
{
	CState::PostRender(fTime);
}

CWin* CWin::Clone()
{
	return new CWin(*this);
}