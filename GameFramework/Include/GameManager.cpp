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

    // ���� �����Ǿ� �ִ� ��Ʈ������ �ǵ����ش�.
    SelectObject(m_hBackDC, m_hBackPrevBmp);
    DeleteObject(m_hBackBmp);
    DeleteDC(m_hBackDC);
    ReleaseDC(m_hWnd, m_hDC);
}


bool CGameManager::Init(HINSTANCE hInst)
{
    // �ػ� ����
    m_tResolution.x = 854.f;
    m_tResolution.y = 480.f;

	// lstrcpy : �����ڵ��϶��� ��Ƽ����Ʈ �϶� �ڵ����� ���ڿ� Ÿ����
	// ����� �Լ��� ȣ��ȴ�.
	lstrcpy(m_strTitle, TEXT("Baba Is You by JHR"));
	lstrcpy(m_strClass, TEXT("Baba Is You by JHR"));

	m_hInst = hInst;

	Register();
	Create();

    // ȭ�鿡 �׸��� ���� DC�� ���´�.
    m_hDC = GetDC(m_hWnd);

    // BackBuffer�� DC�� �����Ѵ�.
    m_hBackDC = CreateCompatibleDC(m_hDC);

    // BackBuffer�� �ȼ� ������ �����ϱ� ���� ��Ʈ���� ������ش�.
    m_hBackBmp = CreateCompatibleBitmap(m_hDC, (int)m_tResolution.x, (int)m_tResolution.y);

    // ������ ������� ��Ʈ���� DC�� �������ش�. �������ٶ� ������ DC�� �����Ǿ� �ִ�
    // Bitmap ������ ��ȯ�ǰ� �ȴ�.
    m_hBackPrevBmp = (HBITMAP)SelectObject(m_hBackDC, m_hBackBmp);

    // AlphaDC ����
    m_hAlphaDC = CreateCompatibleDC(m_hDC);
    m_hAlphaBmp = CreateCompatibleBitmap(m_hDC, (int)m_tResolution.x, (int)m_tResolution.y);
    m_hPrevAlphaBmp = (HBITMAP)SelectObject(m_hAlphaDC, m_hAlphaBmp);

    // Brush�� �����.
    m_hGreenBrush = CreateSolidBrush(RGB(0, 255, 0));
    m_hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
    m_hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
    m_hGrayBrush = CreateSolidBrush(RGB(30, 30, 30));
    m_hPurpleBrush = CreateSolidBrush(RGB(255, 0, 255));
    m_hBGBrush = CreateSolidBrush(RGB(21, 24, 31));

    // �����쿡�� �����ϴ� StockObject �� DeleteObject �ϸ� �ȵȴ�.
    m_hTransparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
    m_hTransparentPen = (HPEN)GetStockObject(NULL_PEN);

    m_hGreenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
    m_hRedPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    m_hBluePen = CreatePen(PS_SOLID, 1, RGB(71, 191, 255));
    m_hMagentaPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));

    // Ÿ�̸Ӹ� �����Ѵ�.
    m_pTimer = new CTimer;

    m_pTimer->Init();

    // ��ΰ����� �ʱ�ȭ
    if (!GET_SINGLE(CPathManager)->Init())
        return false;

    // ��Ʈ������ �ʱ�ȭ
    if (!GET_SINGLE(CFontManager)->Init())
        return false;

    // ���ҽ� ������ �ʱ�ȭ
    if (!GET_SINGLE(CResourceManager)->Init())
        return false;

    // �Է°����� �ʱ�ȭ
    if (!GET_SINGLE(CInput)->Init(m_hWnd))
        return false;

    // �������� �ʱ�ȭ
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
    // �Ʒ��� �������� �޼����� ���������� ���� ó���ϱ� ���� �Լ��� �ּҸ�
    // �������ش�.
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

    // �⺻ �޽��� �����Դϴ�:
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

    GET_SINGLE(CResourceManager)->Update(); // FMOD �ý����� �Ź� ������Ʈ�Ѵ�.

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

    // FPS ���
    if (m_bPrintInfo)
    {
        TCHAR   strFPS[64] = { };

        _stprintf_s(strFPS, TEXT("FPS : %.f"), m_pTimer->GetFPS());

        TextOut(m_hBackDC, 0, 0, strFPS, lstrlen(strFPS));
    }

    // ���콺�� ����Ѵ�.
    GET_SINGLE(CInput)->Render(m_hBackDC, fTime);

    // 1�������� DC�� 6�����ڿ� ������ DC�� �׷��ش�.
    // 2��, 3�� ���ڴ� DC���� �׷��� ��ġ�� �����Ѵ�.
    // 4��, 5�� ���ڿ� ���� ũ��� �׷��ش�.
    // 7��, 8�� ���ڴ� BackDC���� �׸��⸦ ������ ��ġ�� �������ش�.
    BitBlt(m_hDC, 0, 0, (int)m_tResolution.x, (int)m_tResolution.y, m_hBackDC,
        0, 0, SRCCOPY);
}

void CGameManager::Exit()
{
    DestroyWindow(m_hWnd);
}

