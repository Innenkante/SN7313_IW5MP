
#include "stdafx.h"

bool NoSpreadEnabled = false;
bool NoRecoilEnabled = false;
bool WhEnabled = false;
bool FullBrightEnabled = false;
bool LaserEnabled = false;
bool RadarEnabled = false;
bool MenuEnabled = true;
vec4_t ColorWhite = { 1.0f,1.0f,1.0f,1.0f };
vec4_t ColorGreen = { 0.0f,  1.0f,  0.0f,  1.0f };
vec4_t ColorRed = { 1.0f,  0.0f,  0.0f,  1.0f };
vec4_t ColorBlue = { 0.0f,  0.0f,  1.0f,  1.0f };
void* ConsoleFont;



tDrawEngineText DrawEngineText_ = (tDrawEngineText)DRAWENGINETEXTOFF;
tRegisterFont RegisterFont_ = (tRegisterFont)REGISTERFONTOFF;
tDrawEngineRadar DrawEngineRadar = (tDrawEngineRadar)DRAWENGINERADAROFF;
R_RegisterShaderPtr RegisterShaderPtr_ = (R_RegisterShaderPtr)REGISTERSHADEROFF;
tGetScreenMatrix GetScreenMatrix = (tGetScreenMatrix)SCREENMATRIXOFF;




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
	return RegisterShaderPtr_(shader);
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
	std::ostringstream oss;
	oss << "Player" << random;
	std::string newName = oss.str();
	std::string* Name = (std::string*)PLAYERNAMEOFF;
	*Name = newName;
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

void ChopperBoxes()
{
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
		RefDef_T* RefDef = (RefDef_T*)REFDEF;
		CRadarHud radarhud;
		int RadarW = 225;
		int RadarH = RadarW;

		int RadarX = RefDef->Width - 20 - RadarW;
		int RadarY = 13;

		radarhud.x = ScaleRadarX(RadarX);
		radarhud.y = ScaleRadarY(RadarY);
		radarhud.w = ScaleRadarX(RadarW);
		radarhud.h = ScaleRadarY(RadarH);

		DrawEngineRadar(0, 0, 0, &radarhud, RegisterShader("black"), ColorBlue);
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
		sprintf(buffer, "cmd mr %d 2 axis", MagicNum);
	if(LocalClient->Team == 2)
		sprintf(buffer, "cmd mr %d 2 allies", MagicNum);

	SendCommandToConsole(buffer);
}

void CallCrashVote()
{
	char buffer[1024];
	sprintf(buffer,"callvote map_rotate");
	SendCommandToConsole(buffer);
}


void Menu()
{
	char buf[2048];
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
	strncat(buf, "\n", sizeof(buf));
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
		DrawTextMW3(550, 40, ConsoleFont, ColorWhite, buf);
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

__declspec(naked) void uiShowList()
{
	__asm
	{
		CALL[dwCall]
		PUSHAD;
		PUSHFD;
	}
	Menu();
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
	ConsoleFont = RegisterFont(FONT_CONSOLE); //Registering the Font before using it in the Menu
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
		if (GetAsyncKeyState(VK_F11))//Change Team
		{
			ChangeTeam();
		}
		if (GetAsyncKeyState(VK_F12))//Forces a juggernaut
		{
			ForceJugg();
		}
		if (GetAsyncKeyState(VK_END))//Calls a vote which may crash the server
		{
			CallCrashVote();
		}
		
		//SendCommandToConsole("say ^2Boboo's ^3MULTI^5HACK ^:beta");
		Sleep(10);
	}

	return 1;
}

