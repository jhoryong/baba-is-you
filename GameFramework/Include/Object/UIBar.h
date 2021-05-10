#pragma once
#include "UI.h"
class CUIBar :
	public CUI
{
public:
	CUIBar();
	virtual ~CUIBar();

private:
	float		m_fMin;
	float		m_fMax;
	float		m_fValue;
	float		m_fPercent;
	Vector2	m_vBarExtent;

public:
	void SetMin(float fMin)
	{
		m_fMin = fMin;

		m_fPercent = (m_fValue - m_fMin) / (m_fMax - m_fMin);
	}

	void SetMax(float fMax)
	{
		m_fMax = fMax;

		m_fPercent = (m_fValue - m_fMin) / (m_fMax - m_fMin);
	}

	void SetValue(float fValue)
	{
		m_fValue = fValue;

		if (m_fValue < m_fMin)
			m_fValue = m_fMin;

		else if (m_fValue > m_fMax)
			m_fValue = m_fMax;

		m_fPercent = (m_fValue - m_fMin) / (m_fMax - m_fMin);
	}

	void AddValue(float fValue)
	{
		m_fValue += fValue;

		if (m_fValue < m_fMin)
			m_fValue = m_fMin;

		else if (m_fValue > m_fMax)
			m_fValue = m_fMax;

		m_fPercent = (m_fValue - m_fMin) / (m_fMax - m_fMin);
	}

	void SetExtent(float x, float y)
	{
		m_vBarExtent = Vector2(x, y);
	}

	void SetExtent(const Vector2& vExtent)
	{
		m_vBarExtent = vExtent;
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
	virtual CUIBar* Clone();
};

