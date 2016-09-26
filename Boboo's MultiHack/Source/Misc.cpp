#include "stdafx.h"
#include "Misc.h"

#include "LinkingFix.h"

bool Misc::NoRecoilEnabled = false;
bool Misc::NoSpreadEnabled = false;
bool Misc::FullBrightEnabled = false;
bool Misc::CrosshairEnabled = false;
bool Misc::LaserEnabled = false;
bool Misc::ChatSpamEnabled = false;
int Misc::OldKillCount = 0;
bool Misc::NoGunEnabled = false;


void Misc::NoRecoil()
{
	BYTE* nr = (BYTE*)NORECOILOFF;
	if (NoRecoilEnabled)
		*nr = 235;
	else
		*nr = 116;
}

void Misc::NoSpread()
{
	float* nospr = (float*)NOSPREADOFF;
	if (NoSpreadEnabled)
		*nospr = 0;
	else
		*nospr = 0.6499999762f;
}

void Misc::FullBright()
{
	int* fullbright = (int*)FULLBRIGHTOFF;
	if (FullBrightEnabled)
		*fullbright = 4;
	else
		*fullbright = 9;
}

void Misc::Laser()
{
	BYTE* laser = (BYTE*)LASEROFF;

	if (LaserEnabled)
		*laser = 0;
	else
		*laser = 37;
}

void Misc::Crosshair()
{
	if (!CrosshairEnabled)
		return;
	RefDef_T* refdef = (RefDef_T*)REFDEFOFF;

	if (!refdef->Width || !refdef->Height)
		return;
	Draw::DrawTextMW3(refdef->Width / 2 - 7, refdef->Height / 2 + 10, Engine.RegisterFont_(FONT_BIG_DEV), ColorGreen, "+");
}

void Misc::ChangeName()
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

void Misc::UnlockClasses()
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

void Misc::ForceJugg()
{
	CG_T* cg = (CG_T*)CGOFF;
	int* MagicNum = (int*)MATCHIDOFF;
	char buffer[1024];
	ClientInfo_T* LocalClient = (ClientInfo_T*)(CLIENTOFF + (CLIENTSIZE * cg->ClientNumber));
	if (LocalClient->Team == 1)
		sprintf_s(buffer, "cmd mr %d 9 allies", *MagicNum);
	if (LocalClient->Team == 2)
		sprintf_s(buffer, "cmd mr %d 9 axis", *MagicNum);
	Engine.ProcessCMD_(0,buffer);
}

void Misc::ChangeTeam()
{
	CG_T* cg = (CG_T*)CGOFF;
	int* MagicNum = (int*)MATCHIDOFF;
	char buffer[1024];
	ClientInfo_T* LocalClient = (ClientInfo_T*)(CLIENTOFF + CLIENTSIZE * cg->ClientNumber);
	if (LocalClient->Team == 1)
		sprintf_s(buffer, "cmd mr %d 2 allies", *MagicNum);
	if (LocalClient->Team == 2)
		sprintf_s(buffer, "cmd mr %d 2 axis", *MagicNum); //This shit aint working right till now :S and thx to Kenny for the menuresponses they are bae
	Engine.ProcessCMD_(0, buffer);
}

char* Misc::GetPlayerName()
{
	const char* Name = (const char*)PLAYERNAMEOFF;
	char buf[32] = "";
	sprintf_s(buf, Name);
	return buf;
}

char * Misc::GetPlayerXUID()
{
	int* ID = (int*)XUIDOFF;
	char buf[16];
	sprintf_s(buf, "%ld", *ID);
	return buf;
}

char * Misc::GetServerName()
{
	const char* ServerName = (const char*)SERVERNAMEOFF;
	char buf[64] = "";
	sprintf_s(buf, ServerName);
	return buf;
}

char * Misc::GetServerIP()
{
	const char* ServerIP = (const char*)SERVERIPOFF;
	char buf[32] = "";
	sprintf_s(buf, ServerIP);
	return buf;
}


void Misc::ChatSpam()
{
	if (!ChatSpamEnabled)
		return;

	int KillCount = *(int*)0x335F6DF4;
	if (KillCount == 0)
	{
		OldKillCount == 0;
	}

	if (KillCount > OldKillCount)
	{
		char* OpponenetsName = (char*)0x058C379E;
		char Buf[128];
		sprintf_s(Buf, "say %s ^1got ^2rekt ^3by ^5SN7313 ^4Download ^;at ^:mpgh.net",*OpponenetsName);
		Engine.ProcessCMD_(0, Buf);
		OldKillCount = KillCount;
	}

}

void Misc::Wrapper()
{
	Misc::Crosshair();
}

void Misc::VoteKickPlayerExploit()
{
	const char* Name = GetPlayerName();
	char Buffer[64];
	sprintf_s(Buffer, "callvote kick %s", Name);
	Engine.ProcessCMD_(0, Buffer);
}

void Misc::NoGun()
{
	int* PosZ = (int*)0x59D3938;
	int* PosX = (int*)0x59D3984;
	if (NoGunEnabled)
	{
		*PosZ = -1;
		*PosX = -2;
	}
	else
	{
		*PosZ = 0;
		*PosX = 0;
	}
	
	
}
