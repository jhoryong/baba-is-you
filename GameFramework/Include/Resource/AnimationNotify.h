#pragma once

#include "../Game.h"

typedef struct _tagNotifyCallback
{
	function<void(float)>	func;
	void* pObj = nullptr;
	void* pFunc = nullptr;
}NotifyCallback, *PNotifyCallback;

class CAnimationNotify
{
	friend class CAnimation;
	friend class CAnimationSequence;

private:
	CAnimationNotify();
	~CAnimationNotify();

private:
	list<PNotifyCallback>		m_CallbackList;
	string		m_strName;
	int			m_iFrame;
	float			m_fNotifyTime;
	bool			m_bCall;

public:
	void SetFrame(int iFrame)
	{
		m_iFrame = iFrame;
	}

	void SetTime(float fTime)
	{
		m_fNotifyTime = fTime;
	}

public:
	void AddNotifyCallback(void(*pFunc)(float));
	template <typename T>
	void AddNotifyCallback(T* pObj, void(T::* pFunc)(float))
	{
		PNotifyCallback	pCallback = new NotifyCallback;
		pCallback->func = bind(pFunc, pObj, placeholders::_1);
		pCallback->pObj = pObj;
		//pCallback->pFunc = (void*)pFunc;

		m_CallbackList.push_back(pCallback);
	}

	void DeleteNotifyCallback(void(*pFunc)(float));

	template <typename T>
	void DeleteNotifyCallback(T* pObj, void(T::*pFunc)(float))
	{
		auto	iter = m_CallbackList.begin();
		auto	iterEnd = m_CallbackList.end();

		for (; iter != iterEnd;)
		{
			if ((*iter)->pObj == pObj)
			{
				SAFE_DELETE((*iter));
				iter = m_CallbackList.erase(iter);
				iterEnd = m_CallbackList.end();
				continue;
			}

			++iter;
		}
	}

	void Call(float fTime);
};

