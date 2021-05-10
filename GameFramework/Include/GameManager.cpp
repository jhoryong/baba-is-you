#include "GameManager.h"
#include "Timer.h"
#include "Input.h"
#include "Scene/SceneManager.h"
#include "PathManager.h"
#include "Resource/ResourceManager.h"
#include "FontManager.h"

DEFINITION_SINGLE(CGameManager)


bool CGameManager::m_bLoop = true;

CGameManager::CGameManager() :
    m_pTimer(nullptr)
{
	memset(m_strTitle, 0, sizeof(TCHAR) * 256);
	memset(m_strClass, 0, sizeof(TCHAR) * 256);
}

CGameManager::~CGameManager()
{
    DESTROY_SINGLE(CSceneManager);

    DESTROY_SINGLE(CPathManager);
    DESTROY_SINGLE(CInput);
    DESTROY_SINGLE(CResourceManager);
    DESTROY_SINGLE(CFontManager);

    SAFE_DELETE(m_pTimer);

    DeleteObject(m_hPurpleBrush);
    DeleteObject(m_hBlueBrush);
    DeleteObject(m_hGrayBrush);
    DeleteObject(m_hGreenBrush);
    DeleteObject(m_hRedBrush);
    DeleteObject(m_hBGBrush);
    
    DeleteObject(m_hGreenPen);
    DeleteObject(m_hRedPen);
    DeleteObject(m_hBluePen);
    DeleteObject(m_hMagentaPen);

    SelectObject(m_hAlphaDC, m_hPrevAlphaBmp);
    DeleteObject(m_hAlphaBmp);
    DeleteDC(m_hAlphaDC);
    ReleaseDC(m_hWnd, m_hAlphaDC);

    // 원래 지정되어 있던 비트맵으로 되돌려준다.
    SelectObject(m_hBackDC, m_hBackPrevBmp);
    DeleteObject(m_hBackBmp);
    DeleteDC(m_hBackDC);
    ReleaseDC(m_hWnd, m_hDC);
}


bool CGameManager::Init(HINSTANCE hInst)
{
    // 해상도 설정
    m_tResolution.x = 854.f;
    m_tResolution.y = 480.f;

	// lstrcpy : 유니코드일때와 멀티바이트 일때 자동으로 문자열 타입이
	// 변경된 함수가 호출된다.
	lstrcpy(m_strTitle, TEXT("Baba Is You by JHR"));
	lstrcpy(m_strClass, TEXT("Baba Is You by JHR"));

	m_hInst = hInst;

	Register();
	Create();

    // 화면에 그리기 위한 DC를 얻어온다.
    m_hDC = GetDC(m_hWnd);

    // BackBuffer용 DC를 생성한다.
    m_hBackDC = CreateCompatibleDC(m_hDC);

    // BackBuffer의 픽셀 정보를 저장하기 위한 비트맵을 만들어준다.
    m_hBackBmp = CreateCompatibleBitmap(m_hDC, (int)m_tResolution.x, (int)m_tResolution.y);

    // 위에서 만들어준 비트맵을 DC에 지정해준다. 지정해줄때 기존에 DC에 지정되어 있던
    // Bitmap 정보가 반환되게 된다.
    m_hBackPrevBmp = (HBITMAP)SelectObject(m_hBackDC, m_hBackBmp);

    // AlphaDC 생성
    m_hAlphaDC = CreateCompatibleDC(m_hDC);
    m_hAlphaBmp = CreateCompatibleBitmap(m_hDC, (int)m_tResolution.x, (int)m_tResolution.y);
    m_hPrevAlphaBmp = (HBITMAP)SelectObject(m_hAlphaDC, m_hAlphaBmp);

    // Brush를 만든다.
    m_hGreenBrush = CreateSolidBrush(RGB(0, 255, 0));
    m_hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
    m_hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
    m_hGrayBrush = CreateSolidBrush(RGB(30, 30, 30));
    m_hPurpleBrush = CreateSolidBrush(RGB(255, 0, 255));
    m_hBGBrush = CreateSolidBrush(RGB(21, 24, 31));

    // 윈도우에서 제공하는 StockObject 는 DeleteObject 하면 안된다.
    m_hTransparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
    m_hTransparentPen = (HPEN)GetStockObject(NULL_PEN);

    m_hGreenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
    m_hRedPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    m_hBluePen = CreatePen(PS_SOLID, 1, RGB(71, 191, 255));
    m_hMagentaPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));

    // 타이머를 생성한다.
    m_pTimer = new CTimer;

    m_pTimer->Init();

    // 경로관리자 초기화
    if (!GET_SINGLE(CPathManager)->Init())
        return false;

    // 폰트관리자 초기화
    if (!GET_SINGLE(CFontManager)->Init())
        return false;

    // 리소스 관리자 초기화
    if (!GET_SINGLE(CResourceManager)->Init())
        return false;

    // 입력관리자 초기화
    if (!GET_SINGLE(CInput)->Init(m_hWnd))
        return false;

    // 장면관리자 초기화
    if (!GET_SINGLE(CSceneManager)->Init())
        return false;

    m_pTimer->Start();

    GET_SINGLE(CInput)->AddActionKey("PrintInfo", VK_F1);
    GET_SINGLE(CInput)->AddBindAction("PrintInfo", KEY_TYPE::DOWN, this, &CGameManager::PrintInfoSwitch);

	return true;
}


void CGameManager::Create()
{
    m_hWnd = CreateWindow(m_strClass, m_strTitle, WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU |
        WS_MINIMIZEBOX,
        0, 0, (int)m_tResolution.x, (int)m_tResolution.y, nullptr, nullptr, m_hInst, nullptr);

    if (!m_hWnd)
    {
        return;
    }

    RECT    rc = { 0, 0, (int)m_tResolution.x, (int)m_tResolution.y };
    AdjustWindowRect(&rc, WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU |
        WS_MINIMIZEBOX, FALSE);
    MoveWindow(m_hWnd, 0, 0, rc.right - rc.left,
        rc.bottom - rc.top, FALSE);

    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);
}


