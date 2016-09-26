#pragma once
class Misc
{
public:
	static bool NoRecoilEnabled;
	static bool NoSpreadEnabled;
	static bool FullBrightEnabled;
	static bool CrosshairEnabled;
	static bool LaserEnabled;
	static bool ChatSpamEnabled;
	static bool NoGunEnabled;
	static void NoRecoil();
	static void NoSpread();
	static void FullBright();
	static void Laser();
	static void Crosshair();
	static void ChangeName();
	static void UnlockClasses();
	static void ForceJugg();
	static void ChangeTeam();
	static char* GetPlayerName();
	static char* GetPlayerXUID();
	static char* GetServerName();
	static char* GetServerIP();
	static void ChatSpam();
	static void Wrapper();
	static void VoteKickPlayerExploit();
	static void NoGun();
	static int OldKillCount;
private:

};
