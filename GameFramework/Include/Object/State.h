#pragma once
#include "Word.h"

class CState :
    public CWord
{
public:
	CState();
	CState(const CState& obj);

protected:
	virtual ~CState();

protected:
	STATE_TYPE m_eStateType;

public:
	virtual bool Init();
	virtual bool Init(const char* pFileName,
		const string& strPathName = DATA_PATH);
	virtual void Start();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void PrevRender(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual void PostRender(float fTime);
	virtual CState* Clone() = 0;

private:
	virtual void CheckConnection();

public:
	STATE_TYPE GetStateType()
	{
		return m_eStateType;
	}
};

