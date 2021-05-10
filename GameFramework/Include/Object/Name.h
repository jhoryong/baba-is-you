#pragma once
#include "Word.h"


// Name ���� �浹�� �Ͼ�ٸ� right bottom ���� Connect �� �ִ��� �ѹ� Ȯ���Ѵ�.
// �浹���� ����ٸ� �ٽ� Ȯ���Ѵ�.
// Connect �� �ִٸ� Connect �� State �� �ִ��� Ȯ���Ѵ�.
// �ִٸ� �� State �� �����´�.
// NONE State Ŭ������ ���⶧���� ���⼭ ó������ �ʰ�, ĳ���Ͱ� ��ȿ�� �˻��Ҷ� �ڽ��� Name �� �ƹ��� State�� ã�� 
//���ߴٸ� NONE �� �ο��Ѵ�.

class CName :
    public CWord
{
public:
	CName();
	CName(const CName& obj);

protected:
	virtual ~CName() = 0;

protected:
	NAME_TYPE	m_eNameType;	

	STATE_TYPE	m_eStateRight;
	STATE_TYPE	m_eStateBottom;
	STATE_TYPE	m_eStateRightPrev;
	STATE_TYPE	m_eStateBottomPrev;

	NAME_TYPE	m_eNameRight;
	NAME_TYPE	m_eNameBottom;
	NAME_TYPE	m_eNameRightPrev;
	NAME_TYPE	m_eNameBottomPrev;

	bool m_bSoundHR = true; 
	bool m_bSoundVB = true;

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
	virtual CName* Clone() = 0;

private:
	virtual void CheckConnection();
	void SoundPlay();
	

public:
	NAME_TYPE GetNameType()
	{
		return m_eNameType;
	}

	STATE_TYPE GetRightState()
	{
		return m_eStateRight;
	}

	STATE_TYPE GetBottomState()
	{
		return m_eStateBottom;
	}

	NAME_TYPE GetNameRight()
	{
		return m_eNameRight;
	}

	NAME_TYPE GetNameBottom()
	{
		return m_eNameBottom;
	}
};

