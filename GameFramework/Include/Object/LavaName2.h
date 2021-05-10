#pragma once
#include "Name.h"
class CLavaName2 :
    public CName
{
public:
	CLavaName2();
	CLavaName2(const CLavaName2& obj);

protected:
	virtual ~CLavaName2();

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
	virtual CLavaName2* Clone();
};

