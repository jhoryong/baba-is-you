#include "SkullName.h"

#include "../GameManager.h"

CSkullName::CSkullName()
{
	m_eNameType = NAME_TYPE::SKULL;
}

CSkullName::CSkullName(const CSkullName& obj) :
	CName(obj)
{
	m_eNameType = NAME_TYPE::SKULL;
}

CSkullName::~CSkullName()
{
}

bool CSkullName::Init()
{
	CName::Init();

	CreateAnimation();

	AddAnimationSequence("SkullName");
	AddAnimationSequence("SkullName_Off");

	return true;
}

bool CSkullName::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CSkullName::Start()
{
	CName::Start();
}

void CSkullName::Update(float fTime)
{
	CName::Update(fTime);
}

void CSkullName::PostUpdate(float fTime)
{
	CName::PostUpdate(fTime);
}

void CSkullName::Collision(float fTime)
{
	CName::Collision(fTime);
}

void CSkullName::PrevRender(float fTime)
{
	CName::PrevRender(fTime);

	if (!m_bMoving)
	{
		if (m_bConnected)
			ChangeAnimation("SkullName");

		else
			ChangeAnimation("SkullName_Off");
	}
}

void CSkullName::Render(HDC hDC, float fTime)
{
	CName::Render(hDC, fTime);
	if (GET_SINGLE(CGameManager)->GetPrintInfo())
	{
		TCHAR   string[64] = { };

		if (m_bConnected)
		{
			_stprintf_s(string, TEXT("SkullName : Connected"));
		}

		else
			_stprintf_s(string, TEXT("SkullName: Not Nonnected"));

		TextOut(hDC, 0, 140, string, lstrlen(string));
	}
}

void CSkullName::PostRender(float fTime)
{
	CName::PostRender(fTime);

}

CSkullName* CSkullName::Clone()
{
	return new CSkullName(*this);
}