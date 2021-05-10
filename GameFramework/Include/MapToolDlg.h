#pragma once

#include "Game.h"

class CMapToolDlg
{
public:
	CMapToolDlg();
	~CMapToolDlg();

private:
	HWND	m_hDlg; // 다이얼로그 핸들
	HWND	m_hObjectList = nullptr;
	HWND	m_hCheckbox = nullptr;
	int		m_iID; // 다이얼로그 ID

	class CMapObj* m_pMapObj; // 저장할 Map Obj 객체

public:
	bool OnDialog(int iID);
	void CreateTileMap(); // 다이얼로그에 있는 값들로 타일맵을 생성한다.
	void Save(); // Save 창을 연다
	void Load(); // Load 창을 연다
	void SaveStage(); // Save 창을 연다
	void LoadStage(); // Load 창을 연다
	void Clear();
	void PlaceObject(); // 타일 텍스쳐를 교체한다.
	void EraseObject();

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	void Save(const TCHAR* pFullPath); // 해당 경로로 save 한다.
	void Load(const TCHAR* pFullPath); // 해당 경로로 load 한다.
	void SaveStage(const TCHAR* pFullPath);
	void LoadStage(const TCHAR* pFullPath);

public:
	class CMapObj* GetMapObj()	const
	{
		return m_pMapObj;
	}
};
