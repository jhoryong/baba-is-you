#pragma once
#include "Character.h"
class CLockDoor :
    public CCharacter
{
public:
	CLockDoor();
	CLockDoor(const CLockDoor& obj);

protected:
	virtual ~CLockDoor();

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
	virtual CLockDoor* Clone();
};

