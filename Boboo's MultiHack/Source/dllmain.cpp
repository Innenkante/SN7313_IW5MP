//TODO CLEAN SOURCE FROM UNESCESSARY STUFF AND USE DIFFRENT FILES MAYBE?
#include "stdafx.h"

bool NoSpreadEnabled = false;
bool NoRecoilEnabled = false;
bool WhEnabled = false;
bool FullBrightEnabled = false;
bool LaserEnabled = false;
bool RadarEnabled = false;
bool MenuEnabled = true;
bool GrabGuidEnabled = false;
vec4_t ColorWhite = { 1.0f,1.0f,1.0f,1.0f };
vec4_t ColorGreen = { 0.0f,  1.0f,  0.0f,  1.0f };
vec4_t ColorRed = { 1.0f,  0.0f,  0.0f,  1.0f };
vec4_t ColorBlue = { 0.0f,  0.0f,  1.0f,  1.0f };
void* Font_Menu_GUID;



DrawEngineText_t DrawEngineText_ = (DrawEngineText_t)DRAWENGINETEXTOFF;
DrawRotatedPic_t DrawRotatedPic_ = (DrawRotatedPic_t)0x0042F420;
RegisterFont_t RegisterFont_ = (RegisterFont_t)REGISTERFONTOFF;
DrawEngineRadar_t DrawEngineRadar_ = (DrawEngineRadar_t)DRAWENGINERADAROFF;
OverlayPackage_t OverlayPackage_ = (OverlayPackage_t)0x0054BD70;
OverlayEnemy_t OverlayEnemey_ = (OverlayEnemy_t)0x004CD2B0;
OverlayFriendly_t OverlayFriendly_ = (OverlayFriendly_t)0x004370C0;
//OverlayHeli_t OverlayHeli_ = (OverlayHeli_t)0x004C3FB0;
//OverlayLocal_t OverlayLocal_ = (OverlayLocal_t)0x004FD740;
//OverlayPlane_t OverlayPlane_ = (OverlayPlane_t)0x0052A6C0;
//OverlayTurret_t OverlayTurret_ = (OverlayTurret_t)0x00561BF0;

RegisterShader_t RegisterShader_ = (RegisterShader_t)REGISTERSHADEROFF;
GetScreenMatrix_t GetScreenMatrix_ = (GetScreenMatrix_t)SCREENMATRIXOFF;
DrawNameTagsOverhead_t DrawNameTags_ = (DrawNameTagsOverhead_t)0x00588A10;

//Aimbot section
RegisterTag_t RegisterTag_ = (RegisterTag_t)0x4922E0;





bool GetState(bool state)
{
	if (state)
		state = false;
	else
		state = true;
	return state;
}


void MessageBoxMethod(const LPCSTR sometext)
{
	MessageBoxA(0, sometext, "DLL Message", MB_OK | MB_ICONINFORMATION);
}

void SendCommandToConsole(char* CMD)
{
	DWORD dwCall = SENDCOMMANDTOCONSOLEOFF;
	__asm
	{
		push CMD;
		push 0;
		push 0;
		call dwCall;
		add esp, 0xC;
	}

}

void* RegisterFont(char* font)
{
	return RegisterFont_(font);
}

int* RegisterShader(char* shader)
{
	return RegisterShader_(shader);
}

void DrawTextMW3(float x, float y, void* pFont, float* color, const char *Text, ...)
{
	char buf[1024] = "";
	va_list va_alist;
	va_start(va_alist, Text);
	vsnprintf_s(buf, sizeof(buf), Text, va_alist);
	va_end(va_alist);

	DrawEngineText_((char*)Text, 0x7FFFFFFF, pFont, x, y, 1.0f, 1.0f, 0.0f, color, 0);
}

void NoRecoil(bool state)
{
	BYTE* nr = (BYTE*)NORECOILOFF;
	if (state)
		*nr = 235;
	else
		*nr = 116;
}


void NoSpread(bool state)
{
	float* nospr = (float*)NOSPREADOFF;
	if (state)
		*nospr = 0;
	else
		*nospr = 0.6499999762f;
}

void ChangeName()
{
	srand(static_cast<int>(time(NULL)));
	BYTE* checkname = (BYTE*)PLAYERNAMECHECKBYTEOFF;
	*checkname = 0xC3;
	int random = rand() % 100;
	char* name = (char*)PLAYERNAMEOFF;
	char newname[16];
	sprintf(newname, "Player %d", random);
	for (int i = 0; i < 16; i++)
		name[i] = newname[i];
}


