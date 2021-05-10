#include "Melt.h"


CMelt::CMelt()
{
	m_eStateType = STATE_TYPE::MELT;
}

CMelt::CMelt(const CMelt& obj) :
	CState(obj)
{
	m_eStateType = STATE_TYPE::MELT;
}

CMelt::~CMelt()
{
}

bool CMelt::Init()
{
	CState::Init();

	CreateAnimation();

	AddAnimationSequence("Melt");
	//AddAnimationSequence("Defeat_Off");

	return true;
}

bool CMelt::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CMelt::Start()
{
	CState::Start();
}

void CMelt::Update(float fTime)
{
	CState::Update(fTime);
}

void CMelt::PostUpdate(float fTime)
{
	CState::PostUpdate(fTime);
}

void CMelt::Collision(float fTime)
{
	CState::Collision(fTime);
}

void CMelt::PrevRender(float fTime)
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

void CMelt::Render(HDC hDC, float fTime)
{
	CState::Render(hDC, fTime);
}

void CMelt::PostRender(float fTime)
{
	CState::PostRender(fTime);
}

CMelt* CMelt::Clone()
{
	return new CMelt(*this);
}