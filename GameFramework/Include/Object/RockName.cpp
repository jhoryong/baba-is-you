#include "RockName.h"

#include "Rock.h"
#include "../GameManager.h"

CRockName::CRockName()
{
	m_eNameType = NAME_TYPE::ROCK;
}

CRockName::CRockName(const CRockName& obj) :
	CName(obj)
{
	m_eNameType = NAME_TYPE::ROCK;
}

CRockName::~CRockName()
{
}

bool CRockName::Init()
{
	CName::Init();

	CreateAnimation();

	AddAnimationSequence("RockName");
	AddAnimationSequence("RockName_Off");

	return true;
}

bool CRockName::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CRockName::Start()
{
	CName::Start();
}

void CRockName::Update(float fTime)
{
	CName::Update(fTime);
}

void CRockName::PostUpdate(float fTime)
{
	CName::PostUpdate(fTime);
}

void CRockName::Collision(float fTime)
{
	CName::Collision(fTime);
}

void CRockName::PrevRender(float fTime)
{
	CName::PrevRender(fTime);

	if (!m_bMoving)
	{
		if (m_bConnected)
			ChangeAnimation("RockName");

		else
			ChangeAnimation("RockName_Off");
	}
}

void CRockName::Render(HDC hDC, float fTime)
{
	CName::Render(hDC, fTime);
	if (GET_SINGLE(CGameManager)->GetPrintInfo())
	{
		TCHAR   string[64] = { };

		if (m_bConnected)
		{
			_stprintf_s(string, TEXT("RockName : Connected"));
		}

		else
			_stprintf_s(string, TEXT("RockName: Not Nonnected"));

		TextOut(hDC, 0, 125, string, lstrlen(string));
	}
}

void CRockName::PostRender(float fTime)
{
	CName::PostRender(fTime);

}

CRockName* CRockName::Clone()
{
	return new CRockName(*this);
}