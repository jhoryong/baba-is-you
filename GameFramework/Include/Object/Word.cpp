#include "Word.h"

CWord::CWord():
	m_eWordType(WORD_TYPE::END)
{
	m_eBlockObjType = BLOCKOBJ_TYPE::WORD;
	m_bState[(int)STATE_TYPE::PUSH] = true; // word 는 무조건 PUSH 로 고정된다.
	m_iZOrder = 3;
}

CWord::CWord(const CWord& obj) :
	CBlockObj(obj),
	m_eWordType(WORD_TYPE::END)
{
	m_eBlockObjType = BLOCKOBJ_TYPE::WORD;
	m_bState[(int)STATE_TYPE::PUSH] = true; // word 는 무조건 PUSH 로 고정된다.
	m_iZOrder = 3;
}

CWord::~CWord()
{
}


bool CWord::Init()
{
	CBlockObj::Init();

	return true;
}

bool CWord::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CWord::Start()
{
	CBlockObj ::Start();
}

void CWord::Update(float fTime)
{
	CBlockObj::Update(fTime);
}

void CWord::PostUpdate(float fTime)
{
	CBlockObj::PostUpdate(fTime);
}

void CWord::Collision(float fTime)
{
	CBlockObj::Collision(fTime);
}

void CWord::PrevRender(float fTime)
{
	CBlockObj::PrevRender(fTime);
}

void CWord::Render(HDC hDC, float fTime)
{
	CBlockObj::Render(hDC, fTime);
}

void CWord::PostRender(float fTime)
{
	CBlockObj::PostRender(fTime);
}
