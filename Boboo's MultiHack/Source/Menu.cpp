#include "Menu.h"
#include "stdafx.h"

#include "LinkingFix.h"

void Menu_::DrawMenu(int BasePosMenuX)
{
	DrawTabHeader("ESP", BasePosMenuX, 20, BasePosMenuX + 40, 50, ColorWhite, Engine.RegisterShader_("white"), 3, Engine.RegisterFont_(FONT_SMALL), ColorBlack, ColorBlue); //Size X = 40
	DrawTabHeader("Aimbot", BasePosMenuX + 40, 20, BasePosMenuX + 40 + 65, 50, ColorWhite, Engine.RegisterShader_("white"), 3, Engine.RegisterFont_(FONT_SMALL), ColorBlack, ColorGreen); //Size X = 65
	DrawTabHeader("Misc", BasePosMenuX + 40 + 65, 20, BasePosMenuX + 40 + 65 + 45, 50, ColorWhite, Engine.RegisterShader_("white"), 3, Engine.RegisterFont_(FONT_SMALL), ColorBlack, ColorOrange); //Size X = 45
	DrawTabHeader("Utils", BasePosMenuX + 40 + 65 + 45, 20, BasePosMenuX + 40 + 65 + 45 + 50, 50, ColorWhite, Engine.RegisterShader_("white"), 3, Engine.RegisterFont_(FONT_SMALL), ColorBlack, ColorRed); //Size X = 50
}

void Menu_::DrawMenuWrapper()
{
	DrawMenu(500);
}

void Menu_::DrawTabHeader(char * TabName, int LeftUPX, int LeftUPY, int RightDownX, int RightDownY, vec4_t ColorTab, int * Shader, int Size, void * Font, vec4_t ColorText, vec4_t ColorBackground)
{
	Draw.DrawRectangleFilled(LeftUPX, LeftUPY, RightDownX - LeftUPX, RightDownY - LeftUPY, 1, ColorBackground);
	Draw.DrawLine(LeftUPX, LeftUPY, RightDownX, LeftUPY, ColorTab, Shader, Size);
	Draw.DrawLine(RightDownX, LeftUPY, RightDownX, RightDownY, ColorTab, Shader, Size);
	Draw.DrawLine(RightDownX, RightDownY, LeftUPX, RightDownY, ColorTab, Shader, Size);
	Draw.DrawLine(LeftUPX, RightDownY, LeftUPX, LeftUPY, ColorTab, Shader, Size);
	Draw.DrawTextMW3(LeftUPX + 2, RightDownY, Font, ColorText, TabName);
}
