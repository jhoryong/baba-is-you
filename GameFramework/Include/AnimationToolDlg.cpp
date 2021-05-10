#include "AnimationToolDlg.h"

#include "GameManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Resource/AnimationSequence.h"
#include "Object/UIImage.h"
#include "Scene/SceneResource.h"
#include "Timer.h"
#include "Scene/SceneAnimEdit.h"
#include "PathManager.h"
#include "Resource/ResourceManager.h"
#include "Object/BlockObj.h"

CAnimationToolDlg* g_pAnimDlg;

CAnimationToolDlg::CAnimationToolDlg() :
	m_hDlg(0),
	m_hAnimationImageCombo(nullptr),
	m_hAnimationTypeCombo(nullptr),
	m_hAnimationOptionCombo(nullptr),
	m_hAnimationPlayTypeCombo(nullptr),
	m_iID(0),
	m_iCount(0)
{
	g_pAnimDlg = this;
}

CAnimationToolDlg::~CAnimationToolDlg()
{
	SAFE_RELEASE_VECLIST(m_vecSeq);

	if (m_hDlg)
		DestroyWindow(m_hDlg);
}

bool CAnimationToolDlg::OnDialog(int iID)
{
	if (m_hDlg)
		return true; // 이미 열려있으면 종료

	m_iID = iID; // 아이디값

	// 다이얼로그 생성
	m_hDlg = CreateDialog(WINDOWINSTANCE, MAKEINTRESOURCE(iID), WINDOWHANDLE, CAnimationToolDlg::WndProc);

	SetWindowPos(m_hDlg, HWND_TOP, 800, 10, 0, 0, SWP_NOSIZE);

	ShowWindow(m_hDlg, SW_SHOW); // 윈도우 띄움

	// 콤보박스 생성
	m_hAnimationImageCombo = GetDlgItem(m_hDlg, IDC_COMBO_ANIMATIONIMAGE);
	m_hAnimationTypeCombo = GetDlgItem(m_hDlg, IDC_COMBO_ANIMATION_TYPE);
	m_hAnimationOptionCombo = GetDlgItem(m_hDlg, IDC_COMBO_ANIMATION_OPTION);
	m_hAnimationPlayTypeCombo = GetDlgItem(m_hDlg, IDC_COMBO_ANIMATION_PLAY_TYPE);

	// 콤보박스에 데이터 추가
	TCHAR strItem[][30] =
	{
		TEXT("Sprite"),
		TEXT("Sprite2")
	};

	for (int i = 0; i < 2; ++i)
	{
		SendMessage(m_hAnimationImageCombo, CB_ADDSTRING, 0, (LPARAM)strItem[i]);
	}

	SendMessage(m_hAnimationImageCombo, CB_SETCURSEL, 0, 0); // 0 번을 기본으로 올려둔다.

	TCHAR strItem2[30] = TEXT("Atlas");
	SendMessage(m_hAnimationTypeCombo, CB_ADDSTRING, 0, (LPARAM)strItem2);
	SendMessage(m_hAnimationTypeCombo, CB_SETCURSEL, 0, 0);
	
	TCHAR strItem3[30] = TEXT("Loop");
	SendMessage(m_hAnimationOptionCombo, CB_ADDSTRING, 0, (LPARAM)strItem3);
	SendMessage(m_hAnimationOptionCombo, CB_SETCURSEL, 0, 0);

	TCHAR strItem4[30] = TEXT("Normal");
	SendMessage(m_hAnimationPlayTypeCombo, CB_ADDSTRING, 0, (LPARAM)strItem4);
	SendMessage(m_hAnimationPlayTypeCombo, CB_SETCURSEL, 0, 0);

	// Edit Control 에 기본값 세팅
	SetDlgItemInt(m_hDlg, IDC_EDIT_FRAME_COUNT, 3, TRUE);
	SetDlgItemText(m_hDlg, IDC_EDIT_LOOP_TIME, TEXT("0.7"));

	return true;
}

void CAnimationToolDlg::Clear()
{
	g_pAnimDlg = 0;
}

void CAnimationToolDlg::DeleteAllObject()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetScene();
	((CSceneAnimEdit*)pScene)->DeleteAllObject();

	SAFE_RELEASE_VECLIST(m_vecSeq);

	pScene->GetSceneResource()->ReleaseAnimationSequence();
	GET_SINGLE(CResourceManager)->ReleaseAnimationSequence();
}

