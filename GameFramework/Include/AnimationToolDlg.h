#pragma once

#include "Game.h"

class CAnimationToolDlg
{
public:
	CAnimationToolDlg();
	~CAnimationToolDlg();

private:
	HWND m_hDlg;
	int m_iID;

	HWND m_hAnimationImageCombo;
	HWND m_hAnimationTypeCombo;
	HWND m_hAnimationOptionCombo;
	HWND m_hAnimationPlayTypeCombo;

	string m_strAnimationSequence;
	vector<class CAnimationSequence*> m_vecSeq;

	int m_iCount;

public:
	bool OnDialog(int iID);
	void Clear();
	void DeleteAllObject();
	void CreateSequence();
	void Save(); // ���� �������� ���� �������� �����Ѵ�.
	void Load();

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Save(const TCHAR* pFullPath);
	void Load(const TCHAR* pFullPath);

public:
	// �޺��ڽ��� ���õ� �׸��� �����´�.
	int GetImageType()
	{
		return (int)SendMessage(m_hAnimationImageCombo, CB_GETCURSEL, 0, 0);
	}
};

