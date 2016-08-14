
#include "stdafx.h"

#include "LinkingFix.h"
char* GetPlayerName()
{
	const char* Name = (const char*)PLAYERNAMEOFF;
	char buf[32] = "";
	sprintf_s(buf, Name);
	return buf;
}

char* GetPlayerID()
{
	int* ID = (int*)XUIDOFF;
	char buf[16];
	sprintf_s(buf, "%ld", *ID);
	return buf;
}

char* GetServerName()
{
	const char* ServerName = (const char*)SERVERNAMEOFF;
	char buf[64] = "";
	sprintf_s(buf, ServerName);
	return buf;
}

char* GetServerIP()
{
	const char* ServerIP = (const char*)SERVERIPOFF;
	char buf[32] = "";
	sprintf_s(buf, ServerIP);
	return buf;
}

int GetGUID(int index)
{
	return *(int*)(*(DWORD *)0x132C3A0 + 0x60 + (0x40 * index));
}


int CurrentTabIndex = 0;
int CurrentOptionIndex = 0;
bool RecodedMenuIsEnabled = true;

std::map<std::string, bool> ESP_Options;

bool ESP_DrawCirlce = true;
bool ESP_DrawBone = false;
bool ESP_DrawName = true;
bool ESP_DrawSlot = false;
bool ESP_DrawRank = false;
bool ESP_DrawDistance = false;
bool ESP_DrawScore = false;
bool ESP_DrawXUID = false;
bool ESP_Draw3DBox = false;
bool ESP_DrawWeapon = false;
bool ESP_DrawSnapline = false;
bool ESP_DrawIcon = true;




void *DetourFunction(BYTE *src, const BYTE *dst, const int len)
{
	BYTE *jmp = (BYTE*)malloc(len + 5);
	DWORD dwBack;

	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &dwBack);
	memcpy(jmp, src, len);
	jmp += len;
	jmp[0] = 0xE9;
	*(DWORD*)(jmp + 1) = (DWORD)(src + len - jmp) - 5;
	src[0] = 0xE9;
	*(DWORD*)(src + 1) = (DWORD)(dst - src) - 5;
	for (int i = 5; i<len; i++)
		src[i] = 0x90;
	VirtualProtect(src, len, dwBack, &dwBack);
	return (jmp - len);
}

DWORD dwCall = HOOKCALL;
DWORD dwReturn = HOOKRETURN; 

__declspec(naked) void hkShowList()
{
	__asm
	{
		CALL[dwCall]
		PUSHAD;
		PUSHFD;
	}
	Menu.DrawMenuWrapper();
	__asm
	{
		POPFD;
		POPAD;
		JMP[dwReturn]

	}
}/////////////////////////////////////////////////////////////////////////////////////////////////////////

DWORD dwJMPback = 0x430436;
__declspec(naked) void hkDraw2D() //MPGH I lub you
{
	__asm PUSHAD
	__asm PUSHFD

	//Aimbot

	__asm POPFD
	__asm POPAD


	__asm PUSH ESI
	__asm MOV ESI, [ESP + 8]
	__asm PUSH ESI

	__asm JMP[dwJMPback]
}

DWORD dwWritePacketReturn = 0x420AB5; //Base 0x00420AB0 + 5 -> OUr hook is 5 bytes long midfunction hook has to 5 bytes min.
__declspec(naked) void hkWritePacket()
{
	__asm
	{
		mov eax, 0x1058 //The first Instruction of the dissasembly to execute the old code
		pushad //Saving the stacks
		pushfd //Saving the Flags
	}
	//Some Operation with the packets lel
	__asm
	{
		popfd //Restoring the flags
		popad //Restoring the stack
		jmp dwWritePacketReturn //Jumping back to the actual code
	}
}

DWORD WINAPI _MainMethod(LPVOID lpParam)
{
	//My keyboardhook
	while (true)
	{

		
	}

	return 1;
}

BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD Reason, LPVOID Reserved)
{
	if (Reason == DLL_PROCESS_ATTACH) {
		DetourFunction((PBYTE)0x0064427B, (PBYTE)hkShowList, 5); //Thanks to google/pastebin/hkDavy for showing me the hook
		DetourFunction((PBYTE)0x430430, (PBYTE)hkDraw2D, 6); //MPGH ftw
		DetourFunction((PBYTE)0x420AB0, (PBYTE)hkWritePacket, 5);

		CreateThread(NULL, 0, &_MainMethod, NULL, 0, NULL); //Creating the Thread
	}

	return TRUE;
}
