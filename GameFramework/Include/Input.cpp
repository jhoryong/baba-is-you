#include "Input.h"
#include "Object/Mouse.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/Camera.h"

DEFINITION_SINGLE(CInput)

CInput::CInput()	:
	m_hWnd(nullptr),
	m_pMouseObj(nullptr),
	m_bLButtonClick(false),
	m_bRButtonClick(false)
{
}

CInput::~CInput()
{
	SAFE_RELEASE(m_pMouseObj);
	SAFE_DELETE_VECLIST(m_KeyList);
	SAFE_DELETE_MAP(m_mapAction);
	SAFE_DELETE_MAP(m_mapAxis);
}

void CInput::CreateMouse()
{
	m_pMouseObj = new CMouse;

	if (!m_pMouseObj->Init())
	{
		SAFE_RELEASE(m_pMouseObj);
		return;
	}

	m_pMouseObj->SetPos(m_vMousePos);

	ShowCursor(TRUE);
}

void CInput::Start()
{
	if (m_pMouseObj)
		m_pMouseObj->Start();
}

bool CInput::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	POINT	ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(m_hWnd, &ptMouse);

	m_vMousePos = ptMouse;

	AddActionKey("MouseLButton", VK_LBUTTON);
	AddActionKey("MouseRButton", VK_RBUTTON);

	AddBindAction("MouseLButton", KEY_TYPE::DOWN, this, &CInput::LButtonDown);
	AddBindAction("MouseLButton", KEY_TYPE::UP, this, &CInput::LButtonUp);

	AddBindAction("MouseRButton", KEY_TYPE::DOWN, this, &CInput::RButtonDown);
	AddBindAction("MouseRButton", KEY_TYPE::UP, this, &CInput::RButtonUp);

	return true;
}

void CInput::Update(float fTime)
{
	auto	iter = m_KeyList.begin();
	auto	iterEnd = m_KeyList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (GetAsyncKeyState((*iter)->cKey) & 0x8000)
		{
			(*iter)->bPush = true;
			(*iter)->fPushTime += fTime;
		}

		else
		{
			(*iter)->bPush = false;
			(*iter)->fPushTime = 0.f;
		}
	}

	UpdateAxis(fTime);
	UpdateAction(fTime);
	UpdateMouse(fTime);
}

void CInput::Render(HDC hDC, float fTime)
{
	m_pMouseObj->PrevRender(fTime);
	m_pMouseObj->Render(hDC, fTime);
}

void CInput::UpdateAxis(float fTime)
{
	auto	iter = m_mapAxis.begin();
	auto	iterEnd = m_mapAxis.end();

	for (; iter != iterEnd; ++iter)
	{
		iter->second->fScale = 0.f;

		size_t	iKeySize = iter->second->vecKey.size();

		for (size_t i = 0; i < iKeySize; ++i)
		{
			if (iter->second->vecKey[i].pInfo->bPush)
				iter->second->fScale += iter->second->vecKey[i].fScale;
		}

		size_t	iCallbackSize = iter->second->vecCallback.size();

		for (size_t i = 0; i < iCallbackSize; ++i)
		{
			iter->second->vecCallback[i](iter->second->fScale, fTime);
		}
	}
}

void CInput::UpdateAction(float fTime)
{
	bool	bUnionKey[(int)KEY_UNION::END] = {};
	char	cKey[(int)KEY_UNION::END] = { VK_CONTROL, VK_MENU, VK_SHIFT };

	for (int i = 0; i < (int)KEY_UNION::END; ++i)
	{
		if (GetAsyncKeyState(cKey[i]) & 0x8000)
		{
			bUnionKey[i] = true;
		}
	}

	auto	iter = m_mapAction.begin();
	auto	iterEnd = m_mapAction.end();

	for (; iter != iterEnd; ++iter)
	{
		size_t	iKeySize = iter->second->vecKey.size();

		for (size_t i = 0; i < iKeySize; ++i)
		{
			bool	bEnable = true;

			for (int j = 0; j < (int)KEY_UNION::END; ++j)
			{
				//  눌렀는데 키에서는 이 키를 안눌러야 할 경우 동작시키면 안된다.
				if (bUnionKey[j] != iter->second->vecKey[i].bKeyUnion[j])
				{
					bEnable = false;
					break;
				}
			}

			if (!bEnable)
				continue;


 			if (iter->second->vecKey[i].pInfo->bPush)
			{
				// 처음 눌렀는지 확인한다.
				if (!iter->second->vecKey[i].bPush)
				{
					iter->second->vecKey[i].bPush = true;

					size_t	iCallbackSize = iter->second->vecCallback[(int)KEY_TYPE::DOWN].size();

					for (size_t j = 0; j < iCallbackSize; ++j)
					{
						iter->second->vecCallback[(int)KEY_TYPE::DOWN][j](fTime);
					}
				}

				// 이전에 눌렀다면 누르고 있는 상태이다.
				else
				{
					size_t	iCallbackSize = iter->second->vecCallback[(int)KEY_TYPE::ON].size();

					for (size_t j = 0; j < iCallbackSize; ++j)
					{
						iter->second->vecCallback[(int)KEY_TYPE::ON][j](fTime);
 					}
				}
			}

			// 눌렀다가 떼는지를 확인한다.
			else
			{
				if (iter->second->vecKey[i].bPush)
				{
					iter->second->vecKey[i].bPush = false;

					size_t	iCallbackSize = iter->second->vecCallback[(int)KEY_TYPE::UP].size();

					for (size_t j = 0; j < iCallbackSize; ++j)
					{
						iter->second->vecCallback[(int)KEY_TYPE::UP][j](fTime);
					}
				}
			}
		}
	}
}

