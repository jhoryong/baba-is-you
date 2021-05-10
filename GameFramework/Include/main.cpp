
#include "GameManager.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
   // _CrtSetBreakAlloc(4882);

    srand((unsigned int)time(0));
    rand();

    if (!GET_SINGLE(CGameManager)->Init(hInstance))
    {
        DESTROY_SINGLE(CGameManager);
        return 0;
    }

    int iRetVal = GET_SINGLE(CGameManager)->Run();

    DESTROY_SINGLE(CGameManager);

    return iRetVal;
}