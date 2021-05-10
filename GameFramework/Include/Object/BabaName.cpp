#include "BabaName.h"

#include "Baba.h"
#include "../GameManager.h"

CBabaName::CBabaName()
{
	m_eNameType = NAME_TYPE::BABA;
}

CBabaName::CBabaName(const CBabaName& obj) :
	CName(obj)
{
	m_eNameType = NAME_TYPE::BABA;
}

CBabaName::~CBabaName()
{
}

bool CBabaName::Init()
{
	CName::Init();

	CreateAnimation();

	AddAnimationSequence("BabaName");
	AddAnimationSequence("BabaName_Off");

	return true;
}

bool CBabaName::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CBabaName::Start()
{
	CName::Start();
}

void CBabaName::Update(float fTime)
{
	CName::Update(fTime);
}

void CBabaName::PostUpdate(float fTime)
{
	CName::PostUpdate(fTime);
}

void CBabaName::Collision(float fTime)
{
	CName::Collision(fTime);
}

void CBabaName::PrevRender(float fTime)
{
	CName::PrevRender(fTime); 
	
	if (!m_bMoving)
	{
		if (m_bConnected)
			ChangeAnimation("BabaName");

		else
			ChangeAnimation("BabaName_Off");
	}
}

void CBabaName::Render(HDC hDC, float fTime)
{
	CName::Render(hDC, fTime);
	if (GET_SINGLE(CGameManager)->GetPrintInfo())
	{
		TCHAR   string[64] = { };

		if (m_bConnected)
		{
			_stprintf_s(string, TEXT("BabaName : Connected"));
		}

		else
			_stprintf_s(string, TEXT("BabaName: Not Nonnected"));

		TextOut(hDC, 0, 80, string, lstrlen(string));
	}
}

void CBabaName::PostRender(float fTime)
{
	CName::PostRender(fTime);
}

CBabaName* CBabaName::Clone()
{
	return new CBabaName(*this);
}
