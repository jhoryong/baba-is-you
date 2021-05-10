#pragma once
#include "Word.h"


// Name 블럭은 충돌이 일어났다면 right bottom 블럭에 Connect 가 있는지 한번 확인한다.
// 충돌에서 벗어났다면 다시 확인한다.
// Connect 가 있다면 Connect 에 State 가 있는지 확인한다.
// 있다면 그 State 를 가져온다.
// NONE State 클래스는 없기때문에 여기서 처리하지 않고, 캐릭터가 유효성 검사할때 자신의 Name 에 아무런 State를 찾지 
//못했다면 NONE 을 부여한다.

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

