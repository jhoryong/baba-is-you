#include "Star.h"



CStar::CStar()
{
	m_eCharacterType = CHARACTER_TYPE::STAR;
	memset(m_bState, false, sizeof(bool) * (int)STATE_TYPE::END);
	m_bNone = true;
}

CStar::CStar(const CStar& obj) :
	CCharacter(obj)
{
	m_eCharacterType = CHARACTER_TYPE::STAR;
	memset(m_bState, false, sizeof(bool) * (int)STATE_TYPE::END);
	m_bNone = true;
}

CStar::~CStar()
{
}

bool CStar::Init()
{
	CCharacter::Init();

	CreateAnimation();
	AddAnimationSequence("Star");

	return true;
}

bool CStar::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CStar::Start()
{
	CCharacter::Start();
}

void CStar::Update(float fTime)
{
	CCharacter::Update(fTime);
}

void CStar::PostUpdate(float fTime)
{
	CCharacter::PostUpdate(fTime);
}

void CStar::Collision(float fTime)
{
	CCharacter::Collision(fTime);
}

void CStar::PrevRender(float fTime)
{
	CCharacter::PrevRender(fTime);
}

void CStar::Render(HDC hDC, float fTime)
{
	CCharacter::Render(hDC, fTime);
}

void CStar::PostRender(float fTime)
{
	CCharacter::PostRender(fTime);
}

CStar* CStar::Clone()
{
	return new CStar(*this);
}