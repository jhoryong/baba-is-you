
#include "MapToolDlg.h"
#include "GameManager.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Object/MapObj.h"
#include "Scene/Camera.h"
#include "PathManager.h"
#include "Input.h"
#include "TileMap/Tile.h"
#include "TileMap/TileMap.h"
#include "Scene/SceneEdit.h"
#include "Object/BlockObj.h"

CMapToolDlg* g_pDlg;

CMapToolDlg::CMapToolDlg() :
	m_hDlg(0),
	m_iID(0),
	m_hObjectList(0),
	m_pMapObj(nullptr)
{
	g_pDlg = this;
}

CMapToolDlg::~CMapToolDlg()
{
	SAFE_RELEASE(m_pMapObj);
	if (m_hDlg)
	{
		DestroyWindow(m_hDlg);
	}
}

bool CMapToolDlg::OnDialog(int iID)
{
	if (m_hDlg)
		return true; // 이미 열려있으면 종료

	m_iID = iID;

	// 다이얼로그 생성
	m_hDlg = CreateDialog(GET_SINGLE(CGameManager)->GetWindowInstance(),
		MAKEINTRESOURCE(iID), GET_SINGLE(CGameManager)->GetWindowHandle(),
		CMapToolDlg::WndProc);

	SetWindowPos(m_hDlg, HWND_TOP, 800, 10, 0, 0, SWP_NOSIZE);

	// 다이얼로그 윈도우 띄움
	ShowWindow(m_hDlg, SW_SHOW);

	// 기본값 넣어주기
	SetDlgItemInt(m_hDlg, IDC_EDIT_TILECOUNTX, 33, TRUE);
	SetDlgItemInt(m_hDlg, IDC_EDIT_TILECOUNTY, 18, TRUE);
	SetDlgItemInt(m_hDlg, IDC_EDIT_TILESIZEX, 24, TRUE);
	SetDlgItemInt(m_hDlg, IDC_EDIT_TILESIZEY, 24, TRUE);

	SetDlgItemInt(m_hDlg, IDC_EDIT_TILESTARTX, 0, TRUE);
	SetDlgItemInt(m_hDlg, IDC_EDIT_TILESTARTY, 0, TRUE);
	SetDlgItemInt(m_hDlg, IDC_EDIT_TILEENDX, 24, TRUE);
	SetDlgItemInt(m_hDlg, IDC_EDIT_TILEENDY, 24, TRUE);

	SetDlgItemInt(m_hDlg, IDC_EDIT_R, 8, TRUE);
	SetDlgItemInt(m_hDlg, IDC_EDIT_G, 8, TRUE);
	SetDlgItemInt(m_hDlg, IDC_EDIT_B, 8, TRUE);

	// 타일타입 콤보박스에 데이터 추가
	// 다차원 배열 문법
	TCHAR		strItem[][30] =
	{
		TEXT("Baba"),
		TEXT("Rock"),
		TEXT("Flag"),
		TEXT("Wall"),
		TEXT("Grass"),
		TEXT("GroundTile"),
		TEXT("Flower"),
		TEXT("Water"),
		TEXT("Skull"),
		TEXT("Brick"),
		TEXT("Lava"),

		TEXT("BabaName"),
		TEXT("RockName"),
		TEXT("FlagName"),
		TEXT("WallName"),
		TEXT("GrassName"),
		TEXT("WaterName"),
		TEXT("SkullName"),
		TEXT("GrassName"),
		TEXT("LavaName"),
		TEXT("LavaName2"),

		TEXT("Is"),

		TEXT("Stop"),
		TEXT("You"),
		TEXT("Win"),
		TEXT("Push"),
		TEXT("Sink"),
		TEXT("Defeat"),
		TEXT("Hot"),
		TEXT("Melt")
	};
	m_hObjectList = GetDlgItem(m_hDlg, IDC_LIST_OBJECT);

	// 콤보박스에 텍스트 추가
	for (int i = 0; i < 30; ++i)
	{
		SendMessage(m_hObjectList, LB_ADDSTRING, 0, (LPARAM)strItem[i]);
	}

	SendMessage(m_hObjectList, LB_SETCURSEL, 0, 0);

	return true;
}