void CAnimationToolDlg::CreateSequence()
{
	// Edit Control에 들어가있는 값들을 얻어온다.

	BOOL bTransfer = FALSE; // 이 변수는 GetDlgItemInt() 의 성공 여부를 반환받는다.

	// 시퀀스 이름
	TCHAR strSqName[50] = {};
	char strSqName1[50] = {};
	GetDlgItemText(m_hDlg, IDC_SEQUENCE_NAME, strSqName, 50);
	
	// 텍스쳐 이름
	int iTextureCombo = -1;
	iTextureCombo = (int)SendMessage(m_hAnimationImageCombo, CB_GETCURSEL, 0, 0);

	if (iTextureCombo != -1)
	{
		TCHAR strTexName[50] = {};
		char strTexName1[50] = {};
		SendMessage(m_hAnimationImageCombo, CB_GETLBTEXT, iTextureCombo, (LPARAM)strTexName);

#ifdef UNICODE
		// 문자열을 multibyte로 변환할 개수가 나온다.
		int iLength = WideCharToMultiByte(CP_ACP, 0, strSqName, -1, nullptr, 0,
			nullptr, nullptr);
		WideCharToMultiByte(CP_ACP, 0, strSqName, -1, strSqName1,
			iLength, nullptr, nullptr);

		int iLength1 = WideCharToMultiByte(CP_ACP, 0, strTexName, -1, nullptr, 0, nullptr, nullptr);
		WideCharToMultiByte(CP_ACP, 0, strTexName, -1, strTexName1,
			iLength1, nullptr, nullptr);
#else
		strcpy_s(strSqName1, strSqName);
		strcpy_s(strTexName1, strTexName);
#endif // UNICODE

		string sSqName = strSqName1;
		string sTexName = strTexName1;

		// ANIM TYPE
		int iAnimTypeCombo = (int)SendMessage(m_hAnimationTypeCombo, CB_GETCURSEL, 0, 0);

		// ATIM_OPTION
		int iAnimOption = (int)SendMessage(m_hAnimationOptionCombo, CB_GETCURSEL, 0, 0);

		// ANIM_PALY_TYPE
		int iAnimPlayType = (int)SendMessage(m_hAnimationPlayTypeCombo, CB_GETCURSEL, 0, 0);

		TCHAR iLoopTime[20] = {};
		GetDlgItemText(m_hDlg, IDC_EDIT_LOOP_TIME, iLoopTime, 20);
		float fLoopTime = (float)_tstof(iLoopTime);

		int iFrameCount = GetDlgItemInt(m_hDlg, IDC_EDIT_FRAME_COUNT, &bTransfer, TRUE);
		int iStartX = GetDlgItemInt(m_hDlg, IDC_EDIT_FRAMESTARTX, &bTransfer, TRUE);
		int iStartY = GetDlgItemInt(m_hDlg, IDC_EDIT_FRAMESTARTY, &bTransfer, TRUE);

		// Animation Sequence 를 생성한다.
		CScene* pScene = GET_SINGLE(CSceneManager)->GetScene();

		CAnimationSequence* pSequence = pScene->GetSceneResource()->FindAnimationSequence(sSqName);

		if (pSequence)
		{
			SAFE_RELEASE(pSequence);
			return;
		}

		pScene->GetSceneResource()->CreateAnimationSequence(sSqName, sTexName, (ANIM_TYPE)(iAnimTypeCombo), (ANIM_OPTION)(iAnimOption), (ANIM_PLAY_TYPE)(iAnimPlayType), fLoopTime);

		for (int i = 0; i < iFrameCount; ++i)
		{
			pScene->GetSceneResource()->AddAnimationFrame(sSqName,
				Vector2((float)iStartX, (float)iStartY + 24.f * i),
				Vector2((float)iStartX + 24.f, (float)iStartY + 24.f * (float)(i + 1))
			);
		}

		CAnimationSequence* pSeq = GET_SINGLE(CResourceManager)->FindAnimationSequence(sSqName);
		if (pSeq)
			m_vecSeq.push_back(pSeq);

		CUIImage* pObj = pScene->CreateObject<CUIImage>(sSqName);
		pObj->CreateAnimation();
		pObj->AddAnimation(sSqName);
		pObj->SetSize(24.f, 24.f);
		pObj->SetPos(50.f + 24.f * m_iCount, 50.f);
		SAFE_RELEASE(pObj);
		++m_iCount;
	}
}

