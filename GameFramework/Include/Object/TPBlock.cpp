#include "TPBlock.h"

CTPBlock::CTPBlock()
{
	m_eCharacterType = CHARACTER_TYPE::TPBLOCK;
	m_bState[(int)STATE_TYPE::STOP] = true;
}

CTPBlock::CTPBlock(const CTPBlock& obj) :
	CCharacter(obj)
{
	m_eCharacterType = CHARACTER_TYPE::TPBLOCK;
	m_bState[(int)STATE_TYPE::STOP] = true;
}

CTPBlock::~CTPBlock()
{
}

bool CTPBlock::Init()
{
	CCharacter::Init();

	return true;
}

bool CTPBlock::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CTPBlock::Start()
{
	CCharacter::Start();
}

void CTPBlock::Update(float fTime)
{
	CCharacter::Update(fTime);
	//m_bMoving = false;
}

void CTPBlock::PostUpdate(float fTime)
{
	CCharacter::PostUpdate(fTime);
}

void CTPBlock::Collision(float fTime)
{
	CCharacter::Collision(fTime);
}

void CTPBlock::PrevRender(float fTime)
{
	CCharacter::PrevRender(fTime);
}

void CTPBlock::Render(HDC hDC, float fTime)
{
	HBRUSH hBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));
	HPEN hPen = (HPEN)SelectObject(hDC, GetStockObject(NULL_PEN));

	CCharacter::Render(hDC, fTime);

	SelectObject(hDC, hBrush);
	SelectObject(hDC, hPen);
}

void CTPBlock::PostRender(float fTime)
{
	CCharacter::PostRender(fTime);
}

CTPBlock* CTPBlock::Clone()
{
	return new CTPBlock(*this);
}