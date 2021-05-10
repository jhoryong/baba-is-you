#include "Obj.h"

#include "../Resource/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Resource/ResourceManager.h"
#include "../Animation.h"
#include "../Resource/AnimationSequence.h"
#include "../Resource/AnimationSequence.h"
#include "../Scene/Camera.h"
#include "../Scene/SceneCollision.h"
#include "../Collider/Collider.h"
#include "../PathManager.h"
#include "../Input.h"

CObj::CObj() :
	m_pScene(nullptr),
	m_pTexture(nullptr),
	m_pAnimation(nullptr),
	m_bUI(false),
	m_bEnvironment(false),
	m_bStart(false),
	m_bAlphaBlend(false),
	m_cAlpha(255),
	m_bDrawCollider(false)
{
}

CObj::CObj(const CObj& obj)
{
	*this = obj;
	m_iRefCount = 1;

	if (m_pTexture)
		m_pTexture->AddRef();

	if (obj.m_pAnimation)
	{
		m_pAnimation = obj.m_pAnimation->Clone();
		m_pAnimation->SetOwner(this);
		m_pAnimation->SetScene(m_pScene);
	}

	m_ColliderList.clear();

	auto	iter = obj.m_ColliderList.begin();
	auto	iterEnd = obj.m_ColliderList.end();

	for (; iter != iterEnd; ++iter)
	{
		CCollider* pCollider = (*iter)->Clone();

		pCollider->m_pOwner = this;

		m_ColliderList.push_back(pCollider);
	}
}

CObj::~CObj()
{
	SAFE_DELETE_VECLIST(m_ColliderList);
	SAFE_DELETE(m_pAnimation);
	SAFE_RELEASE(m_pTexture);
	GET_SINGLE(CInput)->DeleteBindAction("Collider");
}

bool CObj::Init(const char* pFileName, const string& strPathName)
{
	return true;
}

void CObj::Start()
{
	///*static bool bKey = false;
	//if (!bKey)
	//{
	//	bKey = true;
	//	
	//}
	GET_SINGLE(CInput)->AddActionKey("Collider", VK_F2);
	GET_SINGLE(CInput)->AddBindAction("Collider", KEY_TYPE::DOWN, this, &CObj::ColliderSwitch);
	
	if (m_pAnimation)
	{
		SAFE_RELEASE(m_pTexture);
		m_pTexture = m_pAnimation->m_pCurrent->pSequence->GetTexture();
	}
}

void CObj::Update(float fTime)
{
	if (m_pAnimation)
		m_pAnimation->Update(fTime);

	auto	iter = m_ColliderList.begin();
	auto	iterEnd = m_ColliderList.end();

	for (; iter != iterEnd; )
	{
		if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Update(fTime);
		++iter;
	}
}

void CObj::PostUpdate(float fTime)
{
}

void CObj::Collision(float fTime)
{
	auto	iter = m_ColliderList.begin();
	auto	iterEnd = m_ColliderList.end();

	Vector2	vRS = m_pScene->GetMainCamera()->GetResolution();
	Vector2	vCameraPos = m_pScene->GetMainCamera()->GetPos();
	Vector2	vExt = vRS / 4.f;

	for (; iter != iterEnd; ++iter)
	{
		if (!(*iter)->IsEnable())
			continue;

		// 카메라로부터 너무 벗어나 있을 경우 포함을 안시킨다.
		// 만약 이전에 충돌처리가 되고 있던 물체가 있을 경우
		// 떨어지는 처리를 해주도록 한다.
		if (!m_bUI)
		{
			if ((*iter)->GetSectionInfo().fL <= vCameraPos.x + vRS.x + vExt.x &&
				(*iter)->GetSectionInfo().fR >= vCameraPos.x - vExt.x &&
				(*iter)->GetSectionInfo().fT <= vCameraPos.y + vRS.y + vExt.y &&
				(*iter)->GetSectionInfo().fB >= vCameraPos.y - vExt.y)
			{
				m_pScene->GetSceneCollision()->AddCollider(*iter);
			}

			// 이전 충돌체 있는지 판단하여 처리
			else
			{

			}
		}

		else
			m_pScene->GetSceneCollision()->AddCollider(*iter);
	}
}