void RandomCreds()
{
	srand(static_cast<int>(time(NULL)));
	*(ULONG*)0x05CCB272 = (ULONG)(0x11000010000000 + rand() + (rand() * 10) + (rand() * 100));//steam
	*(ULONG*)0x00464A58 = (ULONG)(0x11000010000000 + rand() + (rand() * 10) + (rand() * 100));//xna
	*(ULONG*)0x05A7B1D8 = (ULONG)(0x11000010000000 + rand() + (rand() * 10) + (rand() * 100));//xuid

	ChangeName();
}

void FixBlindPerks()
{
	ClientInfo_T* Clients[18];
	for (int i = 0; i < 18; i++)
	{
		Clients[i] = (ClientInfo_T*)(CLIENTOFF + ((int)CLIENTSIZE * i));
		if (Clients[i] != Clients[*(int*)0x8FF250])
		{
			if (Clients[i]->Perk & 0x20 || Clients[i]->Perk & 0x40)
				Clients[i]->Perk = 0x0;
		}
	}
}

void FullBright(bool state)
{
	int* fullbright = (int*)FULLBRIGHTOFF;
	if (state)
		*fullbright = 4;
	else
		*fullbright = 9;

}


void UnlockClasses()
{
	int *force1 = (int*)FORCECLASS1;
	int *force2 = (int*)FORCECLASS2;
	int *force3 = (int*)FORCECLASS3;
	int *force4 = (int*)FORCECLASS4;
	int *force5 = (int*)FORCECLASS5;
	int *force6 = (int*)FORCECLASS6;
	int *force7 = (int*)FORCECLASS7;
	int *force8 = (int*)FORCECLASS8;
	int *force9 = (int*)FORCECLASS9;

	*force1 = 7;
	*force2 = 0;
	*force3 = 0;
	*force4 = 0;
	*force5 = 0;
	*force6 = 0;
	*force7 = 0;
	*force8 = 0;
	*force9 = 0;
}

void Laser(bool state)
{
	BYTE* laser = (BYTE*)LASEROFF;

	if (state)
		*laser = 0;
	else
		*laser = 37;
}


char* GetBoolInChar(bool b)
{
	char buf[40] = "";
	if (b)
		sprintf_s(buf, "^2On");
	if (!b)
		sprintf_s(buf, "^1Off");
	return buf;
}

char* GetPlayerName()
{
	const char* Name = (const char*)PLAYERNAMEOFF;
	char buf[32] = "";
	sprintf(buf, Name);
	return buf;
}

char* GetPlayerID()
{
	int* ID = (int*)XUIDOFF;
	char buf[16];
	sprintf(buf, "%ld", *ID);
	return buf;
}

char* GetServerName()
{
	const char* ServerName = (const char*)SERVERNAMEOFF;
	char buf[64] = "";
	sprintf(buf, ServerName);
	return buf;
}

char* GetServerIP()
{
	const char* ServerIP = (const char*)SERVERIPOFF;
	char buf[32] = "";
	sprintf(buf, ServerIP);
	return buf;
}

void DrawNameTags()
{
	CG_T* cg = (CG_T*)CGOFF;
	Entity_T* Entity[18];

	for (int i = 0; i < 18; i++)
	{
		Entity[i] = (Entity_T*)(0x00A08630 + (i * 0x000001F8));
		if (Entity[i]->Valid)
			DrawNameTags_(cg->ClientNumber, *Entity[i], 1.0f);
	}
}


void ChopperBoxes()
{
	DrawNameTags();
	DWORD dwCall = 0x5AA470;
	if (WhEnabled)
	{
		FixBlindPerks();
		__asm
		{
			push 0x0;
			call[dwCall];
			add esp, 0x4;
		}
	}
	else
		return;
}

void DrawRadar()
{
	if (RadarEnabled)
	{
		RefDef_T* RefDef = (RefDef_T*)REFDEFOFF;
		RadarHud radarhud;
		int RadarW = 225;
		int RadarH = RadarW;

		int RadarX = RefDef->Width - RadarW;
		int RadarY = 13;

		radarhud.x = ScaleRadarX(RadarX);
		radarhud.y = ScaleRadarY(RadarY);
		radarhud.w = ScaleRadarX(RadarW);
		radarhud.h = ScaleRadarY(RadarH);

		DrawEngineRadar_(0, 0, 0, &radarhud, RegisterShader("black"), ColorWhite);
		OverlayPackage_(0, 0, 0, &radarhud, *RegisterShader("black"), ColorWhite);

		//OverlayLocal_(0, 0, 0, &radarhud, ColorBlue);
		OverlayEnemey_(0, 0, 0, &radarhud, ColorRed);
		OverlayFriendly_(0, 0, 0, &radarhud, ColorGreen);

	}
	else
		return;
}


