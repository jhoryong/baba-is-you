#pragma once
#include "UI.h"

// 충돌 기능이 있는 이미지 클래스이다.

class CUIImage :
	public CUI
{
public:
	CUIImage();
	virtual ~CUIImage();

private:
	string m_strAnimationName;

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
	virtual CUIImage* Clone();

public:
	void AddAnimation(const string& strName);
};

