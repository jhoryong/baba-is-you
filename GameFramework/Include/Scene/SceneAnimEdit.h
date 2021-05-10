#pragma once
#include "Scene.h"
class CSceneAnimEdit :
    public CScene
{
	friend class CSceneManager;

protected:
	CSceneAnimEdit();
	virtual ~CSceneAnimEdit();

private:
	class CAnimationToolDlg* m_pAnimationToolDlg;
	

public:
	virtual bool Init();
	virtual void Start();
	void DeleteAllObject();
	void ReleaseAnimationSequence();

private:
	void LoadTexture();

private:
	void MoveUPDown(float fScale, float fTime); // ī�޶��̵�
	void MoveSide(float fScale, float fTime); // ī�޶��̵�
	void OnAnimationToolEditor(float fTime); 
	
};