LRESULT CAnimationToolDlg::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		ShowCursor(TRUE);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		g_pAnimDlg->Clear();
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			DestroyWindow(hWnd);
			break;
		case IDC_BUTTON_CREATE_SEQUENCE:
			g_pAnimDlg->CreateSequence();
			break;

		case IDC_BUTTON_CLEAR:
			g_pAnimDlg->DeleteAllObject();
			break;

		case IDC_BUTTON_ANIMSAVE:
			g_pAnimDlg->Save();
			break;

		case IDC_BUTTON_ANIMLOAD:
			g_pAnimDlg->Load();
			break;
		}
		break;
	}

	return 0;
}

void CAnimationToolDlg::Save()
{
	TCHAR strFileName[MAX_PATH] = {};

	OPENFILENAME tOFN = {};

	tOFN.lStructSize = sizeof(OPENFILENAME);
	tOFN.hwndOwner = m_hDlg;
	tOFN.lpstrFilter = TEXT("Animation Sequence File (*.asq)\0*.asq\0\0");
	tOFN.lpstrFile = strFileName;
	tOFN.nMaxFile = 256;
	tOFN.lpstrInitialDir = GET_SINGLE(CPathManager)->FindPath(SEQUENCE_PATH);

	if (GetSaveFileName(&tOFN) != 0)
	{
		if (!m_vecSeq.empty())
		{
			Save(strFileName);
		}
	}
}

void CAnimationToolDlg::Load()
{
	TCHAR strFileName[MAX_PATH] = {};

	OPENFILENAME tOFN = {};

	tOFN.lStructSize = sizeof(OPENFILENAME);
	tOFN.hwndOwner = m_hDlg;
	tOFN.lpstrFilter = TEXT("Animation Sequence File(.asq)\0*.asq");
	tOFN.lpstrFile = strFileName;
	tOFN.nMaxFile = 256;
	tOFN.lpstrInitialDir = GET_SINGLE(CPathManager)->FindPath(SEQUENCE_PATH);

	if (GetOpenFileName(&tOFN) != 0)
	{
		Load(strFileName);
	}
}


void CAnimationToolDlg::Save(const TCHAR* pFullPath)
{
	char strFullPath[MAX_PATH] = {};

#ifdef UNICODE
	// 문자열을 multibyte로 변환할 개수가 나온다.
	int iLength = WideCharToMultiByte(CP_ACP, 0, pFullPath, -1, nullptr, 0,
		nullptr, nullptr);
	WideCharToMultiByte(CP_ACP, 0, pFullPath, -1, strFullPath,
		iLength, nullptr, nullptr);
#else
	strcpy_s(strFullPath, pFullPath);
#endif // UNICODE

	FILE* pFile = nullptr;

	fopen_s(&pFile, strFullPath, "wb");

	if (!pFile)
		return;

	auto iter = m_vecSeq.end() - 1;
	(*iter)->Save(pFile);

	fclose(pFile);
}

void CAnimationToolDlg::Load(const TCHAR* pFullPath)
{
	char strFullPath[MAX_PATH] = {};

#ifdef UNICODE
	// 문자열을 multibyte로 변환할 개수가 나온다.
	int iLength = WideCharToMultiByte(CP_ACP, 0, pFullPath, -1, nullptr, 0,
		nullptr, nullptr);
	WideCharToMultiByte(CP_ACP, 0, pFullPath, -1, strFullPath,
		iLength, nullptr, nullptr);
#else
	strcpy_s(strFullPath, pFullPath);
#endif // UNICODE

	FILE* pFile = nullptr;

	fopen_s(&pFile, strFullPath, "rb");

	if (!pFile)
		return;

	int iLen = 0;
	fread(&iLen, sizeof(int), 1, pFile);

	char strName[20] = {};
	fread(&strName, sizeof(char), iLen, pFile);
	string name = strName;

	CScene* pScene = GET_SINGLE(CSceneManager)->GetScene();

	pScene->GetSceneResource()->CreateAnimationSequence(strName, pFile);
	
	CAnimationSequence* pSeq = pScene->GetSceneResource()->FindAnimationSequence(strName);

	if (pSeq)
	{
		m_vecSeq.push_back(pSeq);
		CUIImage* pObj = pScene->CreateObject<CUIImage>(pSeq->GetName());
		pObj->CreateAnimation();
		pObj->AddAnimation(pSeq->GetName());
		pObj->SetSize(24.f, 24.f);
		pObj->SetPos(100.f, 100.f + 24.f * m_iCount);
		SAFE_RELEASE(pObj);
		++m_iCount;
	}

	fclose(pFile);
}