#pragma once
#include "BlockObj.h"

class CWord :
    public CBlockObj
{
public:
	CWord();
	CWord(const CWord& obj);

protected:
	virtual ~CWord() = 0;

protected:
	WORD_TYPE m_eWordType;
	bool m_bConnected = false;

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
	virtual CWord* Clone() = 0;

public:
	WORD_TYPE GetWordType()
	{
		return m_eWordType;
	}

	void SetConnected(bool bConnected)
	{
		m_bConnected = bConnected;
	}
};

