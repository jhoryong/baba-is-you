#pragma once
#include "UI.h"
class CUIButton :
	public CUI
{
public:
	CUIButton();
	virtual ~CUIButton();

protected:
	bool		m_bMouseCollision;
	bool		m_bMouseDown;
	bool		m_bMousePush;
	bool		m_bMouseUp;
	bool		m_bClick;
	string	m_strAnimationName[(int)BUTTON_STATE::END];
	function<void(float)>	m_ClickCallback;
	//string	m_strEventSoundName[(int)BUTTON_STATE::END];
	vector<string> m_strEventSoundName[(int)BUTTON_STATE::END];

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
	virtual CUIButton* Clone();

public:
	virtual void ChangeCollider(COLLIDER_TYPE eType);
	void AddAnimation(BUTTON_STATE eState, const string& strName);
	void SetEventSound(BUTTON_STATE eState, const string& strName);

private:
	void CollisionBegin(class CCollider* pSrc, const Vector2& vMousePos, float fTime);
	void CollisionEnd(class CCollider* pSrc, const Vector2& vMousePos, float fTime);

public:
	void SetClickCallback(	void(*pFunc)(float));

	template <typename T>
	void SetClickCallback(T* pObj, void(T::* pFunc)(float))
	{
		m_ClickCallback = bind(pFunc, pObj, placeholders::_1);
	}
};

