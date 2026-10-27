#include "Win32Helper.h"
#include <windows.h>
#include <shellapi.h>
#include <strsafe.h>

#define WM_TRAYICON (WM_USER + 1)

void CreateTrayIcon(void* hwnd) {
    NOTIFYICONDATA nid{};
    nid.cbSize = sizeof(nid);
    nid.hWnd = (HWND)hwnd;
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
    nid.uCallbackMessage = WM_TRAYICON;
    nid.hIcon = LoadIcon(nullptr, IDI_APPLICATION); // 需要设置有效图标
    StringCchCopy(nid.szTip, ARRAYSIZE(nid.szTip), TEXT("托盘提示"));
    Shell_NotifyIcon(NIM_ADD, &nid);
}
