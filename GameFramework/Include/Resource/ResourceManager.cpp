
#include "ResourceManager.h"
#include "Texture.h"
#include "AnimationSequence.h"
#include "Sound.h"

DEFINITION_SINGLE(CResourceManager)

CResourceManager::CResourceManager():
	m_pMasterGroup(nullptr)
{
	m_pSystem = 0;
}

CResourceManager::~CResourceManager()
{
	SAFE_RELEASE_MAP(m_mapAnimationSequence);
	SAFE_RELEASE_MAP(m_mapTexture);
	SAFE_RELEASE_MAP(m_mapSound);

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
			iter->second->release();
		}
	}

	if (m_pSystem)
	{
		m_pSystem->close(); // 시스템을 반드시 닫아주어야 한다.
		m_pSystem->release(); // 제거
	}
}

bool CResourceManager::Init()
{
	// FMOD System을 생성한다.
	System_Create(&m_pSystem);
	
	// FMOD를 초기화한다.
	m_pSystem->init(256, FMOD_INIT_NORMAL, nullptr);

	m_pSystem->getMasterChannelGroup(&m_pMasterGroup);

	// 채널 그룹을 만든다.
	CreateChannelGroup("BGM");
	CreateChannelGroup("Effect");
	CreateChannelGroup("UI");

	SetGroupVolume("BGM", 30);
	SetGroupVolume("Effect", 100);

	return true;
}

void CResourceManager::Update()
{
	m_pSystem->update();
}

bool CResourceManager::LoadTexture(const string& strName, 
	const TCHAR* pFileName, const string& strPathName)
{
	CTexture* pTexture = FindTexture(strName);

	if (pTexture)
	{
		SAFE_RELEASE(pTexture);
		return false;	
	}

	pTexture = new CTexture;

	if (!pTexture->LoadTexture(strName, pFileName, strPathName))
	{
		SAFE_RELEASE(pTexture);
		return false;
	}

	m_mapTexture.insert(make_pair(strName, pTexture));

	return true;
}

bool CResourceManager::LoadTexture(const string& strName,
	const vector<const TCHAR*>& vecFileName, const string& strPathName)
{
	CTexture* pTexture = FindTexture(strName);

	if (pTexture)
	{
		SAFE_RELEASE(pTexture);
		return false;
	}

	pTexture = new CTexture;

	if (!pTexture->LoadTexture(strName, vecFileName, strPathName))
	{
		SAFE_RELEASE(pTexture);
		return false;
	}

	m_mapTexture.insert(make_pair(strName, pTexture));

	return true;
}

bool CResourceManager::LoadTexture(const string& strName, 
	const TCHAR* pFileName, int iCount, const string& strPathName)
{
	CTexture* pTexture = FindTexture(strName);

	if (pTexture)
	{
		SAFE_RELEASE(pTexture);
		return false;
	}

	pTexture = new CTexture;

	if (!pTexture->LoadTexture(strName, pFileName, iCount, strPathName))
	{
		SAFE_RELEASE(pTexture);
		return false;
	}

	m_mapTexture.insert(make_pair(strName, pTexture));

	return true;
}

bool CResourceManager::LoadTextureFullPath(
	const string& strName, const TCHAR* pFullPath)
{
	CTexture* pTexture = FindTexture(strName);

	if (pTexture)
	{
		SAFE_RELEASE(pTexture);
		return false;
	}

	pTexture = new CTexture;

	if (!pTexture->LoadTextureFullPath(strName, pFullPath))
	{
		SAFE_RELEASE(pTexture);
		return false;
	}

	m_mapTexture.insert(make_pair(strName, pTexture));

	return true;
}

void CResourceManager::SetColorKey(const string& strName,
	unsigned char r, unsigned char g, unsigned char b, int iIndex)
{
	CTexture* pTexture = FindTexture(strName);

	if (!pTexture)
		return;

	pTexture->SetColorKey(r, g, b, iIndex);

	SAFE_RELEASE(pTexture);
}