void CMapToolDlg::CreateTileMap()
{
	BOOL	bTransfer = FALSE;

	// Edit Control에 들어가있는 값들을 얻어온다.
	int iTileCountX = GetDlgItemInt(m_hDlg, IDC_EDIT_TILECOUNTX, &bTransfer, TRUE);
	int iTileCountY = GetDlgItemInt(m_hDlg, IDC_EDIT_TILECOUNTY, &bTransfer, TRUE);
	int iTileSizeX = GetDlgItemInt(m_hDlg, IDC_EDIT_TILESIZEX, &bTransfer, TRUE);
	int iTileSizeY = GetDlgItemInt(m_hDlg, IDC_EDIT_TILESIZEY, &bTransfer, TRUE);

	bool bTransparent = false;

	int i = IsDlgButtonChecked(m_hDlg, IDC_CHECK_TRANSPARENT);

	if (i == 1)
	{
		bTransparent = true;
	}

	char r = GetDlgItemInt(m_hDlg, IDC_EDIT_R, &bTransfer, TRUE);
	char g = GetDlgItemInt(m_hDlg, IDC_EDIT_G, &bTransfer, TRUE);
	char b = GetDlgItemInt(m_hDlg, IDC_EDIT_B, &bTransfer, TRUE);

	unsigned int iColor = RGB(r, g, b);

	// 타일맵을 생성한다.
	CScene* pScene = GET_SINGLE(CSceneManager)->GetScene();

	m_pMapObj = pScene->CreateObject<CMapObj>("Map");
	// Pos = 0, 0. 

	m_pMapObj->CreateTileMap(iTileCountX, iTileCountY, (float)iTileSizeX,
		(float)iTileSizeY, iColor, bTransparent);

	//m_pMapObj->SetTexture("Background", TEXT("Background.bmp")); // 뒷배경
	m_pMapObj->SetSize(pScene->GetMainCamera()->GetResolution()); // 카메라의 크기만큼 출력할 것이다.

	//pScene->GetMainCamera()->SetWorldSize((float)iTileSizeX * (float)iTileCountX, (float)iTileSizeY * (float)iTileCountY); 

	((CSceneEdit*)pScene)->AddPrototype();
}

void CMapToolDlg::Save()
{
	TCHAR		strFileName[MAX_PATH] = {};

	OPENFILENAME	tOFN = {};

	tOFN.lStructSize = sizeof(OPENFILENAME);
	tOFN.hwndOwner = m_hDlg;
	tOFN.lpstrFilter = TEXT("모든파일\0*.*\0MapFile\0*.tmp");
	tOFN.lpstrFile = strFileName;
	tOFN.nMaxFile = 256;
	tOFN.lpstrInitialDir = GET_SINGLE(CPathManager)->FindPath(DATA_PATH); // 저장할 폴더
	
	if (GetSaveFileName(&tOFN) != 0)
	{
		if (m_pMapObj)
			Save(strFileName); // 실제 저장
		//MessageBox(0, strFileName, TEXT("Path"), MB_OK);
	}

}

void CMapToolDlg::Load()
{
	TCHAR		strFileName[MAX_PATH] = {};

	OPENFILENAME	tOFN = {};

	tOFN.lStructSize = sizeof(OPENFILENAME);
	tOFN.hwndOwner = m_hDlg;
	tOFN.lpstrFilter = TEXT("모든파일\0*.*\0MapFile\0*.tmp");
	tOFN.lpstrFile = strFileName;
	tOFN.nMaxFile = 256;
	tOFN.lpstrInitialDir = GET_SINGLE(CPathManager)->FindPath(DATA_PATH);

	if (GetOpenFileName(&tOFN) != 0)
	{
		Load(strFileName);
		//MessageBox(0, strFileName, TEXT("Path"), MB_OK);
	}
}

void CMapToolDlg::SaveStage()
{
	TCHAR		strFileName[MAX_PATH] = {};

	OPENFILENAME	tOFN = {};

	tOFN.lStructSize = sizeof(OPENFILENAME);
	tOFN.hwndOwner = m_hDlg;
	tOFN.lpstrFilter = TEXT("모든파일\0*.*\0Text file\0*.txt");
	tOFN.lpstrFile = strFileName;
	tOFN.nMaxFile = 256;
	tOFN.lpstrInitialDir = GET_SINGLE(CPathManager)->FindPath(DATA_PATH); // 저장할 폴더

	if (GetSaveFileName(&tOFN) != 0)
	{
		if (m_pMapObj)
			SaveStage(strFileName); // 실제 저장
		//MessageBox(0, strFileName, TEXT("Path"), MB_OK);
	}
}

void CMapToolDlg::LoadStage()
{
	TCHAR		strFileName[MAX_PATH] = {};

	OPENFILENAME	tOFN = {};

	tOFN.lStructSize = sizeof(OPENFILENAME);
	tOFN.hwndOwner = m_hDlg;
	tOFN.lpstrFilter = TEXT("모든파일\0*.*\0Text file\0*.txt");
	tOFN.lpstrFile = strFileName;
	tOFN.nMaxFile = 256;
	tOFN.lpstrInitialDir = GET_SINGLE(CPathManager)->FindPath(DATA_PATH);

	if (GetOpenFileName(&tOFN) != 0)
	{
		if (m_pMapObj)
			LoadStage(strFileName);
	}
}

void CMapToolDlg::Clear()
{
	m_hDlg = 0;
}

