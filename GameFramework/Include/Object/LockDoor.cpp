#include "LockDoor.h"


CLockDoor::CLockDoor()
{
	m_eCharacterType = CHARACTER_TYPE::LOCKDOOR;
	memset(m_bState, false, sizeof(bool) * (int)STATE_TYPE::END);
	m_bNone = true;
}

CLockDoor::CLockDoor(const CLockDoor& obj) :
	CCharacter(obj)
{
	m_eCharacterType = CHARACTER_TYPE::LOCKDOOR;
	memset(m_bState, false, sizeof(bool) * (int)STATE_TYPE::END);
	m_bNone = true;
}

CLockDoor::~CLockDoor()
{
}

bool CLockDoor::Init()
{
	CCharacter::Init();

	CreateAnimation();
	AddAnimationSequence("LockDoor");

	return true;
}

bool CLockDoor::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CLockDoor::Start()
{
	CCharacter::Start();
}

void CLockDoor::Update(float fTime)
{
	CCharacter::Update(fTime);
}

void CLockDoor::PostUpdate(float fTime)
{
	CCharacter::PostUpdate(fTime);
}

void CLockDoor::Collision(float fTime)
{
	CCharacter::Collision(fTime);
}

void CLockDoor::PrevRender(float fTime)
{
	CCharacter::PrevRender(fTime);
}

void CLockDoor::Render(HDC hDC, float fTime)
{
	CCharacter::Render(hDC, fTime);
}

void CLockDoor::PostRender(float fTime)
{
	CCharacter::PostRender(fTime);
}

CLockDoor* CLockDoor::Clone()
{
	return new CLockDoor(*this);
}