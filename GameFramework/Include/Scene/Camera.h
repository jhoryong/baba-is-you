#pragma once

#include "../Game.h"

class CCamera
{
	friend class CScene;

protected:
	CCamera();
	virtual ~CCamera();

protected:
	Vector2		m_vPos;
	Vector2		m_vResolution;
	Vector2		m_vWorldSize;
	class CObj* m_pTarget;
	Vector2		m_vTargetOffset;	// 타겟으로부터 얼마나 떨어질지
	Vector2		m_vTargetPivot;
	CCamera*	m_pReturnCamera;

public:
	Vector2 GetPos()	const
	{
		return m_vPos;
	}

	Vector2 GetResolution()	const
	{
		return m_vResolution;
	}

	Vector2 GetWorldSize()	const
	{
		return m_vWorldSize;
	}

	class CObj* GetTarget()	const
	{
		return m_pTarget;
	}

	Vector2 GetTargetOffset()	const
	{
		return m_vTargetOffset;
	}

	Vector2 GetTargetPivot()	const
	{
		return m_vTargetPivot;
	}

public:
	void SetPos(const Vector2& vPos)
	{
		m_vPos = vPos;
	}

	void SetPos(float x, float y)
	{
		m_vPos = Vector2(x, y);
	}

	void SetResolution(const Vector2& vResolution)
	{
		m_vResolution = vResolution;
	}

	void SetResolution(float x, float y)
	{
		m_vResolution = Vector2(x, y);
	}

	void SetWorldSize(const Vector2& vWorldSize)
	{
		m_vWorldSize = vWorldSize;
	}

	void SetWorldSize(float x, float y)
	{
		m_vWorldSize = Vector2(x, y);
	}

	void SetTarget(class CObj* pTarget);
	void SetReturnCamera(CCamera* pCamera)
	{
		m_pReturnCamera = pCamera;
	}

	void SetTargetOffset(const Vector2& vOffset)
	{
		m_vTargetOffset = vOffset;
	}

	void SetTargetOffset(float x, float y)
	{
		m_vTargetOffset = Vector2(x, y);
	}

	void SetTargetPivot(const Vector2& vPivot)
	{
		m_vTargetPivot = vPivot;
	}

	void SetTargetPivot(float x, float y)
	{
		m_vTargetPivot = Vector2(x, y);
	}

	void Move(const Vector2& vMove)
	{
		m_vPos += vMove;
	}

public:
	virtual bool Init();
	virtual void Update(float fTime);
};

