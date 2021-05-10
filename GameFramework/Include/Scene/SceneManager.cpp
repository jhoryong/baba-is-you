
#include "SceneManager.h"
#include "SceneStart.h"

DEFINITION_SINGLE(CSceneManager)

CSceneManager::CSceneManager()	:
	m_pCurrentScene(nullptr),
	m_pNextScene(nullptr)
{
}

CSceneManager::~CSceneManager()
{
	SAFE_DELETE(m_pNextScene);
	SAFE_DELETE(m_pCurrentScene);
}

bool CSceneManager::Init()
{
	//m_pScene = new CSceneMain;
	m_pCurrentScene = new CSceneStart;

	if (!m_pCurrentScene->Init())
	{
		return false;
	}

	GET_SINGLE(CInput)->CreateMouse();

	m_pCurrentScene->Start();

	GET_SINGLE(CInput)->Start();

	return true;
}

bool CSceneManager::Update(float fTime)
{
	m_pCurrentScene->Update(fTime);

	return ChangeScene();
}

bool CSceneManager::PostUpdate(float fTime)
{
	m_pCurrentScene->PostUpdate(fTime);

	return ChangeScene();
}

bool CSceneManager::Collision(float fTime)
{
	m_pCurrentScene->Collision(fTime);

	return ChangeScene();
}

void CSceneManager::PrevRender(float fTime)
{
	m_pCurrentScene->PrevRender(fTime);
}

void CSceneManager::Render(HDC hDC, float fTime)
{
	m_pCurrentScene->Render(hDC, fTime);
}

void CSceneManager::PostRender(float fTime)
{
	m_pCurrentScene->PostRender(fTime);
}

bool CSceneManager::ChangeScene()
{
	if (m_pNextScene)
	{
		SAFE_DELETE(m_pCurrentScene);
		m_pCurrentScene = m_pNextScene;
		m_pNextScene = nullptr;

		m_pCurrentScene->Start();

		GET_SINGLE(CInput)->Start();

		return true;
	}

	return false;
}
