#include "Number.h"

#include "../Scene/SceneManager.h"

CNumber::CNumber()
{
	m_eWordType = WORD_TYPE::NUMBER; 
	m_bState[(int)STATE_TYPE::PUSH] = false;
	m_bNone = true;
	m_iZOrder = 0;
}

CNumber::CNumber(const CNumber& obj) :
	CWord(obj)
{
	m_iNumber = obj.m_iNumber;
	m_eWordType = WORD_TYPE::NUMBER;
	m_bState[(int)STATE_TYPE::PUSH] = false;
	m_bNone = true;
	m_iZOrder = 0;
}

CNumber::~CNumber()
{
}

bool CNumber::Init()
{
	CWord::Init();
	CreateAnimation();
	AddAnimationSequence("Level00");
	AddAnimationSequence("Level01");
	AddAnimationSequence("Level02");
	AddAnimationSequence("Level03");
	AddAnimationSequence("Level04");
	AddAnimationSequence("Level05");
	AddAnimationSequence("Level06");
	AddAnimationSequence("Level07");

	AddAnimationSequence("Level00_Clear");
	AddAnimationSequence("Level01_Clear");
	AddAnimationSequence("Level02_Clear");
	AddAnimationSequence("Level03_Clear");
	AddAnimationSequence("Level04_Clear");
	AddAnimationSequence("Level05_Clear");
	AddAnimationSequence("Level06_Clear");
	AddAnimationSequence("Level07_Clear");

	return true;
}

bool CNumber::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CNumber::Start()
{
	CWord::Start();

	ChangeNumberAnimation();
}

void CNumber::Update(float fTime)
{
	CWord::Update(fTime);
}

void CNumber::PostUpdate(float fTime)
{
	CWord::PostUpdate(fTime);
}

void CNumber::Collision(float fTime)
{
	CWord::Collision(fTime);
}

void CNumber::PrevRender(float fTime)
{
	CWord::PrevRender(fTime);
}

void CNumber::Render(HDC hDC, float fTime)
{
	CWord::Render(hDC, fTime);

	//TCHAR   string[64] = { };

	//if (m_bNone)
	//	_stprintf_s(string, TEXT("NONE STATE"));

	//else
	//	_stprintf_s(string, TEXT("NOT NONE STATE"));

	//TextOut(hDC, 0, 50, string, lstrlen(string));
}

void CNumber::PostRender(float fTime)
{
	CWord::PostRender(fTime);
}

CNumber* CNumber::Clone()
{
	return new CNumber(*this);
}



void CNumber::ChangeNumberAnimation()
{
	bool bClear = GET_SINGLE(CSceneManager)->GetClear(m_iNumber);

	if (!bClear)
	{
		switch (m_iNumber)
		{
		case 0:
			ChangeAnimation("Level00");
			break;
		case 1:
			ChangeAnimation("Level01");
			break;
		case 2:
			ChangeAnimation("Level02");
			break;
		case 3:
			ChangeAnimation("Level03");
			break;
		case 4:
			ChangeAnimation("Level04");
			break;
		case 5:
			ChangeAnimation("Level05");
			break;
		case 6:
			ChangeAnimation("Level06");
			break;
		case 7:
			ChangeAnimation("Level07");
			break;
		}
	}

	else
	{
		switch (m_iNumber)
		{
		case 0:
			ChangeAnimation("Level00_Clear");
			break;
		case 1:
			ChangeAnimation("Level01_Clear");
			break;
		case 2:
			ChangeAnimation("Level02_Clear");
			break;
		case 3:
			ChangeAnimation("Level03_Clear");
			break;
		case 4:
			ChangeAnimation("Level04_Clear");
			break;
		case 5:
			ChangeAnimation("Level05_Clear");
			break;
		case 6:
			ChangeAnimation("Level06_Clear");
			break;
		case 7:
			ChangeAnimation("Level07_Clear");
			break;
		}
	}
	
}