void CGameManager::Register()
{
    WNDCLASSEX		tWndClass = {};

    tWndClass.cbSize = sizeof(WNDCLASSEX);
    tWndClass.style = CS_HREDRAW | CS_VREDRAW;
    // 아래는 윈도우의 메세지가 무엇인지에 따라 처리하기 위한 함수의 주소를
    // 지정해준다.
    tWndClass.lpfnWndProc = CGameManager::WndProc;
    tWndClass.cbClsExtra = 0;
    tWndClass.cbWndExtra = 0;
    tWndClass.hInstance = m_hInst;
    tWndClass.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));
    tWndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    tWndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    tWndClass.lpszMenuName = nullptr;
    tWndClass.lpszClassName = m_strClass;
    tWndClass.hIconSm = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));

    RegisterClassExW(&tWndClass);
}

LRESULT CGameManager::WndProc(HWND hWnd, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        m_bLoop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int CGameManager::Run()
{
    MSG msg = {};

    // 기본 메시지 루프입니다:
    // PeekMessage
    while (m_bLoop)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        else
        {
            Logic();
        }
    }

    return (int)msg.wParam;
}

void CGameManager::Logic()
{
    m_pTimer->Update();

    GET_SINGLE(CResourceManager)->Update(); // FMOD 시스템을 매번 업데이트한다.

    float   fDeltaTime = m_pTimer->GetDeltaTime();

    Input(fDeltaTime);

    if (Update(fDeltaTime))
        return;

    if (Collision(fDeltaTime))
        return;

    Render(fDeltaTime);
}

void CGameManager::Input(float fTime)
{
    GET_SINGLE(CInput)->Update(fTime);
}

bool CGameManager::Update(float fTime)
{
    if (GET_SINGLE(CSceneManager)->Update(fTime))
        return true;

    return GET_SINGLE(CSceneManager)->PostUpdate(fTime);
}

bool CGameManager::Collision(float fTime)
{
    return GET_SINGLE(CSceneManager)->Collision(fTime);
}

void CGameManager::Render(float fTime)
{
    CScene* pCurrentScene = GET_SINGLE(CSceneManager)->GetScene();

    switch (pCurrentScene->GetSceneType())
    {
    case SCENE_TYPE::START:
    {
        HBRUSH hPrevBrush = (HBRUSH)SelectObject(m_hBackDC, GetStockObject(BLACK_BRUSH));
        Rectangle(m_hBackDC, 0, 0, (int)m_tResolution.x, (int)m_tResolution.y);
        SelectObject(m_hBackDC, hPrevBrush);
        break;
    }
    case SCENE_TYPE::MAINMAP:
    {
        HBRUSH hPrevBrush = (HBRUSH)SelectObject(m_hBackDC, BGBRUSH);
        Rectangle(m_hBackDC, -1, -1, (int)RESOLUTION.x + 1, (int)RESOLUTION.y + 1);
        SelectObject(m_hBackDC, hPrevBrush);
        break;
    }
    case SCENE_TYPE::STAGE:
    {
        HBRUSH hPrevBrush = (HBRUSH)SelectObject(m_hBackDC, BGBRUSH);
        Rectangle(m_hBackDC, -1, -1, (int)RESOLUTION.x + 1, (int)RESOLUTION.y + 1);
        SelectObject(m_hBackDC, hPrevBrush);
        break;
    }
    case SCENE_TYPE::EDIT:
    {
        HBRUSH hPrevBrush = (HBRUSH)SelectObject(m_hBackDC, GetStockObject(BLACK_BRUSH));
        Rectangle(m_hBackDC, 0, 0, (int)m_tResolution.x, (int)m_tResolution.y);
        SelectObject(m_hBackDC, hPrevBrush);
        break;
    }

    case SCENE_TYPE::ANIMEDIT:
    {
        HBRUSH hPrevBrush = (HBRUSH)SelectObject(m_hBackDC, GetStockObject(GRAY_BRUSH));
        Rectangle(m_hBackDC, -1, -1, (int)m_tResolution.x, (int)m_tResolution.y);
        SelectObject(m_hBackDC, hPrevBrush);
        break;
    }

    default:
        break;
    }

    GET_SINGLE(CSceneManager)->PrevRender(fTime);
    GET_SINGLE(CSceneManager)->Render(m_hBackDC, fTime);
    GET_SINGLE(CSceneManager)->PostRender(fTime);

    // FPS 출력
    if (m_bPrintInfo)
    {
        TCHAR   strFPS[64] = { };

        _stprintf_s(strFPS, TEXT("FPS : %.f"), m_pTimer->GetFPS());

        TextOut(m_hBackDC, 0, 0, strFPS, lstrlen(strFPS));
    }

    // 마우스를 출력한다.
    GET_SINGLE(CInput)->Render(m_hBackDC, fTime);

    // 1번인자의 DC에 6번인자에 지정된 DC를 그려준다.
    // 2번, 3번 인자는 DC에서 그려줄 위치를 지정한다.
    // 4번, 5번 인자에 들어가는 크기로 그려준다.
    // 7번, 8번 인자는 BackDC에서 그리기를 시작할 위치를 지정해준다.
    BitBlt(m_hDC, 0, 0, (int)m_tResolution.x, (int)m_tResolution.y, m_hBackDC,
        0, 0, SRCCOPY);
}

void CGameManager::Exit()
{
    DestroyWindow(m_hWnd);
}

