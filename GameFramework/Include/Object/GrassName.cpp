#include "GrassName.h"


CGrassName::CGrassName()
{
	m_eNameType = NAME_TYPE::GRASS;
}

CGrassName::CGrassName(const CGrassName& obj) :
	CName(obj)
{
	m_eNameType = NAME_TYPE::GRASS;
}

CGrassName::~CGrassName()
{
}

bool CGrassName::Init()
{
	CName::Init();

	CreateAnimation();

	AddAnimationSequence("GrassName");
	//AddAnimationSequence("SkullName_Off");

	return true;
}

bool CGrassName::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CGrassName::Start()
{
	CName::Start();
}

void CGrassName::Update(float fTime)
{
	CName::Update(fTime);
}

void CGrassName::PostUpdate(float fTime)
{
	CName::PostUpdate(fTime);
}

void CGrassName::Collision(float fTime)
{
	CName::Collision(fTime);
}

void CGrassName::PrevRender(float fTime)
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

void CGrassName::Render(HDC hDC, float fTime)
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

void CGrassName::PostRender(float fTime)
{
	CName::PostRender(fTime);
}

CGrassName* CGrassName::Clone()
{
	return new CGrassName(*this);
}