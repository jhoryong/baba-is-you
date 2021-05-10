#include "LavaName2.h"

CLavaName2::CLavaName2()
{
	m_eNameType = NAME_TYPE::LAVA;
}

CLavaName2::CLavaName2(const CLavaName2& obj) :
	CName(obj)
{
	m_eNameType = NAME_TYPE::LAVA;
}

CLavaName2::~CLavaName2()
{
}

bool CLavaName2::Init()
{
	CName::Init();

	CreateAnimation();

	AddAnimationSequence("LavaName2");
	//AddAnimationSequence("SkullName_Off");

	return true;
}

bool CLavaName2::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CLavaName2::Start()
{
	CName::Start();
}

void CLavaName2::Update(float fTime)
{
	CName::Update(fTime);
}

void CLavaName2::PostUpdate(float fTime)
{
	CName::PostUpdate(fTime);
}

void CLavaName2::Collision(float fTime)
{
	CName::Collision(fTime);
}

void CLavaName2::PrevRender(float fTime)
{
	CName::PrevRender(fTime);

	/*if (!m_bMoving)
	{
		if (m_bConnected)
			ChangeAnimation("SkullName");

		else
			ChangeAnimation("SkullName_Off");
	}*/
}

void CLavaName2::Render(HDC hDC, float fTime)
{
	CName::Render(hDC, fTime);

	//TCHAR   string[64] = { };

	//if (m_bConnected)
	//{
	//	_stprintf_s(string, TEXT("SkullName : Connected"));
	//}

	//else
	//	_stprintf_s(string, TEXT("SkullName: Not Nonnected"));

	//TextOut(hDC, 0, 140, string, lstrlen(string));
}

void CLavaName2::PostRender(float fTime)
{
	CName::PostRender(fTime);
}

CLavaName2* CLavaName2::Clone()
{
	return new CLavaName2(*this);
}