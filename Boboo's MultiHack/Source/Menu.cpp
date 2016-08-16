#include "Menu.h"
#include "stdafx.h"

#include "LinkingFix.h"

void Menu_::DrawMenu(int BasePosMenuX,int BasePosMenuY)
{
	DrawTabHeader("ESP", BasePosMenuX, BasePosMenuY, BasePosMenuX + 40, BasePosMenuY + 30, ColorWhite, Engine.RegisterShader_("white"), 3, Engine.RegisterFont_(FONT_SMALL), ColorBlack, ColorBlue); //Size X = 40
	DrawTabHeader("Aimbot", BasePosMenuX + 40, BasePosMenuY, BasePosMenuX + 40 + 65, BasePosMenuY + 30, ColorWhite, Engine.RegisterShader_("white"), 3, Engine.RegisterFont_(FONT_SMALL), ColorBlack, ColorGreen); //Size X = 65
	DrawTabHeader("Misc", BasePosMenuX + 40 + 65, BasePosMenuY, BasePosMenuX + 40 + 65 + 45, BasePosMenuY + 30, ColorWhite, Engine.RegisterShader_("white"), 3, Engine.RegisterFont_(FONT_SMALL), ColorBlack, ColorOrange); //Size X = 45
	DrawTabHeader("Utils", BasePosMenuX + 40 + 65 + 45, BasePosMenuY, BasePosMenuX + 40 + 65 + 45 + 50, BasePosMenuY + 30, ColorWhite, Engine.RegisterShader_("white"), 3, Engine.RegisterFont_(FONT_SMALL), ColorBlack, ColorRed); //Size X = 50
}

void Menu_::DrawESPOptions(int BasePosX, int BasePosY,int WidthX,int LengthY)
{
	Draw.DrawRectangleFilled(BasePosX, BasePosY, WidthX, LengthY, 1, ColorBlue);
	Draw.DrawRectangle(BasePosX, BasePosY, BasePosX + WidthX, BasePosY, BasePosX + WidthX, BasePosY + LengthY, BasePosX, BasePosY + LengthY, ColorWhite, Engine.RegisterShader_("white"), 3);
}

void Menu_::DrawAimbotOptions(int BasePosX, int BasePosY, int WidthX, int LengthY)
{
	Draw.DrawRectangleFilled(BasePosX, BasePosY, WidthX, LengthY, 1, ColorGreen);
	Draw.DrawRectangle(BasePosX, BasePosY, BasePosX + WidthX, BasePosY, BasePosX + WidthX, BasePosY + LengthY, BasePosX, BasePosY + LengthY, ColorWhite, Engine.RegisterShader_("white"), 3);
}

void Menu_::DrawMiscOptions(int BasePosX, int BasePosY, int WidthX, int LengthY)
{
	Draw.DrawRectangleFilled(BasePosX, BasePosY, WidthX, LengthY, 1, ColorOrange);
	Draw.DrawRectangle(BasePosX, BasePosY, BasePosX + WidthX, BasePosY, BasePosX + WidthX, BasePosY + LengthY, BasePosX, BasePosY + LengthY, ColorWhite, Engine.RegisterShader_("white"), 3);
}

void Menu_::DrawUtilsOptions(int BasePosX, int BasePosY, int WidthX, int LengthY)
{
	Draw.DrawRectangleFilled(BasePosX, BasePosY, WidthX, LengthY, 1, ColorRed);
	Draw.DrawRectangle(BasePosX, BasePosY, BasePosX + WidthX, BasePosY, BasePosX + WidthX, BasePosY + LengthY, BasePosX, BasePosY + LengthY, ColorWhite, Engine.RegisterShader_("white"), 3);
}

void Menu_::DrawMenuWrapper()
{
	if (Enabled)
	{
		DrawMenu(BasePosX, BasePosY);
		if (CurrentActiveMenu == ESPMenuTab)
			DrawESPOptions(BasePosX, BasePosY + 30, 200, 200);
		if (CurrentActiveMenu == AimbotMenuTab)
			DrawAimbotOptions(BasePosX, BasePosY + 30, 200, 200);
		if (CurrentActiveMenu == MiscMenuTab)
			DrawMiscOptions(BasePosX, BasePosY + 30, 200, 200);
		if (CurrentActiveMenu == UtilsMenuTab)
			DrawUtilsOptions(BasePosX, BasePosY + 30, 200, 200);
	}
	return;
}

void Menu_::DrawTabHeader(char * TabName, int LeftUPX, int LeftUPY, int RightDownX, int RightDownY, vec4_t ColorTab, int * Shader, int Size, void * Font, vec4_t ColorText, vec4_t ColorBackground)
{
	Draw.DrawRectangleFilled(LeftUPX, LeftUPY, RightDownX - LeftUPX, RightDownY - LeftUPY, 1, ColorBackground);
	Draw.DrawRectangle(LeftUPX, LeftUPY, RightDownX, LeftUPY, RightDownX, RightDownY, LeftUPX, RightDownY, ColorTab, Shader, Size);
	Draw.DrawTextMW3(LeftUPX + 2, RightDownY, Font, ColorText, TabName);
}
