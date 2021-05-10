#include "AnimationSequence.h"

#include "Texture.h"
#include "ResourceManager.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Resource/ResourceManager.h"
#include "../PathManager.h"

CAnimationSequence::CAnimationSequence()	:
	m_pTexture(nullptr),
	m_eAnimType(ANIM_TYPE::ATLAS),
	m_eOption(ANIM_OPTION::LOOP),
	m_ePlayType(ANIM_PLAY_TYPE::NORMAL),
	m_iCurrentFrame(0),
	m_fLoopTime(1.f),
	m_fFrameTime(1.f),
	m_fCurrentTime(0.f),
	m_fOptionTime(0.f),
	m_fOptionTimeMax(1.f),
	m_fPlayRate(1.f)
{
}

CAnimationSequence::CAnimationSequence(const CAnimationSequence& sequence)
{
	*this = sequence;

	if (m_pTexture)
		m_pTexture->AddRef();
}

CAnimationSequence::~CAnimationSequence()
{
	SAFE_DELETE_MAP(m_mapNotify);
	//SAFE_RELEASE(m_pTexture);

	//string	strName = m_pTexture->GetName();
	//if (m_pTexture->Release())
	//	GET_SINGLE(CResourceManager)->ReleaseTexture(strName);
	m_pTexture->Release();
}

CTexture* CAnimationSequence::GetTexture() const
{
	m_pTexture->AddRef();
	return m_pTexture;
}

void CAnimationSequence::Save(FILE* pFile)
{
	char strName[64] = {};
	strcpy(strName, m_strName.c_str());
	size_t iLength = strlen(strName);
	fwrite(&iLength, sizeof(size_t), 1, pFile);
	fwrite(&strName, sizeof(char), iLength, pFile);

	m_pTexture->Save(pFile);

	size_t iSize = m_vecFrame.size();
	fwrite(&iSize, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < iSize; ++i)
	{
		fwrite(&m_vecFrame[i], sizeof(AnimationFrameInfo), 1, pFile);
	}

	fwrite(&m_eAnimType, sizeof(ANIM_TYPE), 1, pFile);
	fwrite(&m_eOption, sizeof(ANIM_OPTION), 1, pFile);
	fwrite(&m_ePlayType, sizeof(ANIM_PLAY_TYPE), 1, pFile);
	fwrite(&m_iCurrentFrame, sizeof(int), 1, pFile);
	fwrite(&m_fLoopTime, sizeof(float), 1, pFile);
	fwrite(&m_fFrameTime, sizeof(float), 1, pFile);
	fwrite(&m_fCurrentTime, sizeof(float), 1, pFile);
	fwrite(&m_fOptionTime, sizeof(float), 1, pFile);
	fwrite(&m_fOptionTimeMax, sizeof(float), 1, pFile);
	fwrite(&m_fPlayRate, sizeof(float), 1, pFile);
}

bool CAnimationSequence::Load(const string& strName, FILE* pFile)
{
	m_strName = strName;

	// Texture
	size_t iLength = 0;
	fread(&iLength, sizeof(size_t), 1, pFile);

	char strName1[64] = {};

	fread(strName1, 1, iLength, pFile);

	SetTexture(strName1);

	size_t iSize = 0;
	fread(&iSize, sizeof(size_t), 1, pFile);
	for (size_t i = 0; i < iSize; ++i)
	{
		AnimationFrameInfo Info = {};
		fread(&Info, sizeof(AnimationFrameInfo), 1, pFile);
		m_vecFrame.push_back(Info);
	}

	fread(&m_eAnimType, sizeof(ANIM_TYPE), 1, pFile);
	fread(&m_eOption, sizeof(ANIM_OPTION), 1, pFile);
	fread(&m_ePlayType, sizeof(ANIM_PLAY_TYPE), 1, pFile);
	fread(&m_iCurrentFrame, sizeof(int), 1, pFile);
	fread(&m_fLoopTime, sizeof(float), 1, pFile);
	fread(&m_fFrameTime, sizeof(float), 1, pFile);
	fread(&m_fCurrentTime, sizeof(float), 1, pFile);
	fread(&m_fOptionTime, sizeof(float), 1, pFile);
	fread(&m_fOptionTimeMax, sizeof(float), 1, pFile);
	fread(&m_fPlayRate, sizeof(float), 1, pFile);

	return true;
}