void ForceJugg()
{
	CG_T* cg = (CG_T*)CGOFF;
	int* MagicNum = (int*)MATCHIDOFF;
	char buffer[1024];
	ClientInfo_T* LocalClient = (ClientInfo_T*)CLIENTOFF + CLIENTSIZE * cg->ClientNumber;
	if (LocalClient->Team == 0)
		return;
	if (LocalClient->Team == 1)
		sprintf(buffer, "cmd mr %d 9 allies", *MagicNum);
	if(LocalClient->Team == 2)
		sprintf(buffer, "cmd mr %d 9 allies", *MagicNum);
	SendCommandToConsole(buffer);

}

void ChangeTeam()
{
	CG_T* cg = (CG_T*)CGOFF;
	int* MagicNum = (int*)MATCHIDOFF;
	char buffer[1024];
	ClientInfo_T* LocalClient = (ClientInfo_T*)CLIENTOFF + CLIENTSIZE * cg->ClientNumber;
	if (LocalClient->Team == 0)
		return;
	if (LocalClient->Team == 1)
		sprintf(buffer, "cmd mr %d 2 axis", *MagicNum);
	if(LocalClient->Team == 2)
		sprintf(buffer, "cmd mr %d 2 allies", *MagicNum);

	SendCommandToConsole(buffer);
}

void CallCrashVote()
{
	char buffer[1024];
	sprintf(buffer,"callvote map_rotate");
	SendCommandToConsole(buffer);
}

void GrabGUID()
{
	if (!GrabGuidEnabled)
		return;
	int Count_Entrys = 0;
	for (int i = 0; i < 18; i++)
	{
		char* Name = (char*)(0x9FC754 + (i * (int)CLIENTSIZE)); //I am so fucking retardet client struct would have worked but I just forgot 2 brackets
		if (strlen(Name) == 0)
			continue;
		int tmp = *(int*)(*(DWORD *)0x132C3A0 + 0x60 + (0x40 * i));
		if (tmp == 0)
			continue;
		Count_Entrys++;
		char tmp_buf[2048];
		sprintf_s(tmp_buf, "^3 %s ^3[^1 %d ^3] ^4| ^2 %d", Name,i, tmp);
		DrawTextMW3(10, 190 + Count_Entrys * 24, RegisterFont(FONT_BIG_DEV), ColorWhite, tmp_buf);
	}
}

void DrawCrossHair()
{
	RefDef_T* refdef = (RefDef_T*)REFDEFOFF;

	if (!refdef->Width || !refdef->Height)
		return;
	DrawTextMW3(refdef->Width / 2 - 7 , refdef->Height / 2 + 10, RegisterFont(FONT_BIG_DEV), ColorGreen, "+"); //Maybe -6 and + 11?

}

//TODO DrawLine just to make it work xD 


void Menu()
{

	char buf[4096];
	sprintf(buf, "^2Boboo's ^3MultiHack ^4beta!\n");
	strncat(buf, "^5WallHack[F3]: ", sizeof(buf));
	strncat(buf, GetBoolInChar(WhEnabled), sizeof(buf));
	strncat(buf, "\n^5", sizeof(buf));
	strncat(buf, "No Recoil[F4]: ", sizeof(buf));
	strncat(buf, GetBoolInChar(NoRecoilEnabled), sizeof(buf));
	strncat(buf, "\n^5", sizeof(buf));
	strncat(buf, "No Spread[F5]: ", sizeof(buf));
	strncat(buf, GetBoolInChar(NoSpreadEnabled), sizeof(buf));
	strncat(buf, "\n^5", sizeof(buf));
	strncat(buf, "Fullbright[F6]: ", sizeof(buf));
	strncat(buf, GetBoolInChar(FullBrightEnabled), sizeof(buf));
	strncat(buf, "\n^5", sizeof(buf));
	strncat(buf, "Second radar[F7]: ", sizeof(buf));
	strncat(buf, GetBoolInChar(RadarEnabled), sizeof(buf));
	strncat(buf, "\n^5", sizeof(buf));
	strncat(buf, "Laser[F8]: ", sizeof(buf));
	strncat(buf, GetBoolInChar(LaserEnabled), sizeof(buf));
	strncat(buf, "\n^5", sizeof(buf));
	strncat(buf, "Unlock Classes[F9]", sizeof(buf));
	strncat(buf, "\n^5", sizeof(buf));
	strncat(buf, "Change Credentials[F10]", sizeof(buf));
	strncat(buf, "\n^5", sizeof(buf));
	strncat(buf, "ChangeTeam[F11]", sizeof(buf));
	strncat(buf, "\n^5", sizeof(buf));
	strncat(buf, "Force Juggernaut[F12]", sizeof(buf));
	strncat(buf, "\n^5",sizeof(buf));
	strncat(buf, "Crash Vote[END]", sizeof(buf));
	strncat(buf, "\n^5", sizeof(buf));
	strncat(buf, "Show player IDs[INSERT]", sizeof(buf));
	strncat(buf, "\n^3", sizeof(buf));
	//Other stuff:
	strncat(buf, "Name: ^:", sizeof(buf));
	strncat(buf, GetPlayerName(), sizeof(buf));
	strncat(buf, "\n^3", sizeof(buf));
	strncat(buf, "ID: ^:", sizeof(buf));
	strncat(buf, GetPlayerID(), sizeof(buf));
	strncat(buf, "\n^3", sizeof(buf));
	strncat(buf, "Servername: ^;", sizeof(buf));
	strncat(buf, GetServerName(), sizeof(buf));
	strncat(buf, "\n^3", sizeof(buf));
	strncat(buf, "Server IP: ^;", sizeof(buf));
	strncat(buf, GetServerIP(), sizeof(buf));
	strncat(buf, "\n", sizeof(buf));


	if (MenuEnabled)
		DrawTextMW3(550 / 2, 40, RegisterFont(FONT_BIG_DEV), ColorWhite, buf);
}

