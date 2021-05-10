#include "BackgroundObj.h"


CBackgroundObj::CBackgroundObj()
{
	m_bBackgroundObj = true;
}

CBackgroundObj::~CBackgroundObj()
{
}

bool CBackgroundObj::Init()
{
	return true;
}

bool CBackgroundObj::Init(const char* pFileName, const string& strPathName)
{
	if (!CObj::Init(pFileName, strPathName))
		return false;

	return true;
}

void CBackgroundObj::Start()
{
	CObj::Start();
}

void CBackgroundObj::Update(float fTime)
{
	CObj::Update(fTime);
}

void CBackgroundObj::PostUpdate(float fTime)
{
	CObj::PostUpdate(fTime);
}

void CBackgroundObj::Collision(float fTime)
{
	//CObj::Collision(fTime);
}

void CBackgroundObj::PrevRender(float fTime)
{
	CObj::PrevRender(fTime);
}

void CBackgroundObj::Render(HDC hDC, float fTime)
{
	CObj::Render(hDC, fTime);
}

void CBackgroundObj::PostRender(float fTime)
{
	CObj::PostRender(fTime);
}

CBackgroundObj* CBackgroundObj::Clone()
{
	return new CBackgroundObj(*this);
}
