#pragma once

#include "../Game.h"
#include "../Input.h"
#include "Scene.h"

class CSceneManager
{
	DECLARE_SINGLE(CSceneManager)

private:
	class CScene* m_pCurrentScene; // ÇöÀç Scene
	class CScene* m_pNextScene;
	int		m_iCurrentLevel = 0;
	bool m_bClear[8] = {};

public:
	bool Init();
	bool Update(float fTime);
	bool PostUpdate(float fTime);
	bool Collision(float fTime);
	void PrevRender(float fTime);
	void Render(HDC hDC, float fTime);
	void PostRender(float fTime);

private:
	bool ChangeScene();

public:
	template <typename T>
	T* CreateNextScene()
	{
		m_pNextScene = new T;

		if (!m_pNextScene->Init())
		{
			return nullptr;
		}

		return (T*)m_pNextScene;
	}

public:
	class CScene* GetScene() const
	{
		return m_pCurrentScene;
	}

public:
	void SetCurrentLevel(int iLevel)
	{
		m_iCurrentLevel = iLevel;
	}

	int GetCurrentLevel()
	{
		return m_iCurrentLevel;
	}

	void SetClear(int iLevel)
	{
		m_bClear[iLevel] = true;
	}

	bool GetClear(int iLevel)
	{
		return m_bClear[iLevel];
	}
};

