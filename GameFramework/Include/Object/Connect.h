#pragma once
#include "Word.h"

//enum class CONNECT_TYPE
//{
//	IS,
//	AND
//};

class CConnect :
    public CWord
{
public:
	CConnect();
	CConnect(const CConnect& obj);

protected:
	virtual ~CConnect() = 0;

protected:
	CONNECT_TYPE m_eConnectType = CONNECT_TYPE::END;
	bool m_bHorizontal = false;
	bool m_bVertical = false;

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
	virtual CConnect* Clone() = 0;

private:
	virtual void CheckConnection();
};

