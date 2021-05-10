#pragma once

#include "Game.h"

class CRef
{
public:
	CRef();
	virtual ~CRef() = 0;

protected:
	int		m_iRefCount;
	string	m_strName;
	bool	m_bActive;	// 살아있는지 죽었는지
	bool	m_bEnable;	// 활성/비활성

public:
	bool Release();
	void AddRef();

public:
	void SetName(const string& strName)
	{
		m_strName = strName;
	}

	const string& GetName()	const
	{
		return m_strName;
	}


	void Enable(bool bEnable)
	{
		m_bEnable = bEnable;
	}

	bool IsEnable()	const
	{
		return m_bEnable;
	}

	void Destroy()
	{
		m_bActive = false;
	}

	bool IsActive()		const
	{
		return m_bActive;
	}
};

