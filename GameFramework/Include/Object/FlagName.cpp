#include "FlagName.h"

#include "Flag.h"
#include "../GameManager.h"

CFlagName::CFlagName()
{
	m_eNameType = NAME_TYPE::FLAG;
}

CFlagName::CFlagName(const CFlagName& obj) :
	CName(obj)
{
	m_eNameType = NAME_TYPE::FLAG;
}

CFlagName::~CFlagName()
{
}

bool CFlagName::Init()
{
	CName::Init();

	CreateAnimation();

	AddAnimationSequence("FlagName");
	AddAnimationSequence("FlagName_Off");

	return true;
}

bool CFlagName::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CFlagName::Start()
{
	CName::Start();
}

void CFlagName::Update(float fTime)
{
	CName::Update(fTime);
}

void CFlagName::PostUpdate(float fTime)
{
	CName::PostUpdate(fTime);
}

void CFlagName::Collision(float fTime)
{
	CName::Collision(fTime);
}

void CFlagName::PrevRender(float fTime)
{
	CName::PrevRender(fTime);

	if (!m_bMoving)
	{
		if (m_bConnected)
			ChangeAnimation("FlagName");

		else
			ChangeAnimation("FlagName_Off");
	}
}

void CFlagName::Render(HDC hDC, float fTime)
{
	CName::Render(hDC, fTime);
	if (GET_SINGLE(CGameManager)->GetPrintInfo())
	{
		TCHAR   string[64] = { };

		if (m_bConnected)
		{
			_stprintf_s(string, TEXT("FlagName : Connected"));
		}

		else
			_stprintf_s(string, TEXT("FlagName: Not Nonnected"));

		TextOut(hDC, 0, 95, string, lstrlen(string));
	}
}

void CFlagName::PostRender(float fTime)
{
	CName::PostRender(fTime);
}

CFlagName* CFlagName::Clone()
{
	return new CFlagName(*this);
}
