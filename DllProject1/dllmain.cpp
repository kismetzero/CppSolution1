// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <cstdio>

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
        if (GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            break;
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
    case DLL_THREAD_ATTACH:
        g_hModule = hModule;
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, DllWorkThread, hModule, 0, nullptr);
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

