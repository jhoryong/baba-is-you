#include "LavaName.h"


CLavaName::CLavaName()
{
	m_eNameType = NAME_TYPE::LAVA;
}

CLavaName::CLavaName(const CLavaName& obj) :
	CName(obj)
{
	m_eNameType = NAME_TYPE::LAVA;
}

CLavaName::~CLavaName()
{
}

bool CLavaName::Init()
{
	CName::Init();

	CreateAnimation();

	AddAnimationSequence("LavaName");
	//AddAnimationSequence("SkullName_Off");

	return true;
}

bool CLavaName::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CLavaName::Start()
{
	CName::Start();
}

void CLavaName::Update(float fTime)
{
	CName::Update(fTime);
}

void CLavaName::PostUpdate(float fTime)
{
	CName::PostUpdate(fTime);
}

void CLavaName::Collision(float fTime)
{
	CName::Collision(fTime);
}

void CLavaName::PrevRender(float fTime)
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

void CLavaName::Render(HDC hDC, float fTime)
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

void CLavaName::PostRender(float fTime)
{
	CName::PostRender(fTime);
}

CLavaName* CLavaName::Clone()
{
	return new CLavaName(*this);
}