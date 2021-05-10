
#include "Mouse.h"
#include "../Resource/ResourceManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "../Resource/AnimationSequence.h"

CMouse::CMouse()
{
}

CMouse::~CMouse()
{
}

bool CMouse::Init()
{
	m_pScene = GET_SINGLE(CSceneManager)->GetScene();

	//CreateMouseAnimation();

	//SetSize(32.f, 
	//);

	//CreateAnimation();

	//CAnimationSequence* pSequence = GET_SINGLE(CResourceManager)->FindAnimationSequence("MouseNormal");

	//AddAnimationSequence(pSequence);

	//SAFE_RELEASE(pSequence);

	return true;
}

bool CMouse::Init(const char* pFileName, const string& strPathName)
{
	if (!CObj::Init(pFileName, strPathName))
		return false;

	return true;
}

void CMouse::Start()
{
	CObj::Start();

	m_pScene = GET_SINGLE(CSceneManager)->GetScene();
}

void CMouse::Update(float fTime)
{
	CObj::Update(fTime);
}

void CMouse::PostUpdate(float fTime)
{
	CObj::PostUpdate(fTime);
}

void CMouse::Collision(float fTime)
{
	CObj::Collision(fTime);
}

void CMouse::PrevRender(float fTime)
{
	CObj::PrevRender(fTime);

	m_vRenderPos = m_vPos;
}

void CMouse::Render(HDC hDC, float fTime)
{
	CObj::Render(hDC, fTime);
}

void CMouse::PostRender(float fTime)
{
	CObj::PostRender(fTime);
}

CMouse* CMouse::Clone()
{
	return new CMouse(*this);
}

void CMouse::CreateMouseAnimation()
{
	/*vector<const TCHAR*>	vecFileName;

	for (int i = 0; i <= 10; ++i)
	{
		TCHAR* pFileName = new TCHAR[MAX_PATH];
		memset(pFileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(pFileName, TEXT("Mouse/%d.bmp"), i);

		vecFileName.push_back(pFileName);
	}

	GET_SINGLE(CResourceManager)->LoadTexture("MouseNormal",
		vecFileName);
	GET_SINGLE(CResourceManager)->SetColorKeyAll("MouseNormal",
		255, 0, 255);

	SAFE_DELETE_ARRAY_VECLIST(vecFileName);

	GET_SINGLE(CResourceManager)->CreateAnimationSequence("MouseNormal",
		"MouseNormal", FRAME, LOOP, NORMAL, 0.5f);

	for (int i = 0; i <= 10; ++i)
	{
		GET_SINGLE(CResourceManager)->AddAnimationFrame("MouseNormal",
			Vector2(0.f, 0.f), Vector2(32.f, 31.f));
	}*/
}
