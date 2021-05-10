#pragma once
#include "Character.h"
class CSelector :
    public CCharacter
{
public:
	CSelector();
	CSelector(const CSelector& obj);

protected:
	virtual ~CSelector();

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
	virtual CSelector* Clone();

public:
	void SetSelectorPos(int iLevel);

private:
	virtual void MoveLeft(float fTime);
	virtual void MoveRight(float fTime);
	virtual void MoveUp(float fTime);
	virtual void MoveDown(float fTime);

	virtual void MoveLeftOn(float fTime);
	virtual void MoveRightOn(float fTime);
	virtual void MoveUpOn(float fTime);
	virtual void MoveDownOn(float fTime);

	virtual void MoveEnd(float fTime);
	void EnterStage(float fTime);
};