void CResourceManager::SetColorKeyAll(const string& strName, 
	unsigned char r, unsigned char g, unsigned char b)
{
	CTexture* pTexture = FindTexture(strName);

	if (!pTexture)
		return;

	pTexture->SetColorKeyAll(r, g, b);

	SAFE_RELEASE(pTexture);
}

CTexture* CResourceManager::FindTexture(const string& strName)
{
	auto		iter = m_mapTexture.find(strName);

	if (iter == m_mapTexture.end())
		return nullptr;

	iter->second->AddRef();

	return iter->second;
}

void CResourceManager::ReleaseTexture(const string& strName)
{
	auto iter = m_mapTexture.find(strName);

	if (iter == m_mapTexture.end())
		return;

	// Release함수가 true를 반환하면 지워졌다는 것이다.
	if (iter->second->Release())
		m_mapTexture.erase(iter);
}

bool CResourceManager::CreateAnimationSequence(
	const string& strName, const string& strTexName, 
	ANIM_TYPE eType, ANIM_OPTION eOption,
	ANIM_PLAY_TYPE ePlayType, float fLoopTime, float fPlayRate,
	float fOptionTimeMax)
{
	CAnimationSequence* pAnimation = FindAnimationSequence(strName);

	if (pAnimation)
	{
		SAFE_RELEASE(pAnimation);
		return false;
	}

	pAnimation = new CAnimationSequence;

	if (!pAnimation->Init(strName, strTexName, eType, eOption, ePlayType,
		fLoopTime, fPlayRate, fOptionTimeMax))
	{
		SAFE_RELEASE(pAnimation);
		return false;
	}

	m_mapAnimationSequence.insert(make_pair(strName, pAnimation));

	return true;
}

bool CResourceManager::CreateAnimationSequence(const string& strName, const char* pFileName, const string& strPathName)
{
	CAnimationSequence* pAnimation = FindAnimationSequence(strName);

	if (pAnimation)
	{
		SAFE_RELEASE(pAnimation);
		return false;
	}

	pAnimation = new CAnimationSequence;

	if (!pAnimation->Init(strName, pFileName, strPathName))
	{
		SAFE_RELEASE(pAnimation);
		return false;
	}

	m_mapAnimationSequence.insert(make_pair(strName, pAnimation));

	return true;
}

bool CResourceManager::CreateAnimationSequence(const string& strName, FILE* pFile)
{
	CAnimationSequence* pAnimation = FindAnimationSequence(strName);

	if (pAnimation) // 있으면 로드안함.
	{
		SAFE_RELEASE(pAnimation);
		return false;
	}

	pAnimation = new CAnimationSequence;

	if (!pAnimation->Load(strName, pFile))
	{
		SAFE_RELEASE(pAnimation);
		return false;
	}

	m_mapAnimationSequence.insert(make_pair(strName, pAnimation));

	return true;
}

void CResourceManager::AddAnimationFrame(const string& strName, const Vector2& vStart, const Vector2& vEnd)
{
	CAnimationSequence* pAnimation = FindAnimationSequence(strName);

	if (!pAnimation)
		return;

	pAnimation->AddFrame(vStart, vEnd);

	SAFE_RELEASE(pAnimation);
}

void CResourceManager::AddAnimationFrame(const string& strName, const AnimationFrameInfo& tFrame)
{
	CAnimationSequence* pAnimation = FindAnimationSequence(strName);

	if (!pAnimation)
		return;

	pAnimation->AddFrame(tFrame);

	SAFE_RELEASE(pAnimation);
}

CAnimationSequence* CResourceManager::FindAnimationSequence(const string& strName)
{
	auto iter = m_mapAnimationSequence.find(strName);

	if (iter == m_mapAnimationSequence.end())
		return nullptr;

	iter->second->AddRef();

	return iter->second;
}

