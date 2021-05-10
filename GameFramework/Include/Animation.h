#pragma once

#include "Game.h"

typedef struct _tagMotionInfo
{
	class CAnimationSequence* pSequence;
	int			iFrame;
	float			fCurrentTime;
	float			fGlobalTime;
	float			fFrameTime;
	float			fLoopTime;
	float			fOptionTime;
	float			fOptionTimeMax;
	float			fPlayRate;
}MotionInfo, *PMotionInfo;

class CAnimation
{
	friend class CObj;

private:
	CAnimation();
	CAnimation(const CAnimation& animation);
	~CAnimation();

private:
	class CScene* m_pScene;
	class CObj* m_pOwner;

private:
	unordered_map<string, PMotionInfo>	m_mapAnimationSequence;
	PMotionInfo m_pCurrent;
	PMotionInfo m_pDefault;

public:
	AnimationFrameInfo GetCurrnetFrameInfo();

public:
	bool Init();
	void AddSequence(const string& strName);
	void AddSequence(class CAnimationSequence* pSequence);
	void Change(const string& strName);
	void SetCurrent(const string& strName);
	void SetDefault(const string& strName);
	void SetPlayRate(const string& strName, float fPlayRate);
	void AddPlayRate(const string& strName, float fPlayRate);
	void Update(float fTime);
	CAnimation* Clone();

private:
	PMotionInfo FindMotionInfo(const string& strName);
	void CallNotifyTime(float fTime);
	void CallNotifyFrame(float fTime);
	void ClearNotify();

public:
	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}

	void SetOwner(class CObj* pOwner)
	{
		m_pOwner = pOwner;
	}
};

