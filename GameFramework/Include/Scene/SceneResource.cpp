#include "SceneResource.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Texture.h"
#include "../Resource/Sound.h"

CSceneResource::CSceneResource()
{
}

CSceneResource::~CSceneResource()
{
	{
		auto	iter = m_mapTexture.begin();
		auto	iterEnd = m_mapTexture.end();

		for (; iter != iterEnd; ++iter)
		{
			string	strKey = iter->first;
			//iter->second->Release();
			GET_SINGLE(CResourceManager)->ReleaseTexture(strKey);
		}

		m_mapTexture.clear();
	}

	{
		auto	iter = m_mapSound.begin();
		auto	iterEnd = m_mapSound.end();

		for (; iter != iterEnd; ++iter)
		{
			string	strKey = iter->first;
			//if (iter->second->Release())
			GET_SINGLE(CResourceManager)->ReleaseSound(strKey);
		}

		m_mapSound.clear();
	}

	{
		auto	iter = m_mapChannelGroup.begin();
		auto	iterEnd = m_mapChannelGroup.end();

		for (; iter != iterEnd; ++iter)
		{
			string	strKey = iter->first;
			//if (iter->second->Release())
			GET_SINGLE(CResourceManager)->ReleaseChannelGroup(strKey);
		}

		m_mapChannelGroup.clear();
	}

	{
		auto	iter = m_mapAnimationSequence.begin();
		auto	iterEnd = m_mapAnimationSequence.end();

		for (; iter != iterEnd; ++iter)
		{
			string	strKey = iter->first;
			if (iter->second->Release())
				GET_SINGLE(CResourceManager)->ReleaseAnimationSequence(strKey);
		}

		m_mapAnimationSequence.clear();
	}
}

bool CSceneResource::LoadTexture(const string& strName, 
	const TCHAR* pFileName, const string& strPathName)
{
	GET_SINGLE(CResourceManager)->LoadTexture(strName, pFileName,
		strPathName);

	CTexture* pTexture = GET_SINGLE(CResourceManager)->FindTexture(strName);

	if (pTexture)
	{
		// 위의 FindTexture에서 가지고올때 카운트가 1이 증가하게 되므로 여기서는
		// 카운트를 1 감소시켜주고 가지고 있게 한다.
		//pTexture->Release();
		m_mapTexture.insert(make_pair(strName, pTexture));
		return true;
	}

	return false;
}

bool CSceneResource::LoadTexture(const string& strName,
	const vector<const TCHAR*>& vecFileName, const string& strPathName)
{
	GET_SINGLE(CResourceManager)->LoadTexture(strName, vecFileName,
		strPathName);

	CTexture* pTexture = GET_SINGLE(CResourceManager)->FindTexture(strName);

	if (pTexture)
	{
		// 위의 FindTexture에서 가지고올때 카운트가 1이 증가하게 되므로 여기서는
		// 카운트를 1 감소시켜주고 가지고 있게 한다.
		//pTexture->Release();
		m_mapTexture.insert(make_pair(strName, pTexture));
		return true;
	}

	return false;
}

bool CSceneResource::LoadTexture(const string& strName, 
	const TCHAR* pFileName, int iCount, const string& strPathName)
{
	GET_SINGLE(CResourceManager)->LoadTexture(strName, pFileName,
		iCount, strPathName);

	CTexture* pTexture = GET_SINGLE(CResourceManager)->FindTexture(strName);

	if (pTexture)
	{
		// 위의 FindTexture에서 가지고올때 카운트가 1이 증가하게 되므로 여기서는
		// 카운트를 1 감소시켜주고 가지고 있게 한다.
		//pTexture->Release();
		m_mapTexture.insert(make_pair(strName, pTexture));
		return true;
	}

	return false;
}

bool CSceneResource::LoadTextureFullPath(
	const string& strName, const TCHAR* pFullPath)
{
	GET_SINGLE(CResourceManager)->LoadTextureFullPath(
		strName, pFullPath);

	CTexture* pTexture = GET_SINGLE(CResourceManager)->FindTexture(strName);

	if (pTexture)
	{
		// 위의 FindTexture에서 가지고올때 카운트가 1이 증가하게 되므로 여기서는
		// 카운트를 1 감소시켜주고 가지고 있게 한다.
		//pTexture->Release();
		m_mapTexture.insert(make_pair(strName, pTexture));
		return true;
	}

	return false;
}

