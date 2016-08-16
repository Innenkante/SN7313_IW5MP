
#include "stdafx.h"
#include "LinkingFix.h"


DWORD WINAPI KeyBoardHook(LPVOID lpParam)
{
	//My keyboardhook
	Menu.CurrentActiveMenu = Menu.ESPMenuTab;
	Menu.BasePosX = 100;
	Menu.BasePosY = 100;
	Menu.Enabled = true;
	while (true)
	{
		if (GetAsyncKeyState(VK_F1))
		{
			Menu.Enabled = Utils.ChangeState(Menu.Enabled);
			Sleep(100);
		}
		if (!Menu.Enabled)
		{
			Sleep(10);
			continue;
		}
		if (GetAsyncKeyState(VK_F2))
		{
			if (Menu.CurrentActiveMenu == 3)
				Menu.CurrentActiveMenu = 0;
			else
				Menu.CurrentActiveMenu++;
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_RIGHT) && GetAsyncKeyState(VK_CONTROL))
		{
			Menu.BasePosX++;
			Sleep(1);
		}
		if (GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_CONTROL))
		{
			Menu.BasePosX--;
			Sleep(1);
		}
		if (GetAsyncKeyState(VK_UP) && GetAsyncKeyState(VK_CONTROL))
		{
			Menu.BasePosY--;
			Sleep(1);
		}
		if (GetAsyncKeyState(VK_DOWN) && GetAsyncKeyState(VK_CONTROL))
		{
			Menu.BasePosY++;
			Sleep(1);
		}

	}
	Sleep(10);
	return 1;
}

#pragma region Hooks

DWORD hkShowListCall = 0x00475CE0;
DWORD hkShowListJmp = 0x00644280;

__declspec(naked) void hkShowList()
{
	__asm
	{
		CALL[hkShowListCall]
		PUSHAD;
		PUSHFD;
	}
	Menu.DrawMenuWrapper();
	__asm
	{
		POPFD;
		POPAD;
		JMP[hkShowListJmp]

	}
}


DWORD hkDraw2DJmp = 0x430436;
__declspec(naked) void hkDraw2D()
{
	__asm PUSHAD
	__asm PUSHFD

	//TODO add aimbot wrapper here after menu is done
	__asm POPFD
	__asm POPAD

	__asm PUSH ESI
	__asm MOV ESI, [ESP + 8]
		__asm PUSH ESI

	__asm JMP[hkDraw2DJmp]
}

#pragma endregion

BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD Reason, LPVOID Reserved)
{
	if (Reason == DLL_PROCESS_ATTACH) {
		Hook.DetourFunction((PBYTE)0x0064427B, (PBYTE)hkShowList, 5); 
		Hook.DetourFunction((PBYTE)0x430430, (PBYTE)hkDraw2D, 6); 
		CreateThread(NULL, 0, &KeyBoardHook, NULL, 0, NULL); //Creating the Thread
	}

	return TRUE;
}
