#include "Rocket.h"



CRocket::CRocket()
{
	m_eCharacterType = CHARACTER_TYPE::ROCKET;
	memset(m_bState, false, sizeof(bool) * (int)STATE_TYPE::END);
	m_bNone = true;
}

CRocket::CRocket(const CRocket& obj) :
	CCharacter(obj)
{
	m_eCharacterType = CHARACTER_TYPE::ROCKET;
	memset(m_bState, false, sizeof(bool) * (int)STATE_TYPE::END);
	m_bNone = true;
}

CRocket::~CRocket()
{
}

bool CRocket::Init()
{
	CCharacter::Init();

	CreateAnimation();
	AddAnimationSequence("Rocket");

	return true;
}

bool CRocket::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CRocket::Start()
{
	CCharacter::Start();
}

void CRocket::Update(float fTime)
{
	CCharacter::Update(fTime);
}

void CRocket::PostUpdate(float fTime)
{
	CCharacter::PostUpdate(fTime);
}

void CRocket::Collision(float fTime)
{
	CCharacter::Collision(fTime);
}

void CRocket::PrevRender(float fTime)
{
	CCharacter::PrevRender(fTime);
}

void CRocket::Render(HDC hDC, float fTime)
{
	CCharacter::Render(hDC, fTime);
}

void CRocket::PostRender(float fTime)
{
	CCharacter::PostRender(fTime);
}

CRocket* CRocket::Clone()
{
	return new CRocket(*this);
}