//DWORD WINAPI Console(LPVOID foo)
//{
//	AllocConsole();
//	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
//	int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
//	FILE* hf_out = _fdopen(hCrt, "w");
//	setvbuf(hf_out, NULL, _IONBF, 1);
//	*stdout = *hf_out;
//
//	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
//	hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
//	FILE* hf_in = _fdopen(hCrt, "r");
//	setvbuf(hf_in, NULL, _IONBF, 128);
//	*stdin = *hf_in;
//	//https://justcheckingonall.wordpress.com/2008/08/29/console-window-win32-app/
//
//	bool MainEnabled = true;
//	bool DevEnabled = true;
//	std::string input;
//	char buffer[1024];
//
//	std::cout << "Boboo's ModerWarfare 3 External Console" << std::endl;
//	std::cout << "---------------------------------------" << std::endl;
//	while (MainEnabled)
//	{
//		std::string input;
//		int* MatchID = (int*)0xFF5058;
//		std::cout << "Enter your command:" << std::endl;
//		getline(std::cin, input);
//		if (input == "exit")
//			MainEnabled = false;
//		if (input == "help")
//		{
//			std::cout << "juggernaut-allies -> Forces a juggernaut in allies team" << std::endl;
//			std::cout << "juggernaut-axis -> Forces a juggernaut in axis team" << std::endl;
//			std::cout << "spectator -> Puts yourself in specator mode" << std::endl;
//			std::cout << "crash -> Crashes other clients when they vote" << std::endl;
//			std::cout << "allies -> Changes your team to allies" << std::endl;
//			std::cout << "axis -> Changes your team to axis" << std::endl;
//			std::cout << "devmode -> You can execute your own commands now(It may crash if you fuck something up)" << std::endl;
//		}
//		if (input == "juggernaut-allies")
//		{
//			sprintf_s(buffer, "cmd mr %d 9 allies", *MatchID);
//			SendCommandToConsole(buffer);
//		}
//		if (input == "juggernaut-axis")
//		{
//			sprintf_s(buffer, "cmd mr %d 9 axis", *MatchID);
//			SendCommandToConsole(buffer);
//		}
//		if (input == "spectator")
//		{
//			sprintf_s(buffer, "cmd mr %d 2 spectator", *MatchID);
//			SendCommandToConsole(buffer);
//		}
//		if (input == "crash")
//		{
//			sprintf_s(buffer, "callvote map_rotate");
//			SendCommandToConsole(buffer);
//		}
//		if (input == "allies")
//		{
//			sprintf_s(buffer, "cmd mr %d 2 allies", *MatchID);
//			SendCommandToConsole(buffer);
//		}
//		if (input == "axis")
//		{
//			std::string cmd;
//			sprintf_s(buffer, "cmd mr %d 2 axis", *MatchID);
//			SendCommandToConsole(buffer);
//		}
//		if (input == "clear")
//		{
//			system("cls");
//			std::cout << "Boboo's ModerWarfare 3 External Console" << std::endl;
//			std::cout << "---------------------------------------" << std::endl;
//		}
//		if (input == "devmode")
//		{
//			std::cout << "Entered developer mode" << std::endl;
//			while (DevEnabled)
//			{
//				std::string cmd;
//				char buff[1024];
//				std::cout << "Enter your command:" << std::endl;
//				getline(std::cin, cmd);
//				if (cmd == "exit")
//					DevEnabled = false;
//				if (cmd == "matchid")
//				{
//					std::cout << "MatchID:" << *MatchID << std::endl;
//					continue;
//				}
//				strcpy_s(buff, cmd.c_str());
//				SendCommandToConsole(buff);
//			}
//			std::cout << "Exited developer mode" << std::endl;
//		}
//		else
//			std::cout << "Command not found" << std::endl;
//		Sleep(5);
//	}
//	return 1;
//}




BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD Reason, LPVOID Reserved)
{
	if (Reason == DLL_PROCESS_ATTACH) {
		MessageBoxMethod("Attached to Process");
		MakeJMP((PBYTE)0x0064427B, (DWORD)uiShowList, 5);
		CreateThread(NULL, 0, &_MainMethod, NULL, 0, NULL);
		CreateThread(NULL, 0, &Console, NULL, 0, NULL);
	}

	return TRUE;
}
