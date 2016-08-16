#pragma once
class Menu_
{
public:
	void DrawMenuWrapper();
	int CurrentActiveMenu;
	enum MenuTab
	{
		ESPMenuTab,
		AimbotMenuTab,
		MiscMenuTab,
		UtilsMenuTab
	};
	bool Enabled;
	int BasePosX;
	int BasePosY;
private:
	void DrawTabHeader(char * TabName, int LeftUPX, int LeftUPY, int RightDownX, int RightDownY, vec4_t ColorTab, int * Shader, int Size, void * Font, vec4_t ColorText, vec4_t ColorBackground);
	void DrawMenu(int BasePosMenuX,int MenuBasePosY);
	void DrawESPOptions(int BasePosX, int BasePosY,int WidthX,int LengthY);
	void DrawAimbotOptions(int BasePosX, int BasePosY, int WidthX, int LengthY);
	void DrawMiscOptions(int BasePosX, int BasePosY, int WidthX, int LengthY);
	void DrawUtilsOptions(int BasePosX, int BasePosY, int WidthX, int LengthY);
};


