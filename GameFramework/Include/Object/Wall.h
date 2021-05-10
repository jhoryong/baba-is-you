#pragma once
#include "Character.h"
class CWall :
    public CCharacter
{
public:
	CWall();
	CWall(const CWall& obj);

protected:
	virtual ~CWall();

private:
	int	 m_iWallType; /* 0 ~ 15 */
	bool m_bLeft = false;
	bool m_bRight = false;
	bool m_bUp = false;
	bool m_bDown = false;

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
	virtual CWall* Clone();

public:
	virtual void RegisterKey();

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

private:
	void CheckWall();
	void SetWallType();
	void ChangeWallAnimation();
};

