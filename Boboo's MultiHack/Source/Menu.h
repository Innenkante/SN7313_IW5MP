#pragma once
class Menu
{
public:
	static void DrawMenuWrapper();
	static void SwitchOnOrOff(int Key);
	static int CurrentActiveMenu;

	static const int ESPMenuTab = 0;
	static const int AimbotMenuTab = 1;
	static const int MiscMenuTab = 2;
	static const int UtilsMenuTab = 3;

	static bool Enabled;
	static int BasePosX;
	static int BasePosY;
	static int OptionNumber;

	static void register_fonts();
	static void register_shaders();
private:
	static void DrawTabHeader(char * TabName, int LeftUPX, int LeftUPY, int RightDownX, int RightDownY, vec4_t ColorTab, int * Shader, int Size, void * Font, vec4_t ColorText, vec4_t ColorBackground);
	static void DrawMenu(int BasePosMenuX, int MenuBasePosY);
	static void DrawESPOptions(int BasePosX, int BasePosY, int WidthX, int LengthY);
	static void DrawAimbotOptions(int BasePosX, int BasePosY, int WidthX, int LengthY);
	static void DrawMiscOptions(int BasePosX, int BasePosY, int WidthX, int LengthY);
	static void DrawUtilsOptions(int BasePosX, int BasePosY, int WidthX, int LengthY);
	static void DrawCurrentOption(int BasePosX, int BasePosY, int Width);
};