void CInput::UpdateMouse(float fTime)
{
	POINT	ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(m_hWnd, &ptMouse);

	Vector2	vCurMouse = ptMouse;

	m_vMouseMove = vCurMouse - m_vMousePos;

	m_vMousePos = vCurMouse;

	CScene* pScene = GET_SINGLE(CSceneManager)->GetScene();
	CCamera* pCamera = pScene->GetMainCamera();

	m_vMouseWorldPos = m_vMousePos + pCamera->GetPos();

	m_pMouseObj->SetPos(m_vMousePos);

	m_pMouseObj->Update(fTime);
}

void CInput::AddAxisKey(const string& strName, char cKey, float fScale)
{
	PBindAxis	pAxis = FindAxis(strName);

	if (!pAxis)
	{
		pAxis = new BindAxis;
		m_mapAxis.insert(make_pair(strName, pAxis));

		strcpy_s(pAxis->strName, strName.c_str());
	}

	PKeyInfo	pInfo = nullptr;

	auto	iter = m_KeyList.begin();
	auto	iterEnd = m_KeyList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->cKey == cKey)
		{
			pInfo = *iter;
			break;
		}
	}

	if (!pInfo)
	{
		pInfo = new KeyInfo;
		pInfo->cKey = cKey;
		m_KeyList.push_back(pInfo);
	}


	KeyAxis	tKey = {};
	tKey.pInfo = pInfo;
	tKey.fScale = fScale;
	pAxis->vecKey.push_back(tKey);	
}

void CInput::AddBindAxis(const string& strName, void(*pFunc)(float, float))
{
	PBindAxis pAxis = FindAxis(strName);

	if (!pAxis)
	{
		pAxis = new BindAxis;
		strcpy_s(pAxis->strName, strName.c_str());
		m_mapAxis.insert(make_pair(strName, pAxis));
	}

	pAxis->vecCallback.push_back(bind(pFunc, placeholders::_1, placeholders::_2));

}

void CInput::AddActionKey(const string& strName, char cKey)
{
	PBindAction	pAction = FindAction(strName);

	if (!pAction)
	{
		pAction = new BindAction;
		m_mapAction.insert(make_pair(strName, pAction));

		strcpy_s(pAction->strName, strName.c_str());
	}

	PKeyInfo	pInfo = nullptr;

	auto	iter = m_KeyList.begin();
	auto	iterEnd = m_KeyList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->cKey == cKey)
		{
			pInfo = *iter;
			break;
		}
	}

	if (!pInfo)
	{
		pInfo = new KeyInfo;
		pInfo->cKey = cKey;
		m_KeyList.push_back(pInfo);
	}

	KeyAction	tKey = {};
	tKey.pInfo = pInfo;
	pAction->vecKey.push_back(tKey);
}

void CInput::AddActionKeyUnion(const string& strName, char cKey,
	KEY_UNION eType)
{
	PBindAction	pAction = FindAction(strName);

	if (!pAction)
	{
		pAction = new BindAction;
		m_mapAction.insert(make_pair(strName, pAction));

		strcpy_s(pAction->strName, strName.c_str());
	}

	PKeyInfo	pInfo = nullptr;

	auto	iter = m_KeyList.begin();
	auto	iterEnd = m_KeyList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->cKey == cKey)
		{
			pInfo = *iter;
			break;
		}
	}

	if (!pInfo)
	{
		pInfo = new KeyInfo;
		pInfo->cKey = cKey;
		m_KeyList.push_back(pInfo);
	}

	if (pAction->vecKey.empty())
	{
		KeyAction	tKey = {};
		tKey.pInfo = pInfo;
		pAction->vecKey.push_back(tKey);
	}

	// 등록되어 있는 키 수만큼 반복하며 키를 찾는다.
	size_t	iKeySize = pAction->vecKey.size();

	for (size_t i = 0; i < iKeySize; ++i)
	{
		if (pAction->vecKey[i].pInfo->cKey == cKey)
		{
			pAction->vecKey[i].bKeyUnion[(int)eType] = true;
			break;
		}
	}
}

void CInput::AddBindAction(const string& strName, KEY_TYPE eType, 
	void(*pFunc)(float))
{
	PBindAction pAction = FindAction(strName);

	if (!pAction)
	{
		pAction = new BindAction;
		strcpy_s(pAction->strName, strName.c_str());
		m_mapAction.insert(make_pair(strName, pAction));
	}

	pAction->vecCallback[(int)eType].push_back(bind(pFunc, placeholders::_1));
}

void CInput::DeleteBindAction(const string& strName)
{
	auto iter = m_mapAction.find(strName);

	if (iter != m_mapAction.end())
	{
		SAFE_DELETE(iter->second);
		m_mapAction.erase(iter);
	}
}

PBindAxis CInput::FindAxis(const string& strName)
{
	auto	iter = m_mapAxis.find(strName);

	if (iter == m_mapAxis.end())
		return nullptr;

	return iter->second;
}

PBindAction CInput::FindAction(const string& strName)
{
	auto	iter = m_mapAction.find(strName);

	if (iter == m_mapAction.end())
		return nullptr;

	return iter->second;
}

void CInput::LButtonDown(float fTime)
{
	m_bLButtonClick = true;
}

void CInput::RButtonDown(float fTime)
{
	m_bRButtonClick = true;
}

void CInput::LButtonUp(float fTime)
{
	m_bLButtonClick = false;
}

void CInput::RButtonUp(float fTime)
{
	m_bRButtonClick = false;
}
