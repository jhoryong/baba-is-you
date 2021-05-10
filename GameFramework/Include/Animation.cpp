#include "Animation.h"
#include "Resource/AnimationSequence.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Object/Obj.h"
#include "Resource/AnimationNotify.h"

CAnimation::CAnimation() :
	m_pCurrent(nullptr),
	m_pDefault(nullptr),
	m_pScene(nullptr),
	m_pOwner(nullptr)
{
}

CAnimation::CAnimation(const CAnimation& animation)
{
	*this = animation;

	m_mapAnimationSequence.clear();

	auto	iter = animation.m_mapAnimationSequence.begin();
	auto	iterEnd = animation.m_mapAnimationSequence.end();

	for (; iter != iterEnd; ++iter)
	{
		PMotionInfo	pMotion = new MotionInfo;
		*pMotion = *iter->second;

		if (pMotion->pSequence)
			pMotion->pSequence->AddRef();

		m_mapAnimationSequence.insert(make_pair(iter->first, pMotion));

		if (iter->first == animation.m_pCurrent->pSequence->m_strName)
			m_pCurrent = pMotion;

		if (iter->first == animation.m_pDefault->pSequence->m_strName)
			m_pDefault = pMotion;
	}
}

CAnimation::~CAnimation()
{
	auto		iter = m_mapAnimationSequence.begin();
	auto		iterEnd = m_mapAnimationSequence.end();
	for (; iter != iterEnd; ++iter)
	{
		SAFE_RELEASE(iter->second->pSequence);
		SAFE_DELETE(iter->second);
	}
	m_mapAnimationSequence.clear();
}

AnimationFrameInfo CAnimation::GetCurrnetFrameInfo()
{
	return m_pCurrent->pSequence->m_vecFrame[m_pCurrent->iFrame];
}

bool CAnimation::Init()
{
	return true;
}

void CAnimation::AddSequence(const string& strName)
{
	CAnimationSequence* pAnimation = m_pScene->GetSceneResource()->FindAnimationSequence(strName);

	if (!pAnimation)
		return;

	PMotionInfo	pMotion = new MotionInfo;

	pMotion->pSequence = pAnimation;
	pMotion->fCurrentTime = 0.f;
	pMotion->fGlobalTime = 0.f;
	pMotion->iFrame = 0;
	pMotion->fLoopTime = pAnimation->m_fLoopTime;
	pMotion->fFrameTime = pAnimation->m_fFrameTime;
	pMotion->fOptionTime = 0.f;
	pMotion->fOptionTimeMax = pAnimation->m_fOptionTimeMax;
	pMotion->fPlayRate = pAnimation->m_fPlayRate;

	m_mapAnimationSequence.insert(make_pair(strName, pMotion));

	if (!m_pCurrent)
		m_pCurrent = pMotion;
	
	if (!m_pDefault)
		m_pDefault = pMotion;
}

void CAnimation::AddSequence(CAnimationSequence* pSequence)
{
	PMotionInfo	pMotion = new MotionInfo;

	pMotion->pSequence = pSequence;
	pMotion->fCurrentTime = 0.f;
	pMotion->fGlobalTime = 0.f;
	pMotion->iFrame = 0;
	pMotion->fLoopTime = pSequence->m_fLoopTime;
	pMotion->fFrameTime = pSequence->m_fFrameTime;
	pMotion->fOptionTime = 0.f;
	pMotion->fOptionTimeMax = pSequence->m_fOptionTimeMax;
	pMotion->fPlayRate = pSequence->m_fPlayRate;

	pSequence->AddRef();

	m_mapAnimationSequence.insert(make_pair(pSequence->GetName(), pMotion));

	if (!m_pCurrent)
		m_pCurrent = pMotion;

	if (!m_pDefault)
		m_pDefault = pMotion;
}

void CAnimation::Change(const string& strName)
{
	if (m_pCurrent->pSequence->m_strName == strName)
		return;

	m_pCurrent->fCurrentTime = 0.f;
	m_pCurrent->fOptionTime = 0.f;
	m_pCurrent->iFrame = 0;

	ClearNotify();

	m_pCurrent = FindMotionInfo(strName);

	m_pOwner->SetTexture(m_pCurrent->pSequence->m_pTexture);
}

