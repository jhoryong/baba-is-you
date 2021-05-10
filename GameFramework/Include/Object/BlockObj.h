#pragma once
#include "Obj.h"


class CBlockObj :
    public CObj
{
public:
	CBlockObj();
	CBlockObj(const CBlockObj& obj);

protected:
	virtual ~CBlockObj() = 0;

protected:
	// Ÿ�ϸ�, Ÿ��
	class CTileMap* m_pTileMap; // �ڽ��� ���� Ÿ�ϸ�
	Vector2 m_vRelPos; // Ÿ�ϸ� ���� ���������ġ
	class CTile* m_pTile; // ���� Ÿ��
	class CTile* m_pPrevTile = nullptr;
	Vector2 m_vTileSize;
	Vector2 m_vTilePos; // Ÿ�� ���� ��ġ

	int		m_iTileCountX; // Ÿ�� x ����
	int		m_iTileCountY; // Ÿ�� y ����
	int		m_iTileIndex; // ���� Ÿ��
	int		m_iTileIndexX;
	int		m_iTileIndexY;
	int		m_iPrevTileIndex = 0;

	// �̵�
	bool	m_bMoving; // �̵����ϰ�� true �ȴ�.
	bool	m_bMoved = false; // ���� �߾����� ���� ���� �� ���� �����ӿ� true �ǰ� ���� �����ӿ��� false �ȴ�.
	bool	m_bBoundEnter = false; // �׵θ� ���� ���� ��� true �ȴ�. 
	bool m_bMoveStart = false;

	Vector2 m_vBackPos;
	Vector2	m_vMoveDir;
	Vector2 m_vStopDir;
	float	m_fSpeed;
	float   m_fMoveDist;
	float   m_fMoveDistAcc = 0.f;
	BLOCKOBJ_TYPE m_eBlockObjType; // Character vs Word

	// ���� ����
	bool m_bState[(int)STATE_TYPE::END]; // ���� State
	bool m_bNone = false;
	int m_iZOrder = 0;
	bool m_bSink = false;
	bool m_bDefeat = false;
	bool m_bMelt = false;

	/*
	�浹üũ -> �̵� -> Ÿ�Ͽ� ��� -> ���� ���� -> ���� �ݿ� -> �ִϸ��̼� �ݿ�
	*/

	bool m_bInitialFrame = true;
	bool m_bUndo = false;

public:
	virtual bool Init();
	virtual bool Init(const char* pFileName,
		const string& strPathName = DATA_PATH);
	virtual void Start();
	virtual void Update(float fTime); // �浹 üũ
	virtual void PostUpdate(float fTime); // �̵� 
	virtual void Collision(float fTime); // Ÿ�Ͽ� ���
	virtual void PrevRender(float fTime); // ���� ����
	virtual void Render(HDC hDC, float fTime);
	virtual void PostRender(float fTime);
	virtual CBlockObj* Clone() = 0;

private:
	void Move(Vector2 vDir);
	void CheckCollision(float fTime);
	void DestroyObject();

public:
	void SetTileIndex(int x, int y);
	void SetTileIndex(int iIndex);
	void SetRelPos(const Vector2& vRelPos);
	void SetRelPos(float x, float y);

public:
	virtual void MoveLeft(float fTime);
	virtual void MoveRight(float fTime);
	virtual void MoveUp(float fTime);
	virtual void MoveDown(float fTime);

	virtual void MoveLeftOn(float fTime);
	virtual void MoveRightOn(float fTime);
	virtual void MoveUpOn(float fTime);
	virtual void MoveDownOn(float fTime);

public:
	BLOCKOBJ_TYPE GetBlockObjType()
	{
		return m_eBlockObjType;
	}

	Vector2 GetStopDir()
	{
		return m_vStopDir;
	}

	void SetStopDir(Vector2 vStopDir)
	{
		m_vStopDir = vStopDir;
	}

	int GetZOrder()	const
	{
		return m_iZOrder;
	}

	void SetZOrder(int iZOrder)
	{
		m_iZOrder = iZOrder;
	}

	void EnableUndo()
	{
		m_bUndo = true;
	}

	void DisableUndo()
	{
		m_bUndo = false;
	}

	bool GetUndo()
	{
		return m_bUndo;
	}
	
	void SetBackPos(Vector2 vBackPos)
	{
		m_vBackPos = vBackPos;
	}

	Vector2 GetBackPos()
	{
		return m_vBackPos;
	}

	int GetIndexX()
	{
		return m_iTileIndexX;
	}

	int GetIndexY()
	{
		return m_iTileIndexY;
	}

	void SetSink()
	{
		m_bSink = true;
	}

	bool GetYou()
	{
		return m_bState[(int)STATE_TYPE::YOU];
	}
};

