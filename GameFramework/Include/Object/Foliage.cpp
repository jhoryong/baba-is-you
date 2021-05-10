#include "Foliage.h"


CFoliage::CFoliage()
{
	m_eCharacterType = CHARACTER_TYPE::FOLIAGE;
	memset(m_bState, false, sizeof(bool) * (int)STATE_TYPE::END);
	m_bNone = true;
}

CFoliage::CFoliage(const CFoliage& obj) :
	CCharacter(obj)
{
	m_eCharacterType = CHARACTER_TYPE::FOLIAGE;
	memset(m_bState, false, sizeof(bool) * (int)STATE_TYPE::END);
	m_bNone = true;
}

CFoliage::~CFoliage()
{
}

bool CFoliage::Init()
{
	CCharacter::Init();

	CreateAnimation();
	AddAnimationSequence("Foliage");

	return true;
}

bool CFoliage::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CFoliage::Start()
{
	CCharacter::Start();
}

void CFoliage::Update(float fTime)
{
	CCharacter::Update(fTime);
}

void CFoliage::PostUpdate(float fTime)
{
	CCharacter::PostUpdate(fTime);
}

void CFoliage::Collision(float fTime)
{
	CCharacter::Collision(fTime);
}

void CFoliage::PrevRender(float fTime)
{
	CCharacter::PrevRender(fTime);
}

void CFoliage::Render(HDC hDC, float fTime)
{
	CCharacter::Render(hDC, fTime);
}

void CFoliage::PostRender(float fTime)
{
	CCharacter::PostRender(fTime);
}

CFoliage* CFoliage::Clone()
{
	return new CFoliage(*this);
}