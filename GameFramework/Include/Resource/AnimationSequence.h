#pragma once

#include "../Ref.h"
#include "AnimationNotify.h"

// 이 클래스는 하나의 모션을 의미한다.
class CAnimationSequence	:
	public CRef
{
	friend class CResourceManager;
	friend class CAnimation;

private:
	CAnimationSequence();
	CAnimationSequence(const CAnimationSequence& sequence);
	~CAnimationSequence();

private:
	class CTexture* m_pTexture;
	vector<AnimationFrameInfo>	m_vecFrame;
	ANIM_TYPE		m_eAnimType;
	ANIM_OPTION		m_eOption;
	ANIM_PLAY_TYPE	m_ePlayType;
	int			m_iCurrentFrame;
	float		m_fLoopTime;
	float		m_fFrameTime;
	float		m_fCurrentTime;
	float		m_fOptionTime;
	float		m_fOptionTimeMax;
	float		m_fPlayRate;

private:
	unordered_map<string, class CAnimationNotify*>	m_mapNotify;

public:
	bool Init(const string& strName, const string& strTexName,
		ANIM_TYPE eType, ANIM_OPTION eOption,
		ANIM_PLAY_TYPE ePlayType, float fLoopTime,
		float fPlayRate = 1.f, float fOptionTimeMax = 1.f);
	bool Init(const string& strName, const char* pFileName,
		const string& strPathName = SEQUENCE_PATH);
	void AddFrame(const Vector2& vStart, const Vector2& vEnd);
	void AddFrame(const AnimationFrameInfo& tFrame);

public:
	void AddNotify(const string& strName, int iFrame);
	void AddNotify(const string& strName, float fTime);
	void AddNotifyFunction(const string& strName,
		void (*pFunc)(float));
	template <typename T>
	void AddNotifyFunction(const string& strName, T* pObj,
		void (T::*pFunc)(float))
	{
		CAnimationNotify* pNotify = FindNotify(strName);

		if (!pNotify)
			return;

		pNotify->AddNotifyCallback<T>(pObj, pFunc);
	}
	void DeleteNotifyFunction(const string& strName,
		void (*pFunc)(float));
	template <typename T>
	void DeleteNotifyFunction(const string& strName, T* pObj,
		void (T::* pFunc)(float))
	{
		CAnimationNotify* pNotify = FindNotify(strName);

		if (!pNotify)
			return;

		pNotify->DeleteNotifyCallback<T>(pObj, pFunc);
	}

private:
	class CAnimationNotify* FindNotify(const string& strName);

public:
	void Update(float fTime);
	CAnimationSequence* Clone();

public:
	class CTexture* GetTexture()	const;
	ANIM_TYPE GetAnimType()	const
	{
		return m_eAnimType;
	}

public:
	void Save(FILE* pFile);
	bool Load(const string& strName, FILE* pFile);
	bool SetTexture(const string& strName);
};

