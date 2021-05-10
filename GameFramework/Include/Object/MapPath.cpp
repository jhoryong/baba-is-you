#include "MapPath.h"

CMapPath::CMapPath()
{
	m_eWordType = WORD_TYPE::MAP_PATH;
	m_bState[(int)STATE_TYPE::PUSH] = false;
	m_bNone = true;
	m_iZOrder = 0;
}

CMapPath::CMapPath(const CMapPath& obj) :
	CWord(obj)
{
	m_eWordType = WORD_TYPE::MAP_PATH;
	m_bState[(int)STATE_TYPE::PUSH] = false;
	m_iZOrder = 0;
	m_bNone = true;
	m_iNumber = obj.m_iNumber;
}

CMapPath::~CMapPath()
{
}

bool CMapPath::Init()
{
	CWord::Init();

	CreateAnimation();

	AddAnimationSequence("MapPath_0");
	AddAnimationSequence("MapPath_1");

	return true;
}

bool CMapPath::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CMapPath::Start()
{
	CWord::Start();

	NumberTexture();
}

void CMapPath::Update(float fTime)
{
	CWord::Update(fTime);
}

void CMapPath::PostUpdate(float fTime)
{
	CWord::PostUpdate(fTime);
}

void CMapPath::Collision(float fTime)
{
	CWord::Collision(fTime);
}

void CMapPath::PrevRender(float fTime)
{
	CWord::PrevRender(fTime);
}

void CMapPath::Render(HDC hDC, float fTime)
{
	CWord::Render(hDC, fTime);

	//TCHAR   string[64] = { };

	//if (m_bNone)
	//	_stprintf_s(string, TEXT("NONE STATE"));

	//else
	//	_stprintf_s(string, TEXT("NOT NONE STATE"));

	//TextOut(hDC, 0, 75, string, lstrlen(string));
}

void CMapPath::PostRender(float fTime)
{
	CWord::PostRender(fTime);
}

CMapPath* CMapPath::Clone()
{
	return new CMapPath(*this);
}


void CMapPath::NumberTexture()
{
	switch (m_iNumber)
	{
	case 0:
		ChangeAnimation("MapPath_0");
		break;
	case 1:
		ChangeAnimation("MapPath_1");
		break;
	}
}