void CObj::PrevRender(float fTime)
{
	if (!m_bUI)
		m_vRenderPos = m_vPos - m_pScene->GetMainCamera()->GetPos();

	else
		m_vRenderPos = m_vPos;
}

void CObj::Render(HDC hDC, float fTime)
{
	CCamera* pCamera = m_pScene->GetMainCamera();

	Vector2	vLT = m_vRenderPos - m_vPivot * m_vSize;

	if (m_pTexture)
	{
		if (m_bAlphaBlend)
		{
			if (m_pAnimation)
			{
				AnimationFrameInfo	tCurrentFrame = m_pAnimation->GetCurrnetFrameInfo();
				m_vSize = tCurrentFrame.vEnd - tCurrentFrame.vStart;

				if (vLT.x + m_vSize.x <= 0.f)
					return;

				else if (vLT.x >= pCamera->GetResolution().x)
					return;

				else if (vLT.y + m_vSize.y <= 0.f)
					return;

				else if (vLT.y >= pCamera->GetResolution().y)
					return;

				int	iFrame = 0;

				if (m_pAnimation->m_pCurrent->pSequence->GetAnimType() == ANIM_TYPE::FRAME)
					iFrame = m_pAnimation->m_pCurrent->iFrame;

				m_pTexture->RenderAlphaBlend(m_cAlpha, hDC, vLT, tCurrentFrame.vStart, m_vSize, iFrame);
			}

			else
			{
				if (vLT.x + m_vSize.x <= 0.f)
					return;

				else if (vLT.x >= pCamera->GetResolution().x)
					return;

				else if (vLT.y + m_vSize.y <= 0.f)
					return;

				else if (vLT.y >= pCamera->GetResolution().y)
					return;

				m_pTexture->RenderAlphaBlend(m_cAlpha, hDC, vLT, Vector2::Zero, m_vSize);
			}
		}

		else
		{
			if (m_pAnimation)
			{
				AnimationFrameInfo	tCurrentFrame = m_pAnimation->GetCurrnetFrameInfo();
				m_vSize = tCurrentFrame.vEnd - tCurrentFrame.vStart;

				if (vLT.x + m_vSize.x <= 0.f)
					return;

				else if (vLT.x >= pCamera->GetResolution().x)
					return;

				else if (vLT.y + m_vSize.y <= 0.f)
					return;

				else if (vLT.y >= pCamera->GetResolution().y)
					return;

				int	iFrame = 0;

				if (m_pAnimation->m_pCurrent->pSequence->GetAnimType() == ANIM_TYPE::FRAME)
					iFrame = m_pAnimation->m_pCurrent->iFrame;

				m_pTexture->Render(hDC, vLT, tCurrentFrame.vStart, m_vSize, iFrame);
			}

			else
			{
				if (vLT.x + m_vSize.x <= 0.f)
					return;

				else if (vLT.x >= pCamera->GetResolution().x)
					return;

				else if (vLT.y + m_vSize.y <= 0.f)
					return;

				else if (vLT.y >= pCamera->GetResolution().y)
					return;

				m_pTexture->Render(hDC, vLT, Vector2::Zero, m_vSize);
			}
		}
	}

	else
	{
		Vector2	vRB = vLT + m_vSize;
		//HBRUSH hPrevBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));
		Rectangle(hDC, (int)vLT.x, (int)vLT.y, (int)vRB.x, (int)vRB.y);
		//SelectObject(hDC, hPrevBrush);
	}

	if (m_bDrawCollider) // 디버깅 용으로 충돌체를 그려준다.
	{
		auto	iter = m_ColliderList.begin();
		auto	iterEnd = m_ColliderList.end();

		for (; iter != iterEnd; )
		{
			if (!(*iter)->IsEnable())
			{
				++iter;
				continue;
			}

			(*iter)->Render(hDC, fTime);
			++iter;
		}
	}
}

void CObj::PostRender(float fTime)
{
}

void CObj::SaveFile(const char* pFileName, const string& strPathName)
{
	FILE* pFile = nullptr;

	const char* pPath = GET_SINGLE(CPathManager)->FindPathMultibyte(strPathName);
	char	strFullPath[MAX_PATH] = {};

	if (pPath)
		strcpy_s(strFullPath, pPath);

	strcat_s(strFullPath, pFileName);

	fopen_s(&pFile, strFullPath, "wb");

	if (!pFile)
		return;

	Save(pFile);

	fclose(pFile);
}

