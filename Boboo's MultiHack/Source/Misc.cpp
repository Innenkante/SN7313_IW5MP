#include "stdafx.h"
#include "Misc.h"

#include "LinkingFix.h"


void Misc_::NoRecoil(bool state)
{
	BYTE* nr = (BYTE*)NORECOILOFF;
	if (state)
		*nr = 235;
	else
		*nr = 116;
}

void Misc_::NoSpread(bool state)
{
	float* nospr = (float*)NOSPREADOFF;
	if (state)
		*nospr = 0;
	else
		*nospr = 0.6499999762f;
}

void Misc_::FullBright(bool state)
{
	int* fullbright = (int*)FULLBRIGHTOFF;
	if (state)
		*fullbright = 4;
	else
		*fullbright = 9;
}

void Misc_::Laser(bool state)
{
	BYTE* laser = (BYTE*)LASEROFF;

	if (state)
		*laser = 0;
	else
		*laser = 37;
}

void Misc_::Crosshair(bool state)
{
	if (!state)
		return;
	RefDef_T* refdef = (RefDef_T*)REFDEFOFF;

	if (!refdef->Width || !refdef->Height)
		return;
	Draw.DrawTextMW3(refdef->Width / 2 - 7, refdef->Height / 2 + 10, Engine.RegisterFont_(FONT_BIG_DEV), ColorGreen, "+");
}

void Misc_::ChangeName()
{
	srand(static_cast<int>(time(NULL)));
	BYTE* checkname = (BYTE*)PLAYERNAMECHECKBYTEOFF;
	*checkname = 0xC3;
	int random = rand() % 100;
	char* name = (char*)PLAYERNAMEOFF;
	char newname[16];
	sprintf_s(newname, "Scrub %d", random);
	for (int i = 0; i < 16; i++)
		name[i] = newname[i];
}

void Misc_::RandomCreds()
{
	srand(static_cast<int>(time(NULL)));
	*(ULONG*)0x05CCB272 = (ULONG)(0x11000010000000 + rand() + (rand() * 10) + (rand() * 100));//steam
	*(ULONG*)0x00464A58 = (ULONG)(0x11000010000000 + rand() + (rand() * 10) + (rand() * 100));//xna
	*(ULONG*)0x05A7B1D8 = (ULONG)(0x11000010000000 + rand() + (rand() * 10) + (rand() * 100));//xuid

	ChangeName();
}

void Misc_::UnlockClasses()
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

void Misc_::ForceJugg()
{
	CG_T* cg = (CG_T*)CGOFF;
	int* MagicNum = (int*)MATCHIDOFF;
	char buffer[1024];
	ClientInfo_T* LocalClient = (ClientInfo_T*)(CLIENTOFF + (CLIENTSIZE * cg->ClientNumber));
	if (LocalClient->Team == 1)
		sprintf_s(buffer, "cmd mr %d 9 allies", *MagicNum);
	if (LocalClient->Team == 2)
		sprintf_s(buffer, "cmd mr %d 9 axis", *MagicNum);
	Engine.SendCommandToConsole(buffer);
}

void Misc_::ChangeTeam()
{
	CG_T* cg = (CG_T*)CGOFF;
	int* MagicNum = (int*)MATCHIDOFF;
	char buffer[1024];
	ClientInfo_T* LocalClient = (ClientInfo_T*)(CLIENTOFF + CLIENTSIZE * cg->ClientNumber);
	if (LocalClient->Team == 1)
		sprintf_s(buffer, "cmd mr %d 2 allies", *MagicNum);
	if (LocalClient->Team == 2)
		sprintf_s(buffer, "cmd mr %d 2 axis", *MagicNum); //This shit aint working right till now :S and thx to Kenny for the menuresponses they are bae
	Engine.SendCommandToConsole(buffer);
}

char* Misc_::GetPlayerName()
{
	const char* Name = (const char*)PLAYERNAMEOFF;
	char buf[32] = "";
	sprintf_s(buf, Name);
	return buf;
}

char * Misc_::GetPlayerXUID()
{
	int* ID = (int*)XUIDOFF;
	char buf[16];
	sprintf_s(buf, "%ld", *ID);
	return buf;
}

char * Misc_::GetServerName()
{
	const char* ServerName = (const char*)SERVERNAMEOFF;
	char buf[64] = "";
	sprintf_s(buf, ServerName);
	return buf;
}

char * Misc_::GetServerIP()
{
	const char* ServerIP = (const char*)SERVERIPOFF;
	char buf[32] = "";
	sprintf_s(buf, ServerIP);
	return buf;
}

