#include "WallName.h"

#include "Wall.h"
#include "../GameManager.h"

CWallName::CWallName()
{
	m_eNameType = NAME_TYPE::WALL;
}

CWallName::CWallName(const CWallName& obj) :
	CName(obj)
{
	m_eNameType = NAME_TYPE::WALL;
}

CWallName::~CWallName()
{
}

bool CWallName::Init()
{
	CName::Init();

	CreateAnimation();

	AddAnimationSequence("WallName");
	AddAnimationSequence("WallName_Off");

	return true;
}

bool CWallName::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CWallName::Start()
{
	CName::Start();
}

void CWallName::Update(float fTime)
{
	CName::Update(fTime);
}

void CWallName::PostUpdate(float fTime)
{
	CName::PostUpdate(fTime);
}

void CWallName::Collision(float fTime)
{
	CName::Collision(fTime);
}

void CWallName::PrevRender(float fTime)
{
	CName::PrevRender(fTime);

	if (!m_bMoving)
	{
		if (m_bConnected)
			ChangeAnimation("WallName");

		else
			ChangeAnimation("WallName_Off");
	}
}

void CWallName::Render(HDC hDC, float fTime)
{
	CName::Render(hDC, fTime);
	if (GET_SINGLE(CGameManager)->GetPrintInfo())
	{
		TCHAR   string[64] = { };

		if (m_bConnected)
		{
			_stprintf_s(string, TEXT("WallName : Connected"));
		}

		else
			_stprintf_s(string, TEXT("WallName: Not Nonnected"));

		TextOut(hDC, 0, 110, string, lstrlen(string));
	}
}

void CWallName::PostRender(float fTime)
{
	CName::PostRender(fTime);
}

CWallName* CWallName::Clone()
{
	return new CWallName(*this);
}
