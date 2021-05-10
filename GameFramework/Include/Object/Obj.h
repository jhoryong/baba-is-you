#pragma once

#include "../Ref.h"

class CObj :
	public CRef
{
	friend class CScene;
	friend class CSceneStage;

public:
	CObj();
	CObj(const CObj& obj);

protected:
	virtual ~CObj() = 0;

protected:
	class CScene* m_pScene;

protected:
	Vector2	m_vPos; // 위치
	Vector2	m_vRenderPos; // 렌더위치
	Vector2	m_vSize; // 크기
	Vector2	m_vPivot; // Pivot

	class CTexture* m_pTexture;
	class CAnimation* m_pAnimation;
	list<class CCollider*>	m_ColliderList;

	bool	m_bUI;
	bool	m_bEnvironment; // map obj 인지 아닌지.
	bool	m_bBackgroundObj = false;
	bool	m_bStart;

	// for Alpha Blending
	unsigned char	m_cAlpha;
	bool			m_bAlphaBlend;

	// Draw Collider
	bool m_bDrawCollider;

public:
	virtual bool Init() = 0;
	virtual bool Init(const char* pFileName,
		const string& strPathName = DATA_PATH);
	virtual void Start();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void PrevRender(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual void PostRender(float fTime);
	virtual CObj* Clone() = 0;

public:
	void ColliderSwitch(float fTime = 0.f)
	{
		m_bDrawCollider = m_bDrawCollider ? false : true;
	}

public:
	virtual void SaveFile(const char* pFileName, const string& strPathName = DATA_PATH);
	virtual void LoadFile(const char* pFileName, const string& strPathName = DATA_PATH);
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);

public:
	bool SetTexture(const string& strName);
	bool SetTexture(const string& strName, const TCHAR* pFileName,
		const string& strPathName = TEXTURE_PATH);
	bool SetTexture(const string& strName, const vector<const TCHAR*>& vecFileName,
		const string& strPathName = TEXTURE_PATH);
	bool SetTexture(const string& strName, const TCHAR* pFileName,
		int iCount, const string& strPathName = TEXTURE_PATH);
	bool SetTexture(class CTexture* pTexture);

public:
	void CreateAnimation();
	void AddAnimationSequence(const string& strName); // Scene Resource 에 이미 로드된 애니메이션 시퀀스를 애니메이션 클래스에 추가한다.
	void AddAnimationSequence(class CAnimationSequence* pSequence); // Resource Manager 에 이미 로드된 애니메이션 시퀀스를 애니메이션 클래스에 추가한다.
	void AddLoadedAnimationSequence(const string& strName); // Resource Manager 에 이미 로드된 애니메이션 시퀀스를 애니메이션 클래스에 추가한다.
	void SetAnimationPlayRate(const string& strName, float fPlayRate);
	void AddAnimationPlayRate(const string& strName, float fPlayRate);
	void ChangeAnimation(const string& strName);
	void SetDefaultAnimation(const string& strName);

public:
	class CCollider* FindCollider(const string& strName);
	void DeleteCollider(const string& strName);

	template <typename T>
	T* AddCollider(const string& strName)
	{
		T* pCollider = new T;

		pCollider->m_pOwner = this;
		pCollider->SetName(strName);
		pCollider->SetScene(m_pScene);
		if (m_bUI)
			pCollider->EnableUI();
		
		if (!pCollider->Init())
		{
			SAFE_DELETE(pCollider);
			return nullptr;
		}

		m_ColliderList.push_back(pCollider);

		return pCollider;
	}


public:
	bool IsStart()	const
	{
		return m_bStart;
	}

	void EnableStart()
	{
		m_bStart = true;
	}

	bool IsEnvironment()	const
	{
		return m_bEnvironment;
	}

	bool IsUI()	const
	{
		return m_bUI;
	}

	void SetAlpha(unsigned char cAlpha)
	{
		m_cAlpha = cAlpha;
	}

	void SetAlphaBlend(bool bBlend)
	{
		m_bAlphaBlend = bBlend;
	}

	Vector2 GetPos()	const
	{
		return m_vPos;
	}

	Vector2 GetSize()	const
	{
		return m_vSize;
	}

	Vector2 GetPivot()	const
	{
		return m_vPivot;
	}

	void EnableUI()
	{
		m_bUI = true;
	}

	void SetPos(const Vector2& vPos)
	{
		m_vPos = vPos;
	}

	void SetPos(float x, float y)
	{
		m_vPos = Vector2(x, y);
	}

	void SetSize(const Vector2& vSize)
	{
		m_vSize = vSize;
	}

	void SetSize(float x, float y)
	{
		m_vSize = Vector2(x, y);
	}

	void SetPivot(const Vector2& vPivot)
	{
		m_vPivot = vPivot;
	}

	void SetPivot(float x, float y)
	{
		m_vPivot = Vector2(x, y);
	}

	bool IsBackgroundObj()
	{
		return m_bBackgroundObj;
	}
};