//HOOK!////////////////////////////////////////////////////////////////////////////////////
void MakeJMP(BYTE *pAddress, DWORD dwJumpTo, DWORD dwLen)
{
	DWORD dwOldProtect, dwBkup, dwRelAddr;

	VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	dwRelAddr = (DWORD)(dwJumpTo - (DWORD)pAddress) - 5;
	*pAddress = 0xE9;

	*((DWORD *)(pAddress + 0x1)) = dwRelAddr;
	for (DWORD x = 0x5; x < dwLen; x++) *(pAddress + x) = 0x90;
	VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);

	return;
}

DWORD dwCall = HOOKCALL;
DWORD dwReturn = HOOKRETURN;

__declspec(naked) void ShowMenu()
{
	__asm
	{
		CALL[dwCall]
		PUSHAD;
		PUSHFD;
	}
	Menu();
	GrabGUID();
	DrawCrossHair();
	ChopperBoxes();
	DrawRadar();
	__asm
	{
		POPFD;
		POPAD;
		JMP[dwReturn]

	}
}/////////////////////////////////////////////////////////////////////////////////////////////////////////


DWORD WINAPI _MainMethod(LPVOID lpParam)
{
	while (true)
	{
		if (GetAsyncKeyState(VK_F2)) //ChatSpam
		{
			MenuEnabled = GetState(MenuEnabled);
			Sleep((100));
		}
		if (GetAsyncKeyState(VK_F3)) //ChopperBox
		{
			WhEnabled = GetState(WhEnabled);
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_F4)) //NoRecoil
		{
			NoRecoilEnabled = GetState(NoRecoilEnabled);
			NoRecoil(NoRecoilEnabled);
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_F5)) //NoSpread
		{
			NoSpreadEnabled = GetState(NoSpreadEnabled);
			NoSpread(NoSpreadEnabled);
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_F6)) ////FullBright
		{
			FullBrightEnabled = GetState(FullBrightEnabled);
			FullBright(FullBrightEnabled); 
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_F7)) //Second Radar
		{
			RadarEnabled = GetState(RadarEnabled);
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_F8)) //Laser
		{
			LaserEnabled = GetState(LaserEnabled);
			Laser(LaserEnabled);
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_F9)) //Unlock locked classes
		{
			UnlockClasses();
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_F10)) //Randomize credentials
		{
			RandomCreds();
			Sleep(100);
		} 
		if (GetAsyncKeyState(VK_F11)) //Change Team
		{
			ChangeTeam();
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_F12)) //Forces a juggernaut
		{
			ForceJugg();
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_END)) //Calls a vote which may crash the server
		{
			CallCrashVote();
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_INSERT)) //Opens the stealing menu
		{
			GrabGuidEnabled = GetState(GrabGuidEnabled);
			Sleep(100);
		}
		//SendCommandToConsole("say ^2Boboo's ^3MULTI^5HACK ^:beta");
		Sleep(10);
	}

	return 1;
}


BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD Reason, LPVOID Reserved)
{
	if (Reason == DLL_PROCESS_ATTACH) {
		MessageBoxMethod("Attached to Process");
		MakeJMP((PBYTE)0x0064427B, (DWORD)ShowMenu, 5);
		CreateThread(NULL, 0, &_MainMethod, NULL, 0, NULL);
		//CreateThread(NULL, 0, &Console, NULL, 0, NULL);
	}

	return TRUE;
}
