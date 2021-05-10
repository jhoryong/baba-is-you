#pragma once
#include "Scene.h"
class CSceneEdit :
	public CScene
{
	friend class CSceneManager;

protected:
	CSceneEdit();
	virtual ~CSceneEdit();

private:
	class CMapToolDlg* m_pMapToolDlg; // 다이얼로그 객체

public:
	virtual bool Init();
	virtual void Start();
	virtual void Update(float fTime); // 타일 편집 기능이다.

public:
	virtual void LoadTexture();
	virtual void LoadAnimation();
	virtual void AddPrototype();
	virtual class CBlockObj* CreateBlockObj(const char* cName);

public:
	CObj* FindObject(int iIndex_X, int iIndex_Y);
	void SaveObjectList(FILE* pFile);

private:
	void MoveUPDown(float fScale, float fTime); // 카메라이동
	void MoveSide(float fScale, float fTime); // 카메라이동
	void OnMapToolEditor(float fTime); // ctrl + m 을 누르면 실행된다.
	void PlaceObject();
	void EraseObject();
};