void CSceneResource::SetColorKey(const string& strName, unsigned char r, unsigned char g, unsigned char b, int iIndex)
{
	CTexture* pTexture = FindTexture(strName);

	if (!pTexture)
		return;

	pTexture->SetColorKey(r, g, b, iIndex);

	SAFE_RELEASE(pTexture);
}

void CSceneResource::SetColorKeyAll(const string& strName, unsigned char r, unsigned char g, unsigned char b)
{
	CTexture* pTexture = FindTexture(strName);

	if (!pTexture)
		return;

	pTexture->SetColorKeyAll(r, g, b);

	SAFE_RELEASE(pTexture);
}

CTexture* CSceneResource::FindTexture(const string& strName)
{
	auto		iter = m_mapTexture.find(strName);

	if (iter == m_mapTexture.end())
		return nullptr;

	iter->second->AddRef();

	return iter->second;
}

bool CSceneResource::CreateAnimationSequence(const string& strName, 
	const string& strTexName, ANIM_TYPE eType, 
	ANIM_OPTION eOption, ANIM_PLAY_TYPE ePlayType, 
	float fLoopTime, float fPlayRate, float fOptionTimeMax)
{
	GET_SINGLE(CResourceManager)->CreateAnimationSequence(strName,
		strTexName, eType, eOption, ePlayType, fLoopTime, fPlayRate, 
		fOptionTimeMax);

	CAnimationSequence* pAnimation = GET_SINGLE(CResourceManager)->FindAnimationSequence(strName);

	if (pAnimation)
	{
		// 위의 FindTexture에서 가지고올때 카운트가 1이 증가하게 되므로 여기서는
		// 카운트를 1 감소시켜주고 가지고 있게 한다.
		m_mapAnimationSequence.insert(make_pair(strName, pAnimation));
		return true;
	}

	return false;
}

bool CSceneResource::CreateAnimationSequence(const string& strName, 
	const char* pFileName, const string& strPathName)
{
	GET_SINGLE(CResourceManager)->CreateAnimationSequence(strName, pFileName);

	CAnimationSequence* pAnimation = GET_SINGLE(CResourceManager)->FindAnimationSequence(strName);

	if (pAnimation)
	{
		// 위의 FindTexture에서 가지고올때 카운트가 1이 증가하게 되므로 여기서는
		// 카운트를 1 감소시켜주고 가지고 있게 한다.
		m_mapAnimationSequence.insert(make_pair(strName, pAnimation));
		return true;
	}

	return false;
}

bool CSceneResource::CreateAnimationSequence(const string& strName, FILE* pFile)
{
	GET_SINGLE(CResourceManager)->CreateAnimationSequence(strName, pFile);

	CAnimationSequence* pAnimation = GET_SINGLE(CResourceManager)->FindAnimationSequence(strName);

	if (pAnimation)
	{
		// 위의 FindTexture에서 가지고올때 카운트가 1이 증가하게 되므로 여기서는
		// 카운트를 1 감소시켜주고 가지고 있게 한다.
		m_mapAnimationSequence.insert(make_pair(strName, pAnimation));
		return true;
	}

	return false;
}

void CSceneResource::AddAnimationFrame(const string& strName,
	const Vector2& vStart, const Vector2& vEnd)
{
	GET_SINGLE(CResourceManager)->AddAnimationFrame(strName, vStart, vEnd);
}

void CSceneResource::AddAnimationFrame(const string& strName, 
	const AnimationFrameInfo& tFrame)
{
	GET_SINGLE(CResourceManager)->AddAnimationFrame(strName, tFrame);
}

CAnimationSequence* CSceneResource::FindAnimationSequence(
	const string& strName)
{
	auto iter = m_mapAnimationSequence.find(strName);

	if (iter == m_mapAnimationSequence.end())
		return nullptr;

	iter->second->AddRef();

	return iter->second;
}

void CSceneResource::ReleaseAnimationSequence()
{
	auto	iter = m_mapAnimationSequence.begin();
	auto	iterEnd = m_mapAnimationSequence.end();

	for (; iter != iterEnd; ++iter)
	{
		iter->second->Release();
	}

	m_mapAnimationSequence.clear();
}

