#include "Fungi.h"


CFungi::CFungi()
{
	m_eCharacterType = CHARACTER_TYPE::FUNGI;
	memset(m_bState, false, sizeof(bool) * (int)STATE_TYPE::END);
	m_bNone = true;
}

CFungi::CFungi(const CFungi& obj) :
	CCharacter(obj)
{
	m_eCharacterType = CHARACTER_TYPE::FUNGI;
	memset(m_bState, false, sizeof(bool) * (int)STATE_TYPE::END);
	m_bNone = true;
}

CFungi::~CFungi()
{
}

bool CFungi::Init()
{
	CCharacter::Init();

	CreateAnimation();
	AddAnimationSequence("Fungi");

	return true;
}

bool CFungi::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CFungi::Start()
{
	CCharacter::Start();
}

void CFungi::Update(float fTime)
{
	CCharacter::Update(fTime);
}

void CFungi::PostUpdate(float fTime)
{
	CCharacter::PostUpdate(fTime);
}

void CFungi::Collision(float fTime)
{
	CCharacter::Collision(fTime);
}

void CFungi::PrevRender(float fTime)
{
	CCharacter::PrevRender(fTime);
}

void CFungi::Render(HDC hDC, float fTime)
{
	CCharacter::Render(hDC, fTime);
}

void CFungi::PostRender(float fTime)
{
	CCharacter::PostRender(fTime);
}

CFungi* CFungi::Clone()
{
	return new CFungi(*this);
}