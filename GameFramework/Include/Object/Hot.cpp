#include "Hot.h"


CHot::CHot()
{
	m_eStateType = STATE_TYPE::HOT;
}

CHot::CHot(const CHot& obj) :
	CState(obj)
{
	m_eStateType = STATE_TYPE::HOT;
}

CHot::~CHot()
{
}

bool CHot::Init()
{
	CState::Init();

	CreateAnimation();

	AddAnimationSequence("Hot");
	//AddAnimationSequence("Defeat_Off");

	return true;
}

bool CHot::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CHot::Start()
{
	CState::Start();
}

void CHot::Update(float fTime)
{
	CState::Update(fTime);
}

void CHot::PostUpdate(float fTime)
{
	CState::PostUpdate(fTime);
}

void CHot::Collision(float fTime)
{
	CState::Collision(fTime);
}

void CHot::PrevRender(float fTime)
{
	CState::PrevRender(fTime);

	if (!m_bMoving)
	{
		//if (m_bConnected)
		//	ChangeAnimation("Defeat");

		//else
		//	ChangeAnimation("Defeat_Off");
	}

}

void CHot::Render(HDC hDC, float fTime)
{
	CState::Render(hDC, fTime);
}

void CHot::PostRender(float fTime)
{
	CState::PostRender(fTime);
}

CHot* CHot::Clone()
{
	return new CHot(*this);
}