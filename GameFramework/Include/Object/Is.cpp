#include "Is.h"


CIs::CIs()
{
	m_eConnectType = CONNECT_TYPE::IS;
}

CIs::CIs(const CIs& obj) :
	CConnect(obj)
{
	m_eConnectType = CONNECT_TYPE::IS;
}

CIs::~CIs()
{
}

bool CIs::Init()
{
	CConnect::Init();

	CreateAnimation();

	AddAnimationSequence("Is");
	AddAnimationSequence("Is_Off");

	return true;
}

bool CIs::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CIs::Start()
{
	CConnect::Start();
}

void CIs::Update(float fTime)
{
	CConnect::Update(fTime);
}

void CIs::PostUpdate(float fTime)
{
	CConnect::PostUpdate(fTime);
}

void CIs::Collision(float fTime)
{
	CConnect::Collision(fTime);
}

void CIs::PrevRender(float fTime)
{
	CConnect::PrevRender(fTime);

	if (!m_bMoving)
	{
		if (m_bConnected)
			ChangeAnimation("Is");

		else
			ChangeAnimation("Is_Off");
	}
}

void CIs::Render(HDC hDC, float fTime)
{
	CConnect::Render(hDC, fTime);
}

void CIs::PostRender(float fTime)
{
	CConnect::PostRender(fTime);

}

CIs* CIs::Clone()
{
	return new CIs(*this);
}