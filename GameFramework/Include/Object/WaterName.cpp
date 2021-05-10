#include "WaterName.h"

#include "../GameManager.h"

CWaterName::CWaterName()
{
	m_eNameType = NAME_TYPE::WATER;
}

CWaterName::CWaterName(const CWaterName& obj) :
	CName(obj)
{
	m_eNameType = NAME_TYPE::WATER;
}

CWaterName::~CWaterName()
{
}

bool CWaterName::Init()
{
	CName::Init();

	CreateAnimation();

	AddAnimationSequence("WaterName");
	//AddAnimationSequence("WaterName_Off");

	return true;
}

bool CWaterName::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CWaterName::Start()
{
	CName::Start();
}

void CWaterName::Update(float fTime)
{
	CName::Update(fTime);
}

void CWaterName::PostUpdate(float fTime)
{
	CName::PostUpdate(fTime);
}

void CWaterName::Collision(float fTime)
{
	CName::Collision(fTime);
}

void CWaterName::PrevRender(float fTime)
{
	CName::PrevRender(fTime);

	/*if (!m_bMoving)
	{
		if (m_bConnected)
			ChangeAnimation("WaterName");

		else
			ChangeAnimation("WaterName_Off");
	}*/
}

void CWaterName::Render(HDC hDC, float fTime)
{
	CName::Render(hDC, fTime);
	if (GET_SINGLE(CGameManager)->GetPrintInfo())
	{
		TCHAR   string[64] = { };

		if (m_bConnected)
		{
			_stprintf_s(string, TEXT("WaterName : Connected"));
		}

		else
			_stprintf_s(string, TEXT("WaterName: Not Nonnected"));

		TextOut(hDC, 0, 140, string, lstrlen(string));
	}
}

void CWaterName::PostRender(float fTime)
{
	CName::PostRender(fTime);

}

CWaterName* CWaterName::Clone()
{
	return new CWaterName(*this);
}