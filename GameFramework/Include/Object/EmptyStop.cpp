#include "EmptyStop.h"

#include "../Input.h"
#include "../Scene/Scene.h"

CEmptyStop::CEmptyStop()
{
	m_eCharacterType = CHARACTER_TYPE::EMPTY_STOP;
	m_bState[(int)STATE_TYPE::STOP] = true;
}

CEmptyStop::CEmptyStop(const CEmptyStop& obj) :
	CCharacter(obj)
{
	m_eCharacterType = CHARACTER_TYPE::EMPTY_STOP;
}

CEmptyStop::~CEmptyStop()
{
}

bool CEmptyStop::Init()
{
	CCharacter::Init();

	return true;
}

bool CEmptyStop::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CEmptyStop::Start()
{
	CCharacter::Start();
}

void CEmptyStop::Update(float fTime)
{
	CCharacter::Update(fTime);
}

void CEmptyStop::PostUpdate(float fTime)
{
	CCharacter::PostUpdate(fTime);
}

void CEmptyStop::Collision(float fTime)
{
	CCharacter::Collision(fTime);
}

void CEmptyStop::PrevRender(float fTime)
{
	CCharacter::PrevRender(fTime);
}

void CEmptyStop::Render(HDC hDC, float fTime)
{
	CCharacter::Render(hDC, fTime);
}

void CEmptyStop::PostRender(float fTime)
{
	CCharacter::PostRender(fTime);
}

CEmptyStop* CEmptyStop::Clone()
{
	return new CEmptyStop(*this);
}