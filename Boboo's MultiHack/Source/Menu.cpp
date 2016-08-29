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
	Draw.DrawTextMW3(BasePosX + 2, BasePosY + 25 , Engine.RegisterFont_(FONT_CONSOLE), ColorBlack, "Cirlces:");
	Draw.DrawTextMW3(BasePosX + 2, BasePosY + 45, Engine.RegisterFont_(FONT_CONSOLE), ColorBlack, "Bones:");
	Draw.DrawTextMW3(BasePosX + 2, BasePosY + 65, Engine.RegisterFont_(FONT_CONSOLE), ColorBlack, "Names:");
	Draw.DrawTextMW3(BasePosX + 2, BasePosY + 85, Engine.RegisterFont_(FONT_CONSOLE), ColorBlack, "Slot:");
	Draw.DrawTextMW3(BasePosX + 2, BasePosY + 105, Engine.RegisterFont_(FONT_CONSOLE), ColorBlack, "Rank:");
	Draw.DrawTextMW3(BasePosX + 2, BasePosY + 125, Engine.RegisterFont_(FONT_CONSOLE), ColorBlack, "Distance:");
	Draw.DrawTextMW3(BasePosX + 2, BasePosY + 145, Engine.RegisterFont_(FONT_CONSOLE), ColorBlack, "Score:");
	Draw.DrawTextMW3(BasePosX + 2, BasePosY + 165, Engine.RegisterFont_(FONT_CONSOLE), ColorBlack, "XUID:");
	Draw.DrawTextMW3(BasePosX + 2, BasePosY + 185, Engine.RegisterFont_(FONT_CONSOLE), ColorBlack, "3DBox:");
	Draw.DrawTextMW3(BasePosX + 2, BasePosY + 205, Engine.RegisterFont_(FONT_CONSOLE), ColorBlack, "Weapons:");
	Draw.DrawTextMW3(BasePosX + 2, BasePosY + 225, Engine.RegisterFont_(FONT_CONSOLE), ColorBlack, "Snaplines:");
	Draw.DrawTextMW3(BasePosX + 2, BasePosY + 245, Engine.RegisterFont_(FONT_CONSOLE), ColorBlack, "Shaders:");
}

void Menu_::DrawAimbotOptions(int BasePosX, int BasePosY, int WidthX, int LengthY)
{
	Draw.DrawRectangleFilled(BasePosX, BasePosY, WidthX, LengthY, 1, ColorGreen);
	Draw.DrawRectangle(BasePosX, BasePosY, BasePosX + WidthX, BasePosY, BasePosX + WidthX, BasePosY + LengthY, BasePosX, BasePosY + LengthY, ColorWhite, Engine.RegisterShader_("white"), 3);
	Draw.DrawTextMW3(BasePosX + 2, BasePosY + 25, Engine.RegisterFont_(FONT_CONSOLE), ColorBlack, "Aimbone:");
	Draw.DrawTextMW3(BasePosX + 2, BasePosY + 45, Engine.RegisterFont_(FONT_CONSOLE), ColorBlack, "AimField:");
	Draw.DrawTextMW3(BasePosX + 2, BasePosY + 65, Engine.RegisterFont_(FONT_CONSOLE), ColorBlack, "Closest Aimbot:");
	Draw.DrawTextMW3(BasePosX + 2, BasePosY + 85, Engine.RegisterFont_(FONT_CONSOLE), ColorBlack, "Aim Assist:");
	Draw.DrawTextMW3(BasePosX + 2, BasePosY + 105, Engine.RegisterFont_(FONT_CONSOLE), ColorBlack, "Trace Aimbot:");
}

void Menu_::DrawMiscOptions(int BasePosX, int BasePosY, int WidthX, int LengthY)
{
	Draw.DrawRectangleFilled(BasePosX, BasePosY, WidthX, LengthY, 1, ColorOrange);
	Draw.DrawRectangle(BasePosX, BasePosY, BasePosX + WidthX, BasePosY, BasePosX + WidthX, BasePosY + LengthY, BasePosX, BasePosY + LengthY, ColorWhite, Engine.RegisterShader_("white"), 3);
	Draw.DrawTextMW3(BasePosX + 2, BasePosY + 25, Engine.RegisterFont_(FONT_CONSOLE), ColorBlack, "NoRecoil:");
	Draw.DrawTextMW3(BasePosX + 2, BasePosY + 45, Engine.RegisterFont_(FONT_CONSOLE), ColorBlack, "FullBright:");
	Draw.DrawTextMW3(BasePosX + 2, BasePosY + 65, Engine.RegisterFont_(FONT_CONSOLE), ColorBlack, "Laser:");
	Draw.DrawTextMW3(BasePosX + 2, BasePosY + 85, Engine.RegisterFont_(FONT_CONSOLE), ColorBlack, "Crosshair:");
	Draw.DrawTextMW3(BasePosX + 2, BasePosY + 105, Engine.RegisterFont_(FONT_CONSOLE), ColorBlack, "NoSpread(DVAR):");
}

void Menu_::DrawUtilsOptions(int BasePosX, int BasePosY, int WidthX, int LengthY)
{
	Draw.DrawRectangleFilled(BasePosX, BasePosY, WidthX, LengthY, 1, ColorRed);
	Draw.DrawRectangle(BasePosX, BasePosY, BasePosX + WidthX, BasePosY, BasePosX + WidthX, BasePosY + LengthY, BasePosX, BasePosY + LengthY, ColorWhite, Engine.RegisterShader_("white"), 3);
}

void Menu_::DrawCurrentOption(int BasePosX, int BasePosY, int Width)
{
	Draw.DrawShaderByName(BasePosX + Width - 20, (BasePosY + 40) + (20 * OptionNumber), 14, 14, ColorWhite, "killiconheadshot");
}

void Menu_::DrawMenuWrapper()
{
	if (Enabled)
	{
		
		DrawMenu(BasePosX, BasePosY);
		if (CurrentActiveMenu ==  ESPMenuTab)
			DrawESPOptions(BasePosX, BasePosY + 30, 200, 300);
		if (CurrentActiveMenu == AimbotMenuTab)
			DrawAimbotOptions(BasePosX, BasePosY + 30, 200, 200);
		if (CurrentActiveMenu == MiscMenuTab)
			DrawMiscOptions(BasePosX, BasePosY + 30, 200, 200);
		if (CurrentActiveMenu == UtilsMenuTab)
			DrawUtilsOptions(BasePosX, BasePosY + 30, 200, 200);
		DrawCurrentOption(BasePosX, BasePosY, 200);

		char buf[64];
		sprintf_s(buf, "%d", OptionNumber);
		Draw.DrawTextMW3(100, 100, Engine.RegisterFont_(FONT_BIG), ColorRed, buf);
	}
	return;
}

void Menu_::DrawTabHeader(char * TabName, int LeftUPX, int LeftUPY, int RightDownX, int RightDownY, vec4_t ColorTab, int * Shader, int Size, void * Font, vec4_t ColorText, vec4_t ColorBackground)
{
	Draw.DrawRectangleFilled(LeftUPX, LeftUPY, RightDownX - LeftUPX, RightDownY - LeftUPY, 1, ColorBackground);
	Draw.DrawRectangle(LeftUPX, LeftUPY, RightDownX, LeftUPY, RightDownX, RightDownY, LeftUPX, RightDownY, ColorTab, Shader, Size);
	Draw.DrawTextMW3(LeftUPX + 2, RightDownY, Font, ColorText, TabName);
}