LRESULT CMapToolDlg::WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
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
		g_pDlg->Clear();
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK: // 확인 버튼
			g_pDlg->CreateTileMap(); // 다이얼로그에 있는 값들로 타일맵을 생성한다.
			break;
		case IDCANCEL: // 취소 버튼
			DestroyWindow(hWnd);
			break;
		case IDC_BUTTON_SAVE: // 저장 버튼
			g_pDlg->Save();
			break;
		case IDC_BUTTON_LOAD: // 로드 버튼
			g_pDlg->Load();
			break;
		case IDC_BUTTON_SAVE_STAGE:
			g_pDlg->SaveStage();
			break;
		case IDC_BUTTON_LOAD_STAGE:
			g_pDlg->LoadStage();
			break;
		}
		break;
	}

	return 0;
}

void CMapToolDlg::Save(const TCHAR* pFullPath)
{
	char	strFullPath[MAX_PATH] = {};

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

	// 편집한 타일맵을 저장한다.
	m_pMapObj->Save(pFile);

	fclose(pFile);
}

void CMapToolDlg::Load(const TCHAR* pFullPath)
{
	char	strFullPath[MAX_PATH] = {};

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

	if (!m_pMapObj) // MapObj 없으면 객체 새로 생성
	{
		CScene* pScene = GET_SINGLE(CSceneManager)->GetScene();

		m_pMapObj = pScene->CreateObject<CMapObj>("Map");
	}

	m_pMapObj->Load(pFile);

	fclose(pFile);
}

void CMapToolDlg::SaveStage(const TCHAR* pFullPath)
{
	char	strFullPath[MAX_PATH] = {};

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

	fopen_s(&pFile, strFullPath, "wt");

	if (!pFile)
		return;

	CScene* pScene = GET_SINGLE(CSceneManager)->GetScene();

	if (pScene)
		((CSceneEdit*)pScene)->SaveObjectList(pFile);

	fclose(pFile);
}

void CMapToolDlg::LoadStage(const TCHAR* pFullPath)
{
	char	strFullPath[MAX_PATH] = {};

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

	fopen_s(&pFile, strFullPath, "rt");

	if (!pFile)
		return;

	CScene* pScene = GET_SINGLE(CSceneManager)->GetScene();

	if (pScene)
		pScene->Load(pFile);

	fclose(pFile);
}

void CMapToolDlg::PlaceObject()
{
	// 선택한 Texture의 이름을 얻어온다.
	int		iListIndex = -1;

	// LB_GETCURSEL - 클릭한걸 얻어오는것.
	iListIndex = (int)SendMessage(m_hObjectList, LB_GETCURSEL, 0, 0);
	 
	if (iListIndex != -1)
	{
		TCHAR	strObjName[100] = {};

		SendMessage(m_hObjectList, LB_GETTEXT, iListIndex, (LPARAM)strObjName);

		char	strName[100] = {};

#ifdef UNICODE
		// 문자열을 multibyte로 변환할 개수가 나온다.
		int iLength = WideCharToMultiByte(CP_ACP, 0, strObjName, -1, nullptr, 0,
			nullptr, nullptr);
		WideCharToMultiByte(CP_ACP, 0, strObjName, -1, strName,
			iLength, nullptr, nullptr);
#else
		strcpy_s(strName, strTexName);
#endif // UNICODE

		CScene* pScene = GET_SINGLE(CSceneManager)->GetScene();
		Vector2 vMousePos = GET_SINGLE(CInput)->GetMouseWorldPos();
		CTileMap* pTileMap = pScene->FindTileMap(vMousePos);
		Vector2 vMapStart;

		if (pTileMap)
			vMapStart = pTileMap->GetStartPos();

		Vector2 vRelPos = vMousePos - vMapStart;
		CTile* pTile = pScene->FindTile(vMousePos, vRelPos);

		if (pTile)
		{
			int iIndexX, iIndexY;
			iIndexX = pTile->GetIndexX();
			iIndexY = pTile->GetIndexY();

			CObj* pObj = ((CSceneEdit*)pScene)->FindObject(iIndexX, iIndexY);

			if (pObj)
			{
				SAFE_RELEASE(pObj);
				return;
			}

			CBlockObj* pNewObj = ((CSceneEdit*)pScene)->CreateBlockObj(strName);

			if (pNewObj)
				pNewObj->SetTileIndex(iIndexX, iIndexY);

			SAFE_RELEASE(pNewObj);
		}
	}
}

void CMapToolDlg::EraseObject()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetScene();
	Vector2 vMousePos = GET_SINGLE(CInput)->GetMouseWorldPos();
	CTileMap* pTileMap = pScene->FindTileMap(vMousePos);
	Vector2 vMapStart;

	if (pTileMap)
		vMapStart = pTileMap->GetStartPos();

	Vector2 vRelPos = vMousePos - vMapStart;
	CTile* pTile = pScene->FindTile(vMousePos, vRelPos);

	if (pTile)
	{
		int iIndexX, iIndexY;
		iIndexX = pTile->GetIndexX();
		iIndexY = pTile->GetIndexY();

		CObj* pObj = ((CSceneEdit*)pScene)->FindObject(iIndexX, iIndexY);

		if (pObj)
		{
			pObj->Destroy();
			SAFE_RELEASE(pObj);
		}
	}
}
