#pragma once
#include "State.h"
class CPush :
    public CState
{
public:
	CPush();
	CPush(const CPush& obj);

protected:
	virtual ~CPush();

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
	virtual CPush* Clone();
};