void CAnimation::SetCurrent(const string& strName)
{
	m_pCurrent = FindMotionInfo(strName);
}

void CAnimation::SetDefault(const string& strName)
{
	m_pDefault = FindMotionInfo(strName);
}

void CAnimation::SetPlayRate(const string& strName, float fPlayRate)
{
	PMotionInfo	pMotion = FindMotionInfo(strName);

	if (!pMotion)
		return;

	pMotion->fPlayRate = fPlayRate;
}

void CAnimation::AddPlayRate(const string& strName, float fPlayRate)
{
	PMotionInfo	pMotion = FindMotionInfo(strName);

	if (!pMotion)
		return;

	pMotion->fPlayRate += fPlayRate;
}

void CAnimation::Update(float fTime)
{
	m_pCurrent->fCurrentTime += fTime * m_pCurrent->fPlayRate;
	m_pCurrent->fGlobalTime += fTime * m_pCurrent->fPlayRate;

	CallNotifyTime(fTime);

	while (m_pCurrent->fCurrentTime >= m_pCurrent->fFrameTime)
	{
		m_pCurrent->fCurrentTime -= m_pCurrent->fFrameTime;

		++m_pCurrent->iFrame;

		CallNotifyFrame(fTime);

		// 모션이 한바퀴 돌았을 경우
		if (m_pCurrent->iFrame == m_pCurrent->pSequence->m_vecFrame.size())
		{
			ClearNotify();
			m_pCurrent->fGlobalTime -= m_pCurrent->fLoopTime;

			switch (m_pCurrent->pSequence->m_eOption)
			{
			case ANIM_OPTION::LOOP:
				m_pCurrent->iFrame = 0;
				break;
			case ANIM_OPTION::ONCE_RETURN:
				Change(m_pDefault->pSequence->m_strName);
				break;
			case ANIM_OPTION::ONCE_DESTROY:
				m_pOwner->Destroy();
				break;
			case ANIM_OPTION::ONCE_PAUSE:
				m_pCurrent->iFrame = (int)m_pCurrent->pSequence->m_vecFrame.size() - 1;
				break;
			case ANIM_OPTION::TIME_RETURN:
				break;
			case ANIM_OPTION::TIME_DESTROY:
				break;
			}
		}
	}
}

CAnimation* CAnimation::Clone()
{
	return new CAnimation(*this);
}

PMotionInfo CAnimation::FindMotionInfo(const string& strName)
{
	auto	iter = m_mapAnimationSequence.find(strName);
	
	if (iter == m_mapAnimationSequence.end())
		return nullptr;

	return iter->second;
}

void CAnimation::CallNotifyTime(float fTime)
{
	auto	iter = m_pCurrent->pSequence->m_mapNotify.begin();
	auto	iterEnd = m_pCurrent->pSequence->m_mapNotify.end();

	for (; iter != iterEnd; ++iter)
	{
		if (iter->second->m_fNotifyTime == -1.f)
			continue;

		if (iter->second->m_fNotifyTime >= m_pCurrent->fGlobalTime)
		{
			iter->second->Call(fTime);
		}
	}
}

void CAnimation::CallNotifyFrame(float fTime)
{
	auto	iter = m_pCurrent->pSequence->m_mapNotify.begin();
	auto	iterEnd = m_pCurrent->pSequence->m_mapNotify.end();

	for (; iter != iterEnd; ++iter)
	{
		if (iter->second->m_iFrame == -1)
			continue;

		if (iter->second->m_iFrame <= m_pCurrent->iFrame)
		{
			iter->second->Call(fTime);
		}
	}
}

void CAnimation::ClearNotify()
{
	auto	iter = m_pCurrent->pSequence->m_mapNotify.begin();
	auto	iterEnd = m_pCurrent->pSequence->m_mapNotify.end();

	for (; iter != iterEnd; ++iter)
	{
		iter->second->m_bCall = false;
	}
}
