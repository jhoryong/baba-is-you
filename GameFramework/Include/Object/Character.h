#pragma once
#include "BlockObj.h"


class CCharacter :
    public CBlockObj
{
public:
	CCharacter();
	CCharacter(const CCharacter& obj);

protected:
	virtual ~CCharacter() = 0;

protected:
	CHARACTER_TYPE	m_eCharacterType;
	vector<class CName*> m_vecName;
	//class CName*	m_pName;
	float	m_fWait;
	float	m_fWaitAcc;
	bool	m_bPush = false;
	int	m_bKeyRegisterCount = 0;

	NAME_TYPE m_eNameRight = NAME_TYPE::END;
	NAME_TYPE m_eNameBottom = NAME_TYPE::END;

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
	virtual CCharacter* Clone() = 0;

private:
	void ClearState();
	void CheckNoneState();
	void CheckWinState(float fTime);
	void CheckNameConnection();
	void ChangeObject(NAME_TYPE eNameType);

public:
	virtual void MoveLeft(float fTime);
	virtual void MoveRight(float fTime);
	virtual void MoveUp(float fTime);
	virtual void MoveDown(float fTime);

	virtual void MoveLeftOn(float fTime);
	virtual void MoveRightOn(float fTime);
	virtual void MoveUpOn(float fTime);
	virtual void MoveDownOn(float fTime);

	virtual void MoveEnd(float fTime);

protected:
	void SoundPlay();

public:
	virtual void RegisterKey();

public:
	CHARACTER_TYPE GetCharacterType()
	{
		return m_eCharacterType;
	}

	void SetState(STATE_TYPE eStateType)
	{
		if (eStateType == STATE_TYPE::END)
			return;

		m_bState[(int)eStateType] = true;
	}

	void SetNameRight(NAME_TYPE eNameType)
	{
		if (eNameType == NAME_TYPE::END)
			return;

		m_eNameRight = eNameType;
	}

	void SetNameBottom(NAME_TYPE eNameType)
	{
		if (eNameType == NAME_TYPE::END)
			return;

		m_eNameBottom = eNameType;
	}
};


