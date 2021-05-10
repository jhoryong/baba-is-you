#pragma once
#include "Obj.h"
class CUI :
	public CObj
{
public:
	CUI();
	virtual ~CUI();

protected:
	class CCollider* m_pBody;
	int	m_iZOrder;

public:
	int GetZOrder()	const
	{
		return m_iZOrder;
	}

	void SetZOrder(int iZOrder)
	{
		m_iZOrder = iZOrder;
	}

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
	virtual CUI* Clone();

public:
	virtual void ChangeCollider(COLLIDER_TYPE eType);
};

