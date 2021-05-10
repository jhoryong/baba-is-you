#include "AnimationNotify.h"

CAnimationNotify::CAnimationNotify()	:
	m_iFrame(-1),
	m_fNotifyTime(-1.f),
	m_bCall(false)
{
}

CAnimationNotify::~CAnimationNotify()
{
	SAFE_DELETE_VECLIST(m_CallbackList);
}

void CAnimationNotify::AddNotifyCallback(void(*pFunc)(float))
{
	PNotifyCallback	pCallback = new NotifyCallback;
	pCallback->func = bind(pFunc, placeholders::_1);
	pCallback->pObj = nullptr;
	pCallback->pFunc = (void*)pFunc;

	m_CallbackList.push_back(pCallback);
}

void CAnimationNotify::DeleteNotifyCallback(void(*pFunc)(float))
{
	auto	iter = m_CallbackList.begin();
	auto	iterEnd = m_CallbackList.end();

	for (; iter != iterEnd;)
	{
		if ((*iter)->pFunc == (void*)pFunc)
		{
			SAFE_DELETE((*iter));
			iter = m_CallbackList.erase(iter);
			iterEnd = m_CallbackList.end();
			continue;
		}

		++iter;
	}
}

void CAnimationNotify::Call(float fTime)
{
	if (m_bCall)
		return;

	auto	iter = m_CallbackList.begin();
	auto	iterEnd = m_CallbackList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->func(fTime);
	}

	m_bCall = true;
}
