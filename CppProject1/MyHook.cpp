#include "MyHook.h"
#include <windows.h>
#include "MinHook.h"

typedef int(WINAPI* fpMessageBoxA)(HWND, LPCSTR, LPCSTR, UINT);
fpMessageBoxA originalMessageBoxA = nullptr;

int WINAPI hookMessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
{
	return originalMessageBoxA(hWnd, "你好！MessageBoxA Hook", "标题：MessageBoxA Hook", uType);
}

bool mh_flag_init = false;
bool mh_flag_hook_create = false;
bool mh_flag_hook_en = false;

void mh_init()
{
	if (!mh_flag_init)
	{
		if (MH_Initialize() == MH_OK)
		{
			mh_flag_init = true;
		}
		mh_flag_hook_create = false;
		mh_flag_hook_en = false;
	}
}

void mh_uninit()
{
	if (mh_flag_init)
	{
		if (MH_Uninitialize() == MH_OK)
		{
			mh_flag_init = false;
			mh_flag_hook_create = false;
			mh_flag_hook_en = false;
		}
	}
}

void mh_hook_create()
{
	if (mh_flag_init && !mh_flag_hook_create)
	{
		if (MH_CreateHook(&MessageBoxA, &hookMessageBoxA, reinterpret_cast<void**>(&originalMessageBoxA)) == MH_OK)
		{
			mh_flag_hook_create = true;
		}
		mh_flag_hook_en = false;
	}
}

void mh_hook_remove()
{
	if (mh_flag_init && mh_flag_hook_create)
	{
		if (MH_RemoveHook(&MessageBoxA) == MH_OK)
		{
			mh_flag_hook_create = false;
			mh_flag_hook_en = false;
		}
	}
}

void mh_hook_on()
{
	if (mh_flag_hook_create && !mh_flag_hook_en)
	{
		if (MH_EnableHook(&MessageBoxA) == MH_OK)
		{
			mh_flag_hook_en = true;
		}
	}
}

void mh_hook_off()
{
	if (mh_flag_hook_create && mh_flag_hook_en)
	{
		if (MH_DisableHook(&MessageBoxA) == MH_OK)
		{
			mh_flag_hook_en = false;
		}
	}
}

void MBoxA()
{
	MessageBoxA(NULL, "你好！MessageBoxA", "标题：MessageBoxA", NULL);
}
