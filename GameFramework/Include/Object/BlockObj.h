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
	// 타일맵, 타일
	class CTileMap* m_pTileMap; // 자신이 속한 타일맵
	Vector2 m_vRelPos; // 타일맵 내의 상대적인위치
	class CTile* m_pTile; // 속한 타일
	class CTile* m_pPrevTile = nullptr;
	Vector2 m_vTileSize;
	Vector2 m_vTilePos; // 타일 시작 위치

	int		m_iTileCountX; // 타일 x 개수
	int		m_iTileCountY; // 타일 y 개수
	int		m_iTileIndex; // 현재 타일
	int		m_iTileIndexX;
	int		m_iTileIndexY;
	int		m_iPrevTileIndex = 0;

	// 이동
	bool	m_bMoving; // 이동중일경우 true 된다.
	bool	m_bMoved = false; // 블럭의 중앙점이 선을 넘은 그 순간 프레임에 true 되고 다음 프레임에는 false 된다.
	bool	m_bBoundEnter = false; // 테두리 블럭을 들어갔을 경우 true 된다. 
	bool m_bMoveStart = false;

	Vector2 m_vBackPos;
	Vector2	m_vMoveDir;
	Vector2 m_vStopDir;
	float	m_fSpeed;
	float   m_fMoveDist;
	float   m_fMoveDistAcc = 0.f;
	BLOCKOBJ_TYPE m_eBlockObjType; // Character vs Word

	// 블럭의 상태
	bool m_bState[(int)STATE_TYPE::END]; // 블럭의 State
	bool m_bNone = false;
	int m_iZOrder = 0;
	bool m_bSink = false;
	bool m_bDefeat = false;
	bool m_bMelt = false;

	/*
	충돌체크 -> 이동 -> 타일에 등록 -> 상태 갱신 -> 상태 반영 -> 애니메이션 반영
	*/

	bool m_bInitialFrame = true;
	bool m_bUndo = false;

public:
	virtual bool Init();
	virtual bool Init(const char* pFileName,
		const string& strPathName = DATA_PATH);
	virtual void Start();
	virtual void Update(float fTime); // 충돌 체크
	virtual void PostUpdate(float fTime); // 이동 
	virtual void Collision(float fTime); // 타일에 등록
	virtual void PrevRender(float fTime); // 상태 갱신
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

