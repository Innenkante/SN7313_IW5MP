#pragma once
class Menu_
{
public:
	void DrawMenuWrapper();
	int CurrentActiveMenu;

	int ESPMenuTab = 0;
	int AimbotMenuTab = 1;
	int MiscMenuTab = 2;
	int UtilsMenuTab = 3;

	bool Enabled;
	int BasePosX;
	int BasePosY;
	int OptionNumber;
private:
	void DrawTabHeader(char * TabName, int LeftUPX, int LeftUPY, int RightDownX, int RightDownY, vec4_t ColorTab, int * Shader, int Size, void * Font, vec4_t ColorText, vec4_t ColorBackground);
	void DrawMenu(int BasePosMenuX, int MenuBasePosY);
	void DrawESPOptions(int BasePosX, int BasePosY, int WidthX, int LengthY);
	void DrawAimbotOptions(int BasePosX, int BasePosY, int WidthX, int LengthY);
	void DrawMiscOptions(int BasePosX, int BasePosY, int WidthX, int LengthY);
	void DrawUtilsOptions(int BasePosX, int BasePosY, int WidthX, int LengthY);
	void DrawCurrentOption(int BasePosX, int BasePosY, int Width);
};


