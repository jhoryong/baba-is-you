#include "Tree.h"


CTree::CTree()
{
	m_eCharacterType = CHARACTER_TYPE::TREE;
	memset(m_bState, false, sizeof(bool) * (int)STATE_TYPE::END);
	m_bNone = true;
}

CTree::CTree(const CTree& obj) :
	CCharacter(obj)
{
	m_eCharacterType = CHARACTER_TYPE::TREE;
	memset(m_bState, false, sizeof(bool) * (int)STATE_TYPE::END);
	m_bNone = true;
}

CTree::~CTree()
{
}

bool CTree::Init()
{
	CCharacter::Init();

	CreateAnimation();
	AddAnimationSequence("Tree");

	return true;
}

bool CTree::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CTree::Start()
{
	CCharacter::Start();
}

void CTree::Update(float fTime)
{
	CCharacter::Update(fTime);
}

void CTree::PostUpdate(float fTime)
{
	CCharacter::PostUpdate(fTime);
}

void CTree::Collision(float fTime)
{
	CCharacter::Collision(fTime);
}

void CTree::PrevRender(float fTime)
{
	CCharacter::PrevRender(fTime);
}

void CTree::Render(HDC hDC, float fTime)
{
	CCharacter::Render(hDC, fTime);
}

void CTree::PostRender(float fTime)
{
	CCharacter::PostRender(fTime);
}

CTree* CTree::Clone()
{
	return new CTree(*this);
}