bool CAnimationSequence::SetTexture(const string& strName)
{
	SAFE_RELEASE(m_pTexture);

	m_pTexture = GET_SINGLE(CResourceManager)->FindTexture(strName);

	return true;
}

bool CAnimationSequence::Init(const string& strName,
	const string& strTexName, ANIM_TYPE eType,
	ANIM_OPTION eOption, ANIM_PLAY_TYPE ePlayType, 
	float fLoopTime, float fPlayRate, float fOptionTimeMax)
{
	SetName(strName);
	m_pTexture = GET_SINGLE(CResourceManager)->FindTexture(strTexName);

	m_eAnimType = eType;
	m_eOption = eOption;
	m_ePlayType = ePlayType;
	
	m_fLoopTime = fLoopTime;

	if (!m_vecFrame.empty())
		m_fFrameTime = m_fLoopTime / m_vecFrame.size();

	m_fOptionTimeMax = fOptionTimeMax;
	m_fPlayRate = fPlayRate;

	return true;
}

bool CAnimationSequence::Init(const string& strName, 
	const char* pFileName, const string& strPathName)
{
	const TCHAR* pPath = GET_SINGLE(CPathManager)->FindPath(strPathName);

	char strFullPath[MAX_PATH] = {};

#ifdef UNICODE
	int iLength = WideCharToMultiByte(CP_ACP, 0, pPath, -1, nullptr, 0, nullptr, nullptr);
	WideCharToMultiByte(CP_ACP, 0, pPath, -1, strFullPath, iLength, nullptr, nullptr);
#else
	strcpy_s(strFullPath, pPath);
#endif // UNICODE

	strcat(strFullPath, pFileName);

	FILE* pFile = nullptr;

	fopen_s(&pFile, strFullPath, "rb");
	
	if (!pFile)
		return false;

	size_t iLen = 0;
	fread(&iLen, sizeof(size_t), 1, pFile);

	char strName1[64] = {};
	fread(&strName1, sizeof(char), iLen, pFile);
	
	if (strName != strName1)
		return false;

	Load(strName, pFile);

	fclose(pFile);

	return true;
}

void CAnimationSequence::AddFrame(const Vector2& vStart, 
	const Vector2& vEnd)
{
	AnimationFrameInfo	tFrame;
	tFrame.vStart = vStart;
	tFrame.vEnd = vEnd;

	m_vecFrame.push_back(tFrame);

	if (!m_vecFrame.empty())
		m_fFrameTime = m_fLoopTime / m_vecFrame.size();

}

void CAnimationSequence::AddFrame(const AnimationFrameInfo& tFrame)
{
	m_vecFrame.push_back(tFrame);
}

void CAnimationSequence::AddNotify(const string& strName, int iFrame)
{
	CAnimationNotify* pNotify = FindNotify(strName);

	if (pNotify)
		return;

	pNotify = new CAnimationNotify;

	pNotify->SetFrame(iFrame);

	m_mapNotify.insert(make_pair(strName, pNotify));
}

void CAnimationSequence::AddNotify(const string& strName, float fTime)
{
	CAnimationNotify* pNotify = FindNotify(strName);

	if (pNotify)
		return;

	pNotify = new CAnimationNotify;

	pNotify->SetTime(fTime);

	m_mapNotify.insert(make_pair(strName, pNotify));
}

void CAnimationSequence::AddNotifyFunction(const string& strName, 
	void(*pFunc)(float))
{
	CAnimationNotify* pNotify = FindNotify(strName);

	if (!pNotify)
		return;

	pNotify->AddNotifyCallback(pFunc);
}

void CAnimationSequence::DeleteNotifyFunction(const string& strName, 
	void(*pFunc)(float))
{
	CAnimationNotify* pNotify = FindNotify(strName);

	if (!pNotify)
		return;

	pNotify->DeleteNotifyCallback(pFunc);
}

CAnimationNotify* CAnimationSequence::FindNotify(const string& strName)
{
	auto	iter = m_mapNotify.find(strName);

	if (iter == m_mapNotify.end())
		return nullptr;

	return iter->second;
}

void CAnimationSequence::Update(float fTime)
{
}

CAnimationSequence* CAnimationSequence::Clone()
{
	return new CAnimationSequence(*this);
}
