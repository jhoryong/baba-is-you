#pragma once
#include "UI.h"

// �浹 ����� ���� ������ ��� �̹����� Ŭ�����̴�.

class CUIBackground :
    public CUI
{
public:
	CUIBackground();
	virtual ~CUIBackground();

public:
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
	virtual CUIBackground* Clone();

public:
	void AddAnimation(const string& strName);
};

