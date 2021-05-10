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
	class CMapToolDlg* m_pMapToolDlg; // ���̾�α� ��ü

public:
	virtual bool Init();
	virtual void Start();
	virtual void Update(float fTime); // Ÿ�� ���� ����̴�.

public:
	virtual void LoadTexture();
	virtual void LoadAnimation();
	virtual void AddPrototype();
	virtual class CBlockObj* CreateBlockObj(const char* cName);

public:
	CObj* FindObject(int iIndex_X, int iIndex_Y);
	void SaveObjectList(FILE* pFile);

private:
	void MoveUPDown(float fScale, float fTime); // ī�޶��̵�
	void MoveSide(float fScale, float fTime); // ī�޶��̵�
	void OnMapToolEditor(float fTime); // ctrl + m �� ������ ����ȴ�.
	void PlaceObject();
	void EraseObject();
};

