
#include "Effect.h"
#include "../Resource/ResourceManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "../Resource/AnimationSequence.h"

CEffect::CEffect()
{
}

CEffect::~CEffect()
{
}

bool CEffect::Init()
{
	return true;
}

bool CEffect::Init(const char* pFileName, const string& strPathName)
{
	if (!CObj::Init(pFileName, strPathName))
		return false;

	return true;
}

void CEffect::Start()
{
	CObj::Start();
}

void CEffect::Update(float fTime)
{
	CObj::Update(fTime);
}

void CEffect::PostUpdate(float fTime)
{
	CObj::PostUpdate(fTime);
}

void CEffect::Collision(float fTime)
{
	CObj::Collision(fTime);
}

void CEffect::PrevRender(float fTime)
{
	CObj::PrevRender(fTime);
}

void CEffect::Render(HDC hDC, float fTime)
{
	CObj::Render(hDC, fTime);
}

void CEffect::PostRender(float fTime)
{
	CObj::PostRender(fTime);
}

CEffect* CEffect::Clone()
{
	return new CEffect(*this);
}