void CResourceManager::ReleaseAnimationSequence(const string& strName)
{
	auto		iter = m_mapAnimationSequence.find(strName);

	if (iter == m_mapAnimationSequence.end())
		return;

	// Release함수가 true를 반환하면 지워졌다는 것이다.
	if (iter->second->Release())
		m_mapAnimationSequence.erase(iter);
}

void CResourceManager::ReleaseAnimationSequence()
{
	auto iter = m_mapAnimationSequence.begin();
	auto iterEnd = m_mapAnimationSequence.end();

	for (; iter != iterEnd; ++iter)
	{
		iter->second->Release();
	}

	m_mapAnimationSequence.clear();
}

bool CResourceManager::LoadSound(const string& strGroup, 
	bool bLoop, const string& strName, const char* pFileName,
	const string& strPathName)
{
	CSound* pSound = FindSound(strName);

	if (pSound)
	{
		SAFE_RELEASE(pSound);
		return false;
	}

	ChannelGroup* pGroup = FindChannelGroup(strGroup);

	if (!pGroup)
		return false;

	pSound = new CSound;

	if (!pSound->LoadSound(m_pSystem, pGroup, bLoop, strName, pFileName,
		strPathName))
	{
		SAFE_RELEASE(pSound);
		return false;
	}

	m_mapSound.insert(make_pair(strName, pSound));

	return true;
}

CSound* CResourceManager::FindSound(const string& strName)
{
	auto	iter = m_mapSound.find(strName);

	if (iter == m_mapSound.end())
		return nullptr;

	iter->second->AddRef();

	return iter->second;
}

bool CResourceManager::CreateChannelGroup(
	const string& strName)
{
	ChannelGroup* pGroup = FindChannelGroup(strName);

	if (pGroup)
		return false;

	m_pSystem->createChannelGroup(strName.c_str(), &pGroup);

	m_pMasterGroup->addGroup(pGroup, false, 0);

	m_mapChannelGroup.insert(make_pair(strName, pGroup));

	return true;
}

ChannelGroup* CResourceManager::FindChannelGroup(const string& strName)
{
	auto	iter = m_mapChannelGroup.find(strName);

	if (iter == m_mapChannelGroup.end())
		return nullptr;

	return iter->second;
}

void CResourceManager::ReleaseSound(const string& strName)
{
	auto		iter = m_mapSound.find(strName);

	if (iter == m_mapSound.end())
		return;

	// Release함수가 true를 반환하면 지워졌다는 것이다.
	if (iter->second->Release())
		m_mapSound.erase(iter);
}

void CResourceManager::ReleaseChannelGroup(const string& strName)
{
	auto iter = m_mapChannelGroup.find(strName);

	if (iter == m_mapChannelGroup.end())
		return;

	iter->second->release();
	m_mapChannelGroup.erase(iter);
}

void CResourceManager::SetVolume(int iVolume)
{
	m_pMasterGroup->setVolume(iVolume / 100.f);
}

void CResourceManager::SetGroupVolume(const string& strGroup, int iVolume)
{
	ChannelGroup* pGroup = FindChannelGroup(strGroup);

	if (!pGroup)
		return;

	pGroup->setVolume(iVolume / 100.f);
}

bool CResourceManager::SoundPlay(const string& strName)
{
	CSound* pSound = FindSound(strName);

	if (!pSound)
		return false;

	pSound->Play();

	SAFE_RELEASE(pSound);

	return true;
}

bool CResourceManager::SoundStop(const string& strName)
{
	CSound* pSound = FindSound(strName);

	if (!pSound)
		return false;

	pSound->Stop();

	SAFE_RELEASE(pSound);

	return true;
}

bool CResourceManager::SoundPause(const string& strName)
{
	CSound* pSound = FindSound(strName);

	if (!pSound)
		return false;

	pSound->Pause();

	SAFE_RELEASE(pSound);

	return true;
}

bool CResourceManager::SoundResume(const string& strName)
{
	CSound* pSound = FindSound(strName);

	if (!pSound)
		return false;

	pSound->Resume();

	SAFE_RELEASE(pSound);

	return true;
}
