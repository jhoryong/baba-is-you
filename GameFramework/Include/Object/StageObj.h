#pragma once
#include "Obj.h"

// Stage 는 오브젝트들의 배치 정보를 가지고 있다.

class CStageObj :
    public CObj
{
public:
	CStageObj();
	virtual ~CStageObj();

private:
	vector<list<class CBlockObj*>> m_listVector;
	list<class CCharacter*> m_listCharacter;
	list<class CName> m_listWord;
	list<class CConnect*> m_listConnect;
	list<class CState*> m_listState;

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
	virtual CStageObj* Clone();

public:
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};