void CObj::LoadFile(const char* pFileName, const string& strPathName)
{
	FILE* pFile = nullptr;

	const char* pPath = GET_SINGLE(CPathManager)->FindPathMultibyte(strPathName);
	char	strFullPath[MAX_PATH] = {};

	if (pPath)
		strcpy_s(strFullPath, pPath);

	strcat_s(strFullPath, pFileName);

	fopen_s(&pFile, strFullPath, "rb");

	if (!pFile)
		return;

	Load(pFile);

	fclose(pFile);
}

void CObj::Save(FILE* pFile)
{
}

void CObj::Load(FILE* pFile)
{
}

bool CObj::SetTexture(const string& strName)
{
	SAFE_RELEASE(m_pTexture);
	m_pTexture = m_pScene->GetSceneResource()->FindTexture(strName);

	return true;
}

bool CObj::SetTexture(const string& strName, const TCHAR* pFileName, const string& strPathName)
{
	SAFE_RELEASE(m_pTexture);
	m_pScene->GetSceneResource()->LoadTexture(strName, pFileName, strPathName);

	m_pTexture = m_pScene->GetSceneResource()->FindTexture(strName);

	return true;
}

bool CObj::SetTexture(const string& strName,
	const vector<const TCHAR*>& vecFileName, const string& strPathName)
{
	SAFE_RELEASE(m_pTexture);
	m_pScene->GetSceneResource()->LoadTexture(strName, vecFileName, strPathName);

	m_pTexture = m_pScene->GetSceneResource()->FindTexture(strName);

	return true;
}

bool CObj::SetTexture(const string& strName, const TCHAR* pFileName,
	int iCount, const string& strPathName)
{
	SAFE_RELEASE(m_pTexture);
	m_pScene->GetSceneResource()->LoadTexture(strName, pFileName,
		iCount, strPathName);

	m_pTexture = m_pScene->GetSceneResource()->FindTexture(strName);

	return true;
}

bool CObj::SetTexture(CTexture* pTexture)
{
	SAFE_RELEASE(m_pTexture);
	m_pTexture = pTexture;

	if (m_pTexture)
		m_pTexture->AddRef();

	return true;
}

void CObj::CreateAnimation()
{
	if (m_pAnimation)
		return;

	m_pAnimation = new CAnimation;
	m_pAnimation->SetOwner(this);
	m_pAnimation->SetScene(m_pScene);
	m_pAnimation->Init();
}

void CObj::AddAnimationSequence(const string& strName)
{
	m_pAnimation->AddSequence(strName);
}

void CObj::AddAnimationSequence(CAnimationSequence* pSequence)
{
	m_pAnimation->AddSequence(pSequence);
}

void CObj::AddLoadedAnimationSequence(const string& strName)
{
	CAnimationSequence* pSequence = GET_SINGLE(CResourceManager)->FindAnimationSequence(strName);

	if (!pSequence)
		return;

	m_pAnimation->AddSequence(pSequence);
	SAFE_RELEASE(pSequence);
}

void CObj::SetAnimationPlayRate(const string& strName, float fPlayRate)
{
	m_pAnimation->SetPlayRate(strName, fPlayRate);
}

void CObj::AddAnimationPlayRate(const string& strName, float fPlayRate)
{
	m_pAnimation->AddPlayRate(strName, fPlayRate);
}

void CObj::ChangeAnimation(const string& strName)
{
	m_pAnimation->Change(strName);
}

void CObj::SetDefaultAnimation(const string& strName)
{
	m_pAnimation->SetDefault(strName);
}


CCollider* CObj::FindCollider(const string& strName)
{
	auto	iter = m_ColliderList.begin();
	auto	iterEnd = m_ColliderList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == strName)
			return *iter;
	}

	return nullptr;
}

void CObj::DeleteCollider(const string& strName)
{
	auto	iter = m_ColliderList.begin();
	auto	iterEnd = m_ColliderList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == strName)
		{
			SAFE_DELETE((*iter));
			m_ColliderList.erase(iter);
			break;
		}
	}
}
