#pragma once
#include "UI.h"
class CUIBaba :
    public CUI
{
public:
	CUIBaba();
	virtual ~CUIBaba();

private:
	string m_strAnimationName;
	float m_fWait = 0.2f;
	float m_fWaitAcc = 0.f;

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
	virtual CUIBaba* Clone();

public:
	void AddAnimation(const string& strName);

private:
	void MoveUp(float fTime);
	void MoveUpOn(float fTime);
	void MoveEnd(float fTime);
	void MoveDown(float fTime);
	void MoveDownOn(float fTime);
	void MenuKeyboardSelect(float fTime);
	void PlayButtonSound();
};