void CSceneResource::AddNotify(const string& strSequenceName,
	const string& strName, int iFrame)
{
	CAnimationSequence* pSequence = FindAnimationSequence(strSequenceName);

	if (!pSequence)
		return;

	pSequence->AddNotify(strName, iFrame);

	SAFE_RELEASE(pSequence);
}

void CSceneResource::AddNotify(const string& strSequenceName,
	const string& strName, float fTime)
{
	CAnimationSequence* pSequence = FindAnimationSequence(strSequenceName);

	if (!pSequence)
		return;

	pSequence->AddNotify(strName, fTime);

	SAFE_RELEASE(pSequence);
}

void CSceneResource::AddNotifyFunction(const string& strSequenceName,
	const string& strName, void(*pFunc)(float))
{
	CAnimationSequence* pSequence = FindAnimationSequence(strSequenceName);

	if (!pSequence)
		return;

	pSequence->AddNotifyFunction(strName, pFunc);

	SAFE_RELEASE(pSequence);
}

void CSceneResource::DeleteNotifyFunction(
	const string& strSequenceName, const string& strName, 
	void(*pFunc)(float))
{
	CAnimationSequence* pSequence = FindAnimationSequence(strSequenceName);

	if (!pSequence)
		return;

	pSequence->DeleteNotifyFunction(strName, pFunc);

	SAFE_RELEASE(pSequence);
}

bool CSceneResource::LoadSound(const string& strGroup,
	bool bLoop, const string& strName, const char* pFileName,
	const string& strPathName)
{
	GET_SINGLE(CResourceManager)->LoadSound(strGroup, bLoop, strName, pFileName,
		strPathName);

	CSound* pSound = GET_SINGLE(CResourceManager)->FindSound(strName);

	if (pSound)
	{
		// 위의 FindTexture에서 가지고올때 카운트가 1이 증가하게 되므로 여기서는
		// 카운트를 1 감소시켜주고 가지고 있게 한다.
		//pSound->Release();
		m_mapSound.insert(make_pair(strName, pSound));
		return true;
	}

	return false;
}

CSound* CSceneResource::FindSound(const string& strName)
{
	auto		iter = m_mapSound.find(strName);

	if (iter == m_mapSound.end())
		return nullptr;

	iter->second->AddRef();

	return iter->second;
}

bool CSceneResource::CreateChannelGroup(const string& strName)
{
	GET_SINGLE(CResourceManager)->CreateChannelGroup(strName);

	ChannelGroup* pGroup = GET_SINGLE(CResourceManager)->FindChannelGroup(strName);

	if (pGroup)
	{
		m_mapChannelGroup.insert(make_pair(strName, pGroup));
		return true;
	}

	return false;
}

ChannelGroup* CSceneResource::FindChannelGroup(const string& strName)
{
	auto		iter = m_mapChannelGroup.find(strName);

	if (iter == m_mapChannelGroup.end())
		return nullptr;

	return iter->second;
}

void CSceneResource::SetVolume(int iVolume)
{
	GET_SINGLE(CResourceManager)->SetVolume(iVolume);
}

void CSceneResource::SetGroupVolume(const string& strGroup, int iVolume)
{
	ChannelGroup* pGroup = FindChannelGroup(strGroup);

	if (!pGroup)
		return;

	pGroup->setVolume(iVolume / 100.f);
}

bool CSceneResource::SoundPlay(const string& strName)
{
	CSound* pSound = FindSound(strName);

	if (!pSound)
		return false;

	pSound->Play();

	SAFE_RELEASE(pSound);

	return true;
}

bool CSceneResource::SoundStop(const string& strName)
{
	CSound* pSound = FindSound(strName);

	if (!pSound)
		return false;

	pSound->Stop();

	SAFE_RELEASE(pSound);

	return true;
}

bool CSceneResource::SoundPause(const string& strName)
{
	CSound* pSound = FindSound(strName);

	if (!pSound)
		return false;

	pSound->Pause();

	SAFE_RELEASE(pSound);

	return true;
}

bool CSceneResource::SoundResume(const string& strName)
{
	CSound* pSound = FindSound(strName);

	if (!pSound)
		return false;

	pSound->Resume();

	SAFE_RELEASE(pSound);

	return true;
}
