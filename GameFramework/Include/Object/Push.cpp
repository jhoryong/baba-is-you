#include "Push.h"


CPush::CPush()
{
	m_eStateType = STATE_TYPE::PUSH;
}

CPush::CPush(const CPush& obj) :
	CState(obj)
{
	m_eStateType = STATE_TYPE::PUSH;
}

CPush::~CPush()
{
}

bool CPush::Init()
{
	CState::Init();

	CreateAnimation();

	AddAnimationSequence("Push");
	AddAnimationSequence("Push_Off");

	return true;
}

bool CPush::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CPush::Start()
{
	CState::Start();
}

void CPush::Update(float fTime)
{
	CState::Update(fTime);
}

void CPush::PostUpdate(float fTime)
{
	CState::PostUpdate(fTime);
}

void CPush::Collision(float fTime)
{
	CState::Collision(fTime);
}

void CPush::PrevRender(float fTime)
{
	CState::PrevRender(fTime); 
	
	if (!m_bMoving)
	{
		if (m_bConnected)
			ChangeAnimation("Push");

		else
			ChangeAnimation("Push_Off");
	}

}

void CPush::Render(HDC hDC, float fTime)
{
	CState::Render(hDC, fTime);
}

void CPush::PostRender(float fTime)
{
	CState::PostRender(fTime);
}

CPush* CPush::Clone()
{
	return new CPush(*this);
}