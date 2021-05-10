#include "GroundTile.h"

CGroundTile::CGroundTile()
{
	m_eCharacterType = CHARACTER_TYPE::GROUNDTILE;
	memset(m_bState, false, sizeof(bool) * (int)STATE_TYPE::END);
	m_bNone = true;
}

CGroundTile::CGroundTile(const CGroundTile& obj) :
	CCharacter(obj)
{
	m_eCharacterType = CHARACTER_TYPE::GROUNDTILE;
	memset(m_bState, false, sizeof(bool) * (int)STATE_TYPE::END);
	m_bNone = true;
}

CGroundTile::~CGroundTile()
{
}

bool CGroundTile::Init()
{
	CCharacter::Init();

	CreateAnimation();
	AddAnimationSequence("GroundTile");

	return true;
}

bool CGroundTile::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CGroundTile::Start()
{
	CCharacter::Start();
}

void CGroundTile::Update(float fTime)
{
	CCharacter::Update(fTime);
}

void CGroundTile::PostUpdate(float fTime)
{
	CCharacter::PostUpdate(fTime);
}

void CGroundTile::Collision(float fTime)
{
	CCharacter::Collision(fTime);
}

void CGroundTile::PrevRender(float fTime)
{
	CCharacter::PrevRender(fTime);
}

void CGroundTile::Render(HDC hDC, float fTime)
{
	CCharacter::Render(hDC, fTime);
}

void CGroundTile::PostRender(float fTime)
{
	CCharacter::PostRender(fTime);
}

CGroundTile* CGroundTile::Clone()
{
	return new CGroundTile(*this);
}