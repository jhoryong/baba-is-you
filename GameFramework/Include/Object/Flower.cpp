#include "Flower.h"



CFlower::CFlower()
{
	m_eCharacterType = CHARACTER_TYPE::FLOWER;
	memset(m_bState, false, sizeof(bool) * (int)STATE_TYPE::END);
	m_bNone = true;
}

CFlower::CFlower(const CFlower& obj) :
	CCharacter(obj)
{
	m_eCharacterType = CHARACTER_TYPE::FLOWER;
	memset(m_bState, false, sizeof(bool) * (int)STATE_TYPE::END);
	m_bNone = true;
}

CFlower::~CFlower()
{
}

bool CFlower::Init()
{
	CCharacter::Init();

	CreateAnimation();
	AddAnimationSequence("Flower");

	return true;
}

bool CFlower::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CFlower::Start()
{
	CCharacter::Start();
}

void CFlower::Update(float fTime)
{
	CCharacter::Update(fTime);
}

void CFlower::PostUpdate(float fTime)
{
	CCharacter::PostUpdate(fTime);
}

void CFlower::Collision(float fTime)
{
	CCharacter::Collision(fTime);
}

void CFlower::PrevRender(float fTime)
{
	CCharacter::PrevRender(fTime);
}

void CFlower::Render(HDC hDC, float fTime)
{
	CCharacter::Render(hDC, fTime);
}

void CFlower::PostRender(float fTime)
{
	CCharacter::PostRender(fTime);
}

CFlower* CFlower::Clone()
{
	return new CFlower(*this);
}