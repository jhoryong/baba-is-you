#pragma once

#include "Game.h"
#include "Ref.h"
#include "Object/Obj.h"

enum class KEY_TYPE
{
	DOWN,
	ON,
	UP,
	DBCLICK,
	END
};

enum class KEY_UNION
{
	CONTROL,
	ALT,
	SHIFT,
	END
};

typedef struct _tagKeyInfo
{
	char		cKey;
	float		fPushTime;
	bool		bPush;

	_tagKeyInfo()
	{
		cKey = 0;
		fPushTime = 0.f;
		bPush = false;
	}
}KeyInfo, *PKeyInfo;

typedef struct _tagKeyAxis
{
	PKeyInfo	pInfo;
	float		fScale;

	_tagKeyAxis()
	{
		pInfo = nullptr;
		fScale = 0.f;
	}
}KeyAxis, *PKeyAxis;

typedef struct _tagBindAxis
{
	char		strName[NAME_SIZE];
	float		fScale;
	vector<KeyAxis>	vecKey;
	// scale, pushtime, deltatime 3개를 넘겨준다.
	vector<function<void(float, float)>>	vecCallback;

	_tagBindAxis()
	{
		memset(strName, 0, NAME_SIZE);
		fScale = 0.f;
	}
}BindAxis, *PBindAxis;

typedef struct _tagKeyAction
{
	PKeyInfo	pInfo;
	bool		bKeyUnion[(int)KEY_UNION::END];
	bool		bPush;
	float		fPushTime;

	_tagKeyAction()
	{
		pInfo = nullptr;
		bPush = false;
		fPushTime = 0.f;
		memset(bKeyUnion, 0, (int)KEY_UNION::END);
	}
}KeyAction, * PKeyAction;

typedef struct _tagBindAction
{
	char		strName[NAME_SIZE];
	vector<KeyAction>	vecKey;
	vector<function<void(float)>>	vecCallback[(int)KEY_TYPE::END];
	//unordered_map<string, function<void(float)>> mapCallback[(int)KEY_TYPE::END];

	_tagBindAction()
	{
		memset(strName, 0, NAME_SIZE);
	}
}BindAction, *PBindAction;

class CInput
{
private:
	list<PKeyInfo>						m_KeyList;
	unordered_map<string, PBindAxis>	m_mapAxis;
	unordered_map<string, PBindAction>	m_mapAction;
	Vector2			m_vMousePos;
	Vector2			m_vMouseWorldPos;
	Vector2			m_vMouseMove;
	HWND			m_hWnd;
	class CMouse*	m_pMouseObj;
	bool			m_bLButtonClick;
	bool			m_bRButtonClick;

public:
	void CreateMouse();
	void Start();
	bool Init(HWND hWnd);
	void Update(float fTime);
	void Render(HDC hDC, float fTime);

private:
	void UpdateAxis(float fTime);
	void UpdateAction(float fTime);
	void UpdateMouse(float fTime);

public:
	void AddAxisKey(const string& strName, char cKey, float fScale);
	void AddBindAxis(const string& strName, void (*pFunc)(float, float));
	template <typename T>
	void AddBindAxis(const string& strName, T* pObj, void (T::* pFunc)(float, float))
	{
		PBindAxis pAxis = FindAxis(strName);

		if (!pAxis)
		{
			pAxis = new BindAxis;
			strcpy_s(pAxis->strName, strName.c_str());
			m_mapAxis.insert(make_pair(strName, pAxis));
		}

		pAxis->vecCallback.push_back(bind(pFunc, pObj, placeholders::_1, placeholders::_2));

	}

public:
	void AddActionKey(const string& strName, char cKey);
	void AddActionKeyUnion(const string& strName, char cKey, KEY_UNION eType);
	void AddBindAction(const string& strName, KEY_TYPE eType, void (*pFunc)(float));
	template <typename T>
	void AddBindAction(const string& strName, KEY_TYPE eType, T* pObj, void (T::* pFunc)(float))
	{
		PBindAction pAction = FindAction(strName);

		if (!pAction)
		{
			pAction = new BindAction;
			strcpy_s(pAction->strName, strName.c_str());
			m_mapAction.insert(make_pair(strName, pAction));
		}

		pAction->vecCallback[(int)eType].push_back(bind(pFunc, pObj, placeholders::_1));
		/*pAction->mapCallback[(int)eType].insert(make_pair(pObj->GetName(), bind(pFunc, pObj, placeholders::_1)));*/
	}

	void DeleteBindAction(const string& strName);
	//void DeleteBindActionFunc(const string& strName, class CObj* pObj);

public:
	PBindAxis FindAxis(const string& strName);
	PBindAction FindAction(const string& strName);

private:
	void LButtonDown(float fTime);
	void RButtonDown(float fTime);
	void LButtonUp(float fTime);
	void RButtonUp(float fTime);

	DECLARE_SINGLE(CInput)


public:
	bool IsLButtonClick()	const
	{
		return m_bLButtonClick;
	}

	bool IsRButtonClick()	const
	{
		return m_bRButtonClick;
	}

	Vector2 GetMousePos()	const
	{
		return m_vMousePos;
	}

	Vector2 GetMouseWorldPos()	const
	{
		return m_vMouseWorldPos;
	}

	Vector2 GetMouseMove()	const
	{
		return m_vMouseMove;
	}

};

