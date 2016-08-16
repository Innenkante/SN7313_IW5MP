#pragma once
class Misc_
{
public:
	void NoRecoil(bool state);
	void NoSpread(bool state);
	void FullBright(bool state);
	void Laser(bool state);
	void Crosshair(bool state);
	void ChangeName();
	void RandomCreds();
	void UnlockClasses();
	void ForceJugg();
	void ChangeTeam();
	char* GetPlayerName();
	char* GetPlayerXUID();
	char* GetServerName();
	char* GetServerIP();

private:

};
