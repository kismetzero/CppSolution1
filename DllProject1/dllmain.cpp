// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <cstdio>
#include "MyHook.h"

HMODULE g_hModule;

static DWORD WINAPI DllWorkThread(LPVOID lpParam)
{
    HMODULE hModule = static_cast<HMODULE>(lpParam);
    AllocConsole();
    SetConsoleTitleA("Injected DLL Console");
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    printf("Hello Dll! \n");
    printf("DLL Base: 0x%p \n", hModule);
    printf("Press Space to unload...\n");
    while (1)
    { 
        if (GetAsyncKeyState(VK_SPACE) & 0x1)
        {
            break;
        }

        if (GetAsyncKeyState('Q') & 0x1)
        {
            printf("Press Q : mh_init() \n");
            mh_init();
        }

        if (GetAsyncKeyState('W') & 0x1)
        {
            printf("Press W : mh_hook_create() \n");
            mh_hook_create();
        }

        if (GetAsyncKeyState('E') & 0x1)
        {
            printf("Press E : mh_hook_on() \n");
            mh_hook_on();
        }

        if (GetAsyncKeyState('A') & 0x1)
        {
            printf("Press A : mh_uninit() \n");
            mh_uninit();
        }

        if (GetAsyncKeyState('S') & 0x1)
        {
            printf("Press S : mh_hook_remove() \n");
            mh_hook_remove();
        }

        if (GetAsyncKeyState('D') & 0x1)
        {
            printf("Press D : mh_hook_off() \n");
            mh_hook_off();
        }

        if (GetAsyncKeyState('R') & 0x1)
        {
            printf("Press R : MBoxA() \n");
            MBoxA();
        }
    }
    fclose(stdout);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        break;
    case DLL_THREAD_ATTACH:
        g_hModule = hModule;
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, DllWorkThread, hModule, 0, nullptr);
